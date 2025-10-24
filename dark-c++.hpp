#pragma once
#include <type_traits>
#include <tuple>
#include <utility>

namespace darkｰcᚐᚐ {
// Dispatchers store arguments and forward them to the correct function when the
// Dispatcher is converted to another type.
//
// Each Dispatcher instantiation handles forwarding calls to one function.
// Dispatchers inheret from another dispatcher, so that together, all the
// dispatchers form an inheretance chain, and the head dispatcher has an
// operator T() for each function's return type, so overload resolution will
// choose the correct function based on which type the head Dispatcher is being
// converted to. The Parent at the bottom is a plain tuple of args, so that the
// dispatcher chain has one copy of the args.
template<typename Parent, auto F, typename... Args>
struct Dispatcher : Parent {
	operator decltype(F(std::declval<Args>()...))() {
		std::tuple<Args&&...>& args = *this;
		return std::apply(F, args);
	}
};

// return_type_overload recursively converts a list of functions into a
// Dispatcher chain. At call time, each function which matches the Args list
// becomes a Dispatcher in the chain, while non-matching functions are skipped.
template<auto... Fs>
struct return_type_overload;

template<auto F, auto... Fs>
struct return_type_overload<F, Fs...> {
	template<typename... Args>
		requires std::is_invocable_v<decltype(F), Args...>
	static auto operator()(Args&&... args) {
		return Dispatcher<
			decltype(return_type_overload<Fs...>{}(args...)),
			F,
			Args...
		>{std::forward_as_tuple<Args...>(args...)};
	};

	template<typename... Args>
		requires (!std::is_invocable_v<decltype(F), Args...>)
	static auto operator()(Args&&... args) {
		return return_type_overload<Fs...>{}(args...);
	};
};

// return_type_overload with an empty list of functions just returns a tuple of
// arguments. This forms the bottom of the Dispatcher chain.
template<>
struct return_type_overload<> {
	template<typename... Args>
	static auto operator()(Args&&... args) {
		return std::forward_as_tuple<Args...>(args...);
	};
};

}

namespace dcpp = darkｰcᚐᚐ;
