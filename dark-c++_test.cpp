#include <dark-c++.hpp>
#include <iostream>

const auto foo = dcpp::return_type_overload<
	[](const char* msg) -> int {
		std::cout << msg << ' ';
		return -2;
	},
	[]() -> int {return -1;},
	[]() -> unsigned {return 1;}
>{};

int main(int argc, char **argv) {
	if (argc != 1) {
		std::cout << argv[0] << " takes no arguments.\n";
		return 1;
	}

	const int bar_int = foo("Hi");
	std::cout << bar_int << '\n'; // prints "Hi -2"

	const int bar_int_nomsg = foo();
	std::cout << bar_int_nomsg << '\n'; // prints "-1"

	const unsigned bar_unsigned = foo();
	std::cout << bar_unsigned << '\n'; // prints "1"
}
