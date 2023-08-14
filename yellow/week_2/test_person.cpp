#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// using namespace std;

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		} catch (std::exception& e) {
			++fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		} catch (...) {
			++fail_count;
			std::cerr << "Unknown exception caught" << std::endl;
		}
	}
	
	~TestRunner() {
		if (fail_count > 0) {
			std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

// если имя неизвестно, возвращает пустую строку
std::string FindNameByYear(const std::map<int, std::string>& names, int year) {
	std::string name;  // изначально имя неизвестно
	
	// перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
	for (const auto& item : names) {
		// если очередной год не больше данного, обновляем имя
		if (item.first <= year) {
			name = item.second;
		} else {
			// иначе пора остановиться, так как эта запись и все последующие относятся
			// к будущему
			break;
		}
	}
	
	return name;
}

class Person {
public:
	// Вы можете вставлять сюда различные реализации класса,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный
	void ChangeFirstName(int year, const std::string& first_name) {
		first_names[year] = first_name;
	}

	void ChangeLastName(int year, const std::string& last_name) {
		last_names[year] = last_name;
	}
	
	std::string GetFullName(int year) {
		// получаем имя и фамилию по состоянию на год year
		const std::string first_name = FindNameByYear(first_names, year);
		const std::string last_name = FindNameByYear(last_names, year);
		
		// если и имя, и фамилия неизвестны
		if (first_name.empty() && last_name.empty()) {
		  return "Incognito";
		
		// если неизвестно только имя
		} else if (first_name.empty()) {
		  return last_name + " with unknown first name";
		
		// если неизвестна только фамилия
		} else if (last_name.empty()) {
		  return first_name + " with unknown last name";
		
		// если известны и имя, и фамилия
		} else {
		  return first_name + " " + last_name;
		}
	}

private:
	// приватные поля
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
};

void testNoName() {
	{
		Person empty;
		AssertEqual(empty.GetFullName(1965), "Incognito", "Testing empty");
	}
	{
		Person person;
		person.ChangeFirstName(2003, "Shirwani");
		person.ChangeLastName(2004, "Smith");
		AssertEqual(person.GetFullName(2001), "Incognito",
			"Testing a year that is too early");
	}
}

void testNoFirstName() {
	{
		Person person;
		person.ChangeLastName(1960, "Knuth");
		AssertEqual(person.GetFullName(1970), "Knuth with unknown first name",
			"Testing when there is no first name");
	}
	{
		Person person;
		person.ChangeFirstName(2020, "Abdurroshid");
		person.ChangeLastName(1990, "Shabazov");
		AssertEqual(person.GetFullName(1991), "Shabazov with unknown first name",
			"Testing when first name added later");
	}
}

void testNoLastName() {
	{
		Person person;
		person.ChangeFirstName(1960, "Alan");
		AssertEqual(person.GetFullName(1970), "Alan with unknown last name",
			"Testing when there is no last name");
	}
	{
		Person person;
		person.ChangeFirstName(1990, "Rashid");
		person.ChangeLastName(2020, "Shabazov");
		AssertEqual(person.GetFullName(1991), "Rashid with unknown last name",
			"Testing when last name added later");
	}
}

void testFullName() {
	Person person;
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	AssertEqual(person.GetFullName(1967), "Polina Sergeeva",
		"Testing with both first and last name");
	// for (int year : {1900, 1965, 1990}) {
	// 	std::cout << person.GetFullName(year) << std::endl;
	// }

	// person.ChangeFirstName(1970, "Appolinaria");
	// for (int year : {1969, 1970}) {
	// 	std::cout << person.GetFullName(year) << std::endl;
	// }

	// person.ChangeLastName(1968, "Volkova");
	// for (int year : {1969, 1970}) {
	// 	std::cout << person.GetFullName(year) << std::endl;
	// }

	// person.ChangeFirstName(1990, "Polina");
	// person.ChangeLastName(1990, "Volkova-Sergeeva");
	// std::cout << person.GetFullName(1990) << std::endl;

	// person.ChangeFirstName(1966, "Pauline");
	// std::cout << person.GetFullName(1966) << std::endl;	
	
	// person.ChangeLastName(1960, "Sergeeva");
	// for (int year : {1960, 1967}) {
	// 	std::cout << person.GetFullName(year) << std::endl;
	// }	
	
	// person.ChangeLastName(1961, "Ivanova");
	// std::cout << person.GetFullName(1967) << std::endl;
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(testNoName, "testNoName");
  runner.RunTest(testNoFirstName, "testNoFirstName");
  runner.RunTest(testNoLastName, "testNoLastName");
  runner.RunTest(testFullName, "testFullName");

  return 0;
}
