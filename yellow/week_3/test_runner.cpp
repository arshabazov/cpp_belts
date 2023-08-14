#include "test_runner.h"

void Assert(bool b, const std::string& hint) {
	assertEqual(b, true, hint);
}

TestRunner::~TestRunner() {
	if (fail_counter > 0) {
		std::cerr << "Tests failed: " << fail_counter
		<< " Terminating" << std::endl;
		exit(EXIT_FAILURE);
	}
}