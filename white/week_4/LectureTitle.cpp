#include <string>

struct Specialization {
	std::string value;
	
	explicit Specialization(std::string new_val) {
		value = new_val;
	}
};

struct Course {
	std::string value;
	
	explicit Course(std::string new_val) {
		value = new_val;
	}
};

struct Week {
	std::string value;
	
	explicit Week(std::string new_val) {
		value = new_val;
	}
};

struct LectureTitle {
	std::string specialization;
	std::string course;
	std::string week;
	
	LectureTitle(Specialization new_spec, Course new_course, Week new_week) {
		specialization = new_spec.value;
		course = new_course.value;
		week = new_week.value;
	}
};