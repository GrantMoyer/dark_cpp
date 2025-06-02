#pragma once
#include <type_traits>
#include <tuple>
#include <utility>

namespace darkｰcᚐᚐ {
template<auto F, std::size_t... Index, typename... Args>
auto call_with_tuple(std::index_sequence<Index...> _, std::tuple<Args...>& args) {
	(void) _;
	return F(std::get<Index>(args)...);
}

template<typename Parent, auto F, typename... Args>
struct Dispatcher : Parent {
	operator decltype(F(std::declval<Args>()...))() {
		return call_with_tuple<F>(std::index_sequence_for<Args...>{}, *this);
	}
};

template<auto... Fs>
struct return_type_overload;

template<auto F, auto... Fs>
struct return_type_overload<F, Fs...> {
	template<typename... Args>
		requires std::is_invocable_v<decltype(F), Args...>
	static auto f(Args... args) {
		return Dispatcher<
			decltype(return_type_overload<Fs...>::f(args...)),
			F,
			Args...
		>{std::tuple<Args...>(args...)};
	};

	template<typename... Args>
		requires (!std::is_invocable_v<decltype(F), Args...>)
	static auto f(Args... args) {
		return return_type_overload<Fs...>::f(args...);
	};
};

template<>
struct return_type_overload<> {
	template<typename... Args>
	static auto f(Args... args) {
		return std::tuple<Args...>(args...);
	};
};

}


namespace dcpp = darkｰcᚐᚐ;
