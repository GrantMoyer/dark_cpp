#include <dark-c++.hpp>
#include <iostream>

template<typename... Args>
auto foo(Args... args) {
	return dcpp::return_type_overload<
		[]() -> int {return -1;},
		[]() -> unsigned {return 1;},
		[](const char* msg) -> int {
			std::cout << msg << '\n';
			return -2;
		}
	>::f(args...);
};

int main(int argc, char **argv) {
    if (argc != 1) {
        std::cout << argv[0] << " takes no arguments.\n";
        return 1;
    }

	const int bar_int = foo("Hi");
    std::cout << bar_int << '\n';

	const int bar_int_nomsg = foo();
    std::cout << bar_int_nomsg << '\n';

	const unsigned bar_unsigned = foo();
    std::cout << bar_unsigned << '\n';
}
