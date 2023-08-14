#include <tuple>
#include <map>
#include <iostream>

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,			// новая
	IN_PROGRESS,	// в разработке
	TESTING,		// на тестировании
	DONE			// завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
private:
	std::map<std::string, TasksInfo> staffTaskList;
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
		return staffTaskList.at(person);
	}
	
	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const std::string& person) {
		if (staffTaskList.count(person) == 0) {
			staffTaskList[person][TaskStatus::NEW] = 0;
			staffTaskList[person][TaskStatus::IN_PROGRESS] = 0;
			staffTaskList[person][TaskStatus::TESTING] = 0;
			staffTaskList[person][TaskStatus::DONE] = 0;
		}
		++staffTaskList[person][TaskStatus::NEW];
	}
	
	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count) {
		TasksInfo updated, old;
		TasksInfo& taskList = staffTaskList.at(person);
		// auto it = taskList.begin();
		int forward_points = 0;

		for (auto it = taskList.begin(); it != taskList.end()
			&& (task_count > 0 || forward_points > 0); ++it) {
			if (forward_points > 0) {
				updated[it->first] = forward_points;
				forward_points = 0;
			}
			if (task_count > it->second) {
				forward_points = it->second;
				task_count -= it->second;
				it->second = 0;
			} else {
				forward_points = task_count;
				it->second -= task_count;
				task_count = 0;
				old[it->first] = it->second;
			}
		}
		for (auto& [type, tasks] : updated) {
			taskList[type] += tasks;
		}

		return std::tie(updated, old);
	}
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	
	std::cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	std::cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	std::cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	std::cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	std::cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	std::cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	
	return 0;
}