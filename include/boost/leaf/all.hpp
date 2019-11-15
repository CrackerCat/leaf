#ifndef LEAF_3382F652FCDD11E8AAD1CCB3642D5A5F
#define LEAF_3382F652FCDD11E8AAD1CCB3642D5A5F

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/leaf/config.hpp>
#line 1 "boost/leaf/config.hpp"
#ifndef LEAF_13D3591AFC6811E9883D0A836044C98A
#define LEAF_13D3591AFC6811E9883D0A836044C98A

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if defined(LEAF_NO_DIAGNOSTIC_INFO) && !defined(LEAF_DISCARD_UNEXPECTED)
#	define LEAF_DISCARD_UNEXPECTED
#endif

#ifdef LEAF_USE_BOOST_CONFIG
#	include <boost/config.hpp>
#	if !defined(LEAF_NO_EXCEPTIONS) && defined(BOOST_NO_EXCEPTIONS)
#		define LEAF_NO_EXCEPTIONS
#	endif
#	if !defined(LEAF_NO_THREADS) && !defined(BOOST_HAS_THREADS)
#		define LEAF_NO_THREADS
#	endif
#endif

#endif
// <<< #include <boost/leaf/config.hpp>
#line 10 "../../include/boost/leaf/detail/all.hpp"
// >>> #include <boost/leaf/capture.hpp>
#line 1 "boost/leaf/capture.hpp"
#ifndef LEAF_BC24FB98B2DE11E884419CF5AD35F1A2
#define LEAF_BC24FB98B2DE11E884419CF5AD35F1A2

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/leaf/exception.hpp>
#line 1 "boost/leaf/exception.hpp"
#ifndef LEAF_75F38740D98D11E881DDB244C82C3C47
#define LEAF_75F38740D98D11E881DDB244C82C3C47

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/leaf/error.hpp>
#line 1 "boost/leaf/error.hpp"
#ifndef LEAF_BA049396D0D411E8B45DF7D4A759E189
#define LEAF_BA049396D0D411E8B45DF7D4A759E189

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/leaf/detail/function_traits.hpp>
#line 1 "boost/leaf/detail/function_traits.hpp"
#ifndef LEAF_14440B9CF07011E88377FD4B0ABE8030
#define LEAF_14440B9CF07011E88377FD4B0ABE8030

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/leaf/detail/mp11.hpp>
#line 1 "boost/leaf/detail/mp11.hpp"
#ifndef LEAF_91843B04108711E9AA4E56D98C7F4AFC
#define LEAF_91843B04108711E9AA4E56D98C7F4AFC

//  Copyright 2015-2017 Peter Dimov.
//  Copyright 2019 Emil Dotchevski.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

// LEAF needs a few mp11 utilities, which have been copied into the internal
// namespace boost::leaf::leaf_detail_mp11 in order to avoid a dependency
// on the entire mp11 library. The LEAF_USE_MP11 configuration macro
// tells LEAF to not bother and just use <boost/mp11/algorithm.hpp> instead.
#ifdef LEAF_USE_BOOST_MP11

#include <boost/mp11/algorithm.hpp>

namespace boost { namespace leaf { namespace leaf_detail_mp11 = ::boost::mp11; } }

#else

#include <type_traits>
#include <cstddef>

namespace boost { namespace leaf { namespace leaf_detail_mp11 {

// mp_list<T...>
template<class... T> struct mp_list
{
};

// mp_identity
template<class T> struct mp_identity
{
    using type = T;
};

// mp_inherit
template<class... T> struct mp_inherit: T... {};

// mp_if, mp_if_c
namespace detail
{

template<bool C, class T, class... E> struct mp_if_c_impl
{
};

template<class T, class... E> struct mp_if_c_impl<true, T, E...>
{
    using type = T;
};

template<class T, class E> struct mp_if_c_impl<false, T, E>
{
    using type = E;
};

} // namespace detail

template<bool C, class T, class... E> using mp_if_c = typename detail::mp_if_c_impl<C, T, E...>::type;
template<class C, class T, class... E> using mp_if = typename detail::mp_if_c_impl<static_cast<bool>(C::value), T, E...>::type;

// mp_bool
template<bool B> using mp_bool = std::integral_constant<bool, B>;

using mp_true = mp_bool<true>;
using mp_false = mp_bool<false>;

// mp_to_bool
template<class T> using mp_to_bool = mp_bool<static_cast<bool>( T::value )>;

// mp_not<T>
template<class T> using mp_not = mp_bool< !T::value >;

// mp_int
template<int I> using mp_int = std::integral_constant<int, I>;

// mp_size_t
template<std::size_t N> using mp_size_t = std::integral_constant<std::size_t, N>;

// mp_set_contains<S, V>
namespace detail
{

template<class S, class V> struct mp_set_contains_impl;

template<template<class...> class L, class... T, class V> struct mp_set_contains_impl<L<T...>, V>
{
    using type = mp_to_bool<std::is_base_of<mp_identity<V>, mp_inherit<mp_identity<T>...> > >;
};

} // namespace detail

template<class S, class V> using mp_set_contains = typename detail::mp_set_contains_impl<S, V>::type;

// mp_set_push_back<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_back_impl;

template<template<class...> class L, class... U> struct mp_set_push_back_impl<L<U...>>
{
    using type = L<U...>;
};

template<template<class...> class L, class... U, class T1, class... T> struct mp_set_push_back_impl<L<U...>, T1, T...>
{
    using S = mp_if<mp_set_contains<L<U...>, T1>, L<U...>, L<U..., T1>>;
    using type = typename mp_set_push_back_impl<S, T...>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_push_back = typename detail::mp_set_push_back_impl<S, T...>::type;

// mp_unique<L>
namespace detail
{

template<class L> struct mp_unique_impl;

template<template<class...> class L, class... T> struct mp_unique_impl<L<T...>>
{
    using type = mp_set_push_back<L<>, T...>;
};

} // namespace detail

template<class L> using mp_unique = typename detail::mp_unique_impl<L>::type;

// mp_append<L...>

namespace detail
{

template<class... L> struct mp_append_impl;

template<> struct mp_append_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_append_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2, class... Lr> struct mp_append_impl<L1<T1...>, L2<T2...>, Lr...>
{
    using type = typename mp_append_impl<L1<T1..., T2...>, Lr...>::type;
};

}

template<class... L> using mp_append = typename detail::mp_append_impl<L...>::type;

// mp_front<L>
namespace detail
{

template<class L> struct mp_front_impl
{
// An error "no type named 'type'" here means that the argument to mp_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class T1, class... T> struct mp_front_impl<L<T1, T...>>
{
    using type = T1;
};

} // namespace detail

template<class L> using mp_front = typename detail::mp_front_impl<L>::type;

// mp_pop_front<L>
namespace detail
{

template<class L> struct mp_pop_front_impl
{
// An error "no type named 'type'" here means that the argument to mp_pop_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class T1, class... T> struct mp_pop_front_impl<L<T1, T...>>
{
    using type = L<T...>;
};

} // namespace detail

template<class L> using mp_pop_front = typename detail::mp_pop_front_impl<L>::type;

// mp_first<L>
template<class L> using mp_first = mp_front<L>;

// mp_rest<L>
template<class L> using mp_rest = mp_pop_front<L>;

// mp_remove_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_remove_if_impl;

template<template<class...> class L, class... T, template<class...> class P> struct mp_remove_if_impl<L<T...>, P>
{
    template<class U> using _f = mp_if<P<U>, mp_list<>, mp_list<U>>;
    using type = mp_append<L<>, _f<T>...>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_remove_if = typename detail::mp_remove_if_impl<L, P>::type;

// integer_sequence
template<class T, T... I> struct integer_sequence
{
};

// detail::make_integer_sequence_impl
namespace detail
{

// iseq_if_c
template<bool C, class T, class E> struct iseq_if_c_impl;

template<class T, class E> struct iseq_if_c_impl<true, T, E>
{
    using type = T;
};

template<class T, class E> struct iseq_if_c_impl<false, T, E>
{
    using type = E;
};

template<bool C, class T, class E> using iseq_if_c = typename iseq_if_c_impl<C, T, E>::type;

// iseq_identity
template<class T> struct iseq_identity
{
    using type = T;
};

template<class S1, class S2> struct append_integer_sequence;

template<class T, T... I, T... J> struct append_integer_sequence<integer_sequence<T, I...>, integer_sequence<T, J...>>
{
    using type = integer_sequence< T, I..., ( J + sizeof...(I) )... >;
};

template<class T, T N> struct make_integer_sequence_impl;

template<class T, T N> struct make_integer_sequence_impl_
{
private:

    static_assert( N >= 0, "make_integer_sequence<T, N>: N must not be negative" );

    static T const M = N / 2;
    static T const R = N % 2;

    using S1 = typename make_integer_sequence_impl<T, M>::type;
    using S2 = typename append_integer_sequence<S1, S1>::type;
    using S3 = typename make_integer_sequence_impl<T, R>::type;
    using S4 = typename append_integer_sequence<S2, S3>::type;

public:

    using type = S4;
};

template<class T, T N> struct make_integer_sequence_impl: iseq_if_c<N == 0, iseq_identity<integer_sequence<T>>, iseq_if_c<N == 1, iseq_identity<integer_sequence<T, 0>>, make_integer_sequence_impl_<T, N> > >
{
};

} // namespace detail

// make_integer_sequence
template<class T, T N> using make_integer_sequence = typename detail::make_integer_sequence_impl<T, N>::type;

// index_sequence
template<std::size_t... I> using index_sequence = integer_sequence<std::size_t, I...>;

// make_index_sequence
template<std::size_t N> using make_index_sequence = make_integer_sequence<std::size_t, N>;

// index_sequence_for
template<class... T> using index_sequence_for = make_integer_sequence<std::size_t, sizeof...(T)>;

// implementation by Bruno Dutra (by the name is_evaluable)
namespace detail
{

template<template<class...> class F, class... T> struct mp_valid_impl
{
    template<template<class...> class G, class = G<T...>> static mp_true check(int);
    template<template<class...> class> static mp_false check(...);

    using type = decltype(check<F>(0));
};

} // namespace detail

template<template<class...> class F, class... T> using mp_valid = typename detail::mp_valid_impl<F, T...>::type;

} } }

#endif

#endif
// <<< #include <boost/leaf/detail/mp11.hpp>
#line 10 "boost/leaf/detail/function_traits.hpp"
#include <tuple>

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <class...>
		using void_t = void;

		template<class F,class V=void>
		struct function_traits
		{
			constexpr static int arity = -1;
		};

		template<class F>
		struct function_traits<F,void_t<decltype(&F::operator())>>
		{
		private:

			typedef function_traits<decltype(&F::operator())> tr;

		public:

			typedef typename tr::return_type return_type;
			static constexpr int arity = tr::arity - 1;

			using mp_args = typename leaf_detail_mp11::mp_rest<typename tr::mp_args>;

			template <int I>
			struct arg:
				tr::template arg<I+1>
			{
			};
		};

		template<class R, class... A>
		struct function_traits<R(A...)>
		{
			typedef R return_type;
			static constexpr int arity = sizeof...(A);

			using mp_args = leaf_detail_mp11::mp_list<A...>;

			template <int I>
			struct arg
			{
				static_assert(I < arity, "I out of range");
				typedef typename std::tuple_element<I,std::tuple<A...>>::type type;
			};
		};

		template<class F> struct function_traits<F&> : function_traits<F> { };
		template<class F> struct function_traits<F&&> : function_traits<F> { };
		template<class R, class... A> struct function_traits<R(*)(A...)> : function_traits<R(A...)> { };
		template<class R, class... A> struct function_traits<R(* &)(A...)> : function_traits<R(A...)> { };
		template<class R, class... A> struct function_traits<R(* const &)(A...)> : function_traits<R(A...)> { };
		template<class C, class R, class... A> struct function_traits<R(C::*)(A...)> : function_traits<R(C&,A...)> { };
		template<class C, class R, class... A> struct function_traits<R(C::*)(A...) const> : function_traits<R(C const &,A...)> { };
		template<class C, class R> struct function_traits<R(C::*)> : function_traits<R(C&)> { };

		template <class F>
		using fn_return_type = typename function_traits<F>::return_type;

		template <class F, int I>
		using fn_arg_type = typename function_traits<F>::template arg<I>::type;

		template <class F>
		using fn_mp_args = typename function_traits<F>::mp_args;
	} // namespace leaf_detail

} }

#endif
// <<< #include <boost/leaf/detail/function_traits.hpp>
#line 10 "boost/leaf/error.hpp"
// >>> #include <boost/leaf/detail/print.hpp>
#line 1 "boost/leaf/detail/print.hpp"
#ifndef LEAF_3BAB50A2B87E11E89EEB30600C39171A
#define LEAF_3BAB50A2B87E11E89EEB30600C39171A

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/leaf/detail/optional.hpp>
#line 1 "boost/leaf/detail/optional.hpp"
#ifndef LEAF_47258FCCB6B411E8A1F35AA00C39171A
#define LEAF_47258FCCB6B411E8A1F35AA00C39171A

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <utility>
#include <new>
#include <cassert>
#include <ostream>

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <class T>
		class optional
		{
			int key_;
			union { T value_; };

		public:

			typedef T value_type;

			optional() noexcept:
				key_(0)
			{
			}

			optional( optional const & x ):
				key_(x.key_)
			{
				if( x.key_ )
					(void) new (&value_) T( x.value_ );
			}

			optional( optional && x ) noexcept:
				key_(x.key_)
			{
				if( x.key_ )
				{
					(void) new (&value_) T( std::move(x.value_) );
					x.reset();
				}
			}

			optional( int key, T const & v ):
				key_(key),
				value_(v)
			{
				assert(!empty());
			}

			optional( int key, T && v ) noexcept:
				key_(key),
				value_(std::move(v))
			{
				assert(!empty());
			}

			optional & operator=( optional const & x )
			{
				reset();
				if( int key = x.key() )
				{
					put(key, x.value_);
					key_ = key;
				}
				return *this;
			}

			optional & operator=( optional && x ) noexcept
			{
				reset();
				if( int key = x.key() )
				{
					put(key, std::move(x.value_));
					x.reset();
				}
				return *this;
			}

			~optional() noexcept
			{
				reset();
			}

			bool empty() const noexcept
			{
				return key_==0;
			}

			int key() const noexcept
			{
				return key_;
			}

			void set_key( int key ) noexcept
			{
				assert(!empty());
				key_ = key;
			}

			void reset() noexcept
			{
				if( key_ )
				{
					value_.~T();
					key_=0;
				}
			}

			template <class... A>
			T & emplace( int key, A && ... a )
			{
				assert(key);
				reset();
				(void) new(&value_) T(std::forward<A>(a)...);
				key_=key;
				return value_;
			}

			T & put( int key, T const & v )
			{
				assert(key);
				reset();
				(void) new(&value_) T(v);
				key_=key;
				return value_;
			}

			T & put( int key, T && v ) noexcept
			{
				assert(key);
				reset();
				(void) new(&value_) T(std::move(v));
				key_=key;
				return value_;
			}

			T const * has_value(int key) const noexcept
			{
				assert(key);
				return key_==key ? &value_ : 0;
			}

			T * has_value(int key) noexcept
			{
				assert(key);
				return key_==key ? &value_ : 0;
			}

			T const & value(int key) const & noexcept
			{
				assert(has_value(key)!=0);
				return value_;
			}

			T & value(int key) & noexcept
			{
				assert(has_value(key)!=0);
				return value_;
			}

			T const && value(int key) const && noexcept
			{
				assert(has_value(key)!=0);
				return value_;
			}

			T value(int key) && noexcept
			{
				assert(has_value(key)!=0);
				T tmp(std::move(value_));
				reset();
				return tmp;
			}

			void print( std::ostream & ) const;
		};

	} // leaf_detail

} }

#endif
// <<< #include <boost/leaf/detail/optional.hpp>
#line 11 "boost/leaf/detail/print.hpp"
#include <exception>
#include <ostream>
#include <cstring>
#include <cassert>

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <int N>
		inline char const * check_prefix( char const * t, char const (&prefix)[N] )
		{
			return std::strncmp(t,prefix,sizeof(prefix)-1)==0 ? t+sizeof(prefix)-1 : t;
		}
	}

	template <class Name>
	inline char const * type() noexcept
	{
	char const * t =
#ifdef __FUNCSIG__
		__FUNCSIG__;
#else
		__PRETTY_FUNCTION__;
#endif
#if defined(__clang__)
		assert(leaf_detail::check_prefix(t,"const char *boost::leaf::type() ")==t+32);
		return t+32;
#elif defined(__GNUC__)
		assert(leaf_detail::check_prefix(t,"const char* boost::leaf::type() ")==t+32);
		return t+32;
#else
		char const * clang_style = leaf_detail::check_prefix(t,"const char *boost::leaf::type() ");
		if( clang_style!=t )
			return clang_style;
		char const * gcc_style = leaf_detail::check_prefix(t,"const char* boost::leaf::type() ");
		if( gcc_style!=t )
			return gcc_style;
#endif
		return t;
	}

	namespace leaf_detail
	{
		template <class T, class E = void>
		struct is_printable: std::false_type
		{
		};

		template <class T>
		struct is_printable<T, decltype(std::declval<std::ostream&>()<<std::declval<T const &>(), void())>: std::true_type
		{
		};

		////////////////////////////////////////

		template <class T, class E = void>
		struct has_printable_member_value: std::false_type
		{
		};

		template <class T>
		struct has_printable_member_value<T, decltype(std::declval<std::ostream&>()<<std::declval<T const &>().value, void())>: std::true_type
		{
		};

		////////////////////////////////////////

		template <class Wrapper, bool WrapperPrintable=is_printable<Wrapper>::value, bool ValuePrintable=has_printable_member_value<Wrapper>::value>
		struct diagnostic;

		template <class Wrapper, bool ValuePrintable>
		struct diagnostic<Wrapper, true, ValuePrintable>
		{
			static constexpr bool is_invisible = false;
			static void print( std::ostream & os, Wrapper const & x )
			{
				os << x;
			}
		};

		template <class Wrapper>
		struct diagnostic<Wrapper, false, true>
		{
			static constexpr bool is_invisible = false;
			static void print( std::ostream & os, Wrapper const & x )
			{
				os << type<Wrapper>() << ": " << x.value;
			}
		};

		template <class Wrapper>
		struct diagnostic<Wrapper, false, false>
		{
			static constexpr bool is_invisible = false;
			static void print( std::ostream & os, Wrapper const & )
			{
				os << type<Wrapper>() << ": {Non-Printable}";
			}
		};

		template <>
		struct diagnostic<std::exception_ptr, false, false>
		{
			static constexpr bool is_invisible = true;
			static void print( std::ostream &, std::exception_ptr const & )
			{
			}
		};

		template <class T>
		void optional<T>::print( std::ostream & os ) const
		{
			if( int k = key() )
			{
				os << type<T>() << '[' << k << "]: ";
				diagnostic<T>::print(os, value_);
				os << std::endl;
			}
		}
	} // leaf_detail

} }

#endif
// <<< #include <boost/leaf/detail/print.hpp>
#line 11 "boost/leaf/error.hpp"
#include <system_error>
#include <type_traits>
#include <sstream>
#include <memory>
#include <set>

#ifdef LEAF_NO_THREADS
#	define LEAF_THREAD_LOCAL
	namespace boost { namespace leaf {
		namespace leaf_detail
		{
			using atomic_unsigned_int = unsigned int;
		}
	} }
#else
#	include <atomic>
#	include <thread>
#	define LEAF_THREAD_LOCAL thread_local
	namespace boost { namespace leaf {
		namespace leaf_detail
		{
			using atomic_unsigned_int = std::atomic<unsigned int>;
		}
	} }
#endif

#define LEAF_NEW_ERROR(...) ::boost::leaf::leaf_detail::new_error_at(__FILE__,__LINE__,__FUNCTION__).load(__VA_ARGS__)

#define LEAF_AUTO(v,r)\
	static_assert(::boost::leaf::is_result_type<typename std::decay<decltype(r)>::type>::value, "LEAF_AUTO requires a result type");\
	auto && _r_##v = r;\
	if( !_r_##v )\
		return _r_##v.error();\
	auto && v = _r_##v.value()

#define LEAF_CHECK(r)\
	{\
		static_assert(::boost::leaf::is_result_type<typename std::decay<decltype(r)>::type>::value, "LEAF_CHECK requires a result type");\
		auto && _r = r;\
		if( !_r )\
			return _r.error();\
	}

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template<class T> using has_value_impl = decltype( std::declval<T>().value );

		template <class T> using has_value = leaf_detail_mp11::mp_valid<has_value_impl, T>;

		template <class T>
		struct is_error_type_default
		{
			static constexpr bool value = has_value<T>::value || std::is_base_of<std::exception,T>::value;
		};

		template <>
		struct is_error_type_default<std::exception_ptr>: std::true_type
		{
		};
	}

	template <class T> struct is_e_type: leaf_detail::is_error_type_default<T> { };
	template <class T> struct is_e_type<T const>: is_e_type<T> { };
	template <class T> struct is_e_type<T const &>: is_e_type<T> { };
	template <class T> struct is_e_type<T &>: is_e_type<T> { };
	template <> struct is_e_type<std::error_code>: std::false_type { };

	////////////////////////////////////////

	struct e_source_location
	{
		char const * const file;
		int const line;
		char const * const function;

		friend std::ostream & operator<<( std::ostream & os, e_source_location const & x )
		{
			return os << leaf::type<e_source_location>() << ": " << x.file << '(' << x.line << ") in function " << x.function;
		}
	};

	template <>
	struct is_e_type<e_source_location>: std::true_type
	{
	};

	////////////////////////////////////////

	namespace leaf_detail
	{
		class slot_base
		{
			slot_base & operator=( slot_base const & ) = delete;
			slot_base( slot_base const & ) = delete;

#ifndef LEAF_NO_DIAGNOSTIC_INFO
			virtual bool slot_print( std::ostream &, int err_id ) const = 0;
#endif

		public:

#ifndef LEAF_NO_DIAGNOSTIC_INFO
			static void print_all( std::ostream & os, int err_id )
			{
				for( slot_base const * p = first(); p; p=p->next_ )
					if( p->slot_print(os,err_id) )
						os << std::endl;
			}
#endif

		protected:

#ifdef LEAF_NO_DIAGNOSTIC_INFO
			slot_base() noexcept = default;
			slot_base( slot_base && x ) noexcept = default;
			~slot_base() noexcept = default;
			void activate() noexcept { }
			void deactivate() noexcept { }
#else
			static slot_base * & first() noexcept
			{
				static LEAF_THREAD_LOCAL slot_base * p = 0;
				return p;
			}

			slot_base * next_;

			slot_base() noexcept:
				next_(0)
			{
			}

			slot_base( slot_base && x ) noexcept:
				next_(0)
			{
				assert(x.next_==0);
			}

			~slot_base() noexcept
			{
				assert(next_ == 0);
			}

			void activate() noexcept
			{
				assert(next_ == 0);
				slot_base * * f = &first();
				next_ = *f;
				*f = this;
			}

			void deactivate() noexcept
			{
				slot_base * * f = &first();
				assert(*f == this);
				*f = next_;
				next_ = 0;
			}
#endif
		};
	}

	////////////////////////////////////////

#ifndef LEAF_DISCARD_UNEXPECTED

	namespace leaf_detail
	{
		class e_unexpected_count
		{
		public:

			char const * (*first_type)();
			int count;

			explicit e_unexpected_count( char const * (*first_type)() ) noexcept:
				first_type(first_type),
				count(1)
			{
			}

			void print( std::ostream & os ) const
			{
				assert(first_type!=0);
				assert(count>0);
				os << "Detected ";
				if( count==1 )
					os << "1 attempt to communicate an E-object";
				else
					os << count << " attempts to communicate unexpected E-objects, the first one";
				os << " of type " << first_type() << std::endl;
			}
		};

		template <>
		struct is_error_type_default<e_unexpected_count>: std::true_type
		{
		};

		template <>
		struct diagnostic<e_unexpected_count,false,false>
		{
			static constexpr bool is_invisible = true;
			static void print( std::ostream &, e_unexpected_count const & ) noexcept
			{
			}
		};

		class e_unexpected_info
		{
			std::string s_;
			std::set<char const *(*)()> already_;

		public:

			e_unexpected_info() noexcept
			{
			}

			void reset() noexcept
			{
				s_.clear();
				already_.clear();
			}

			template <class E>
			void add( E const & e )
			{
				std::stringstream s;
				if( !leaf_detail::diagnostic<E>::is_invisible )
				{
					leaf_detail::diagnostic<E>::print(s,e);
					if( already_.insert(&type<E>).second  )
					{
						s << std::endl;
						s_ += s.str();
					}
				}
			}

			void print( std::ostream & os ) const
			{
				os << s_;
			}
		};

		template <>
		struct is_error_type_default<e_unexpected_info>: std::true_type
		{
		};

		template <>
		struct diagnostic<e_unexpected_info,false,false>
		{
			static constexpr bool is_invisible = true;
			static void print( std::ostream &, e_unexpected_info const & ) noexcept
			{
			}
		};
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		inline int & tl_unexpected_enabled_counter() noexcept
		{
			static LEAF_THREAD_LOCAL int c;
			return c;
		}
	}

#endif

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class E>
		class slot;

		template <class E>
		inline slot<E> * & tl_slot_ptr() noexcept
		{
			static LEAF_THREAD_LOCAL slot<E> * s;
			return s;
		}

		template <class E>
		class slot:
			slot_base,
			optional<E>
		{
			slot( slot const & ) = delete;
			slot & operator=( slot const & ) = delete;

			typedef optional<E> impl;
			slot<E> * * top_;
			slot<E> * prev_;
			static_assert(is_e_type<E>::value,"Not an error type");

#ifndef LEAF_NO_DIAGNOSTIC_INFO
			bool slot_print( std::ostream & os, int err_id ) const final override
			{
				if( !diagnostic<E>::is_invisible && *top_==this )
					if( E const * e = has_value(err_id) )
					{
						assert((err_id&3)==1);
						diagnostic<decltype(*e)>::print(os, *e);
						return true;
					}
				return false;
			}
#endif

		public:

			slot() noexcept:
				top_(0)
			{
			}

			slot( slot && x ) noexcept:
				slot_base(std::move(x)),
				optional<E>(std::move(x)),
				top_(0)
			{
				assert(x.top_==0);
			}

			~slot() noexcept
			{
				assert(top_==0);
			}

			void activate() noexcept
			{
				assert(top_==0);
				slot_base::activate();
				top_ = &tl_slot_ptr<E>();
				prev_ = *top_;
				*top_ = this;
			}

			void deactivate( bool propagate_errors ) noexcept;

			using impl::put;
			using impl::has_value;
			using impl::value;
			using impl::print;
		};

#ifndef LEAF_DISCARD_UNEXPECTED

		template <class E>
		inline void load_unexpected_count( int err_id ) noexcept
		{
			if( slot<e_unexpected_count> * sl = tl_slot_ptr<e_unexpected_count>() )
				if( e_unexpected_count * unx = sl->has_value(err_id) )
					++unx->count;
				else
					sl->load(err_id, e_unexpected_count(&type<E>));
		}

		template <class E>
		inline void load_unexpected_info( int err_id, E && e ) noexcept
		{
			if( slot<e_unexpected_info> * sl = tl_slot_ptr<e_unexpected_info>() )
				if( e_unexpected_info * unx = sl->has_value(err_id) )
					unx->add(e);
				else
					sl->load(err_id, e_unexpected_info()).add(e);
		}

		template <class E>
		inline void no_expect_slot( int err_id, E && e  ) noexcept
		{
			load_unexpected_count<E>(err_id);
			load_unexpected_info(err_id, std::move(e));
		}

#endif

		template <class E>
		inline void slot<E>::deactivate( bool propagate_errors ) noexcept
		{
			assert(top_!=0);
			if( propagate_errors )
				if( prev_ )
				{
					impl & this_ = *this;
					impl & that_ = *prev_;
					that_ = std::move(this_);
				}
#ifndef LEAF_DISCARD_UNEXPECTED
				else
				{
					int c = tl_unexpected_enabled_counter();
					assert(c>=0);
					if( c )
						if( int err_id = impl::key() )
							no_expect_slot(err_id, std::move(*this).value(err_id));
				}
#endif
			*top_ = prev_;
			top_ = 0;
			slot_base::deactivate();
		}

		template <class E>
		inline int load_slot( int err_id, E && e ) noexcept
		{
			using T = typename std::decay<E>::type;
			assert((err_id&3)==1);
			if( slot<T> * p = tl_slot_ptr<T>() )
				(void) p->put(err_id, std::forward<E>(e));
#ifndef LEAF_DISCARD_UNEXPECTED
			else
			{
				int c = tl_unexpected_enabled_counter();
				assert(c>=0);
				if( c )
					no_expect_slot(err_id, std::forward<E>(e));
			}
#endif
			return 0;
		}

		template <class F>
		inline int accumulate_slot( int err_id, F && f ) noexcept
		{
			static_assert(function_traits<F>::arity==1, "Lambdas passed to accumulate must take a single e-type argument by reference");
			using E = typename std::decay<fn_arg_type<F,0>>::type;
			static_assert(is_e_type<E>::value, "Lambdas passed to accumulate must take a single e-type argument by reference");
			assert((err_id&3)==1);
			if( auto sl = tl_slot_ptr<E>() )
				if( auto v = sl->has_value(err_id) )
					(void) std::forward<F>(f)(*v);
				else
					(void) std::forward<F>(f)(sl->put(err_id,E()));
			return 0;
		}
	} // leaf_detail

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class=void>
		struct id_factory
		{
			static atomic_unsigned_int counter;
			static LEAF_THREAD_LOCAL int last_id;
			static LEAF_THREAD_LOCAL int next_id;

			static int generate_next_id() noexcept
			{
				unsigned id = ((counter+=4) & ~3) | 1;
				assert((id&3)==1);
				return id;
			}
		};

		template <class T>
		atomic_unsigned_int id_factory<T>::counter(-3);

		template <class T>
		LEAF_THREAD_LOCAL int id_factory<T>::last_id(0);

		template <class T>
		LEAF_THREAD_LOCAL int id_factory<T>::next_id(0);

		inline int last_id() noexcept
		{
			int id = id_factory<>::last_id;
			assert(id==0 || ((id&3)==1));
			return id;
		}

		inline int next_id() noexcept
		{
			if( int id = id_factory<>::next_id )
			{
				assert((id&3)==1);
				return id;
			}
			else
				return id_factory<>::next_id = id_factory<>::generate_next_id();
		}

		inline int new_id() noexcept
		{
			if( int id = id_factory<>::next_id )
			{
				assert((id&3)==1);
				id_factory<>::next_id = 0;
				return id_factory<>::last_id = id;
			}
			else
				return id_factory<>::last_id = id_factory<>::generate_next_id();
		}
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		struct e_original_ec { std::error_code value; };

		class leaf_category: public std::error_category
		{
			bool equivalent( int,  std::error_condition const & ) const noexcept final override { return false; }
			bool equivalent( std::error_code const &, int ) const noexcept final override { return false; }
			char const * name() const noexcept final override { return "LEAF error"; }
			std::string message( int condition ) const final override { return name(); }
		public:
			~leaf_category() noexcept final override { }
		};

		template <class=void>
		struct get_error_category
		{
			static leaf_category cat;
		};

		template <class T>
		leaf_category get_error_category<T>::cat;

		inline int import_error_code( std::error_code const & ec ) noexcept
		{
			if( int err_id = ec.value() )
			{
				std::error_category const & cat = leaf_detail::get_error_category<>::cat;
				if( &ec.category()==&cat )
				{
					assert((err_id&3)==1);
					return err_id;
				}
				else
				{
					err_id = leaf_detail::new_id();
					leaf_detail::load_slot(err_id, leaf_detail::e_original_ec{ec});
					return err_id;
				}
			}
			else
				return 0;
		}

		inline bool is_error_id( std::error_code const & ec ) noexcept
		{
			bool res = (&ec.category() == &leaf_detail::get_error_category<>::cat);
			assert(!res || !ec.value() || ((ec.value()&3)==1));
			return res;
		}
}

	////////////////////////////////////////

	class error_id;

	namespace leaf_detail
	{
		error_id make_error_id(int) noexcept;
	}

	class error_id
	{
		friend error_id leaf_detail::make_error_id(int ) noexcept;

		int value_;

		explicit error_id( int value ) noexcept:
			value_(value)
		{
			assert(value_==0 || ((value_&3)==1));
		}

	public:

		error_id() noexcept:
			value_(0)
		{
		}

		error_id( std::error_code const & ec ) noexcept:
			value_(leaf_detail::import_error_code(ec))
		{
			assert(!value_ || ((value_&3)==1));
		}

		error_id load() const noexcept
		{
			return *this;
		}

		template <class... E>
		error_id load( E && ... e ) const noexcept
		{
			if( int err_id = value() )
			{
				auto _ = { leaf_detail::load_slot(err_id, std::forward<E>(e))... };
				(void) _;
			}
			return *this;
		}

		error_id accumulate() const noexcept
		{
			return *this;
		}

		template <class... F>
		error_id accumulate( F && ... f ) const noexcept
		{
			if( int err_id = value() )
			{
				auto _ = { leaf_detail::accumulate_slot(err_id, std::forward<F>(f))... };
				(void) _;
			}
			return *this;
		}

		template<class T, class E = typename std::enable_if<
			std::is_nothrow_constructible<T, std::error_code>::value &&
			std::is_convertible<std::error_code, T>::value
			>::type>
		operator T() const noexcept
		{
			return std::error_code(value(), leaf_detail::get_error_category<>::cat);
		}

		int value() const noexcept
		{
			assert(!value_ || ((value_&3)==1));
			return value_;
		}

		explicit operator bool() const noexcept
		{
			return value()!=0;
		}

		friend bool operator==( error_id a, error_id b ) noexcept
		{
			return a.value()==b.value();
		}

		friend bool operator!=( error_id a, error_id b ) noexcept
		{
			return !(a==b);
		}

		friend bool operator<( error_id a, error_id b ) noexcept
		{
			return a.value()<b.value();
		}

		friend std::ostream & operator<<( std::ostream & os, error_id x )
		{
			return os<<x.value();
		}
	};

	namespace leaf_detail
	{
		inline error_id make_error_id( int err_id ) noexcept
		{
			return error_id(err_id);
		}
	}

	inline error_id new_error() noexcept
	{
		return leaf_detail::make_error_id(leaf_detail::new_id());
	}

	template <class E1, class... E>
	inline typename std::enable_if<is_e_type<E1>::value, error_id>::type new_error( E1 && e1, E && ... e ) noexcept
	{
		return leaf_detail::make_error_id(leaf_detail::new_id()).load(std::forward<E1>(e1), std::forward<E>(e)...);
	}

	template <class E1, class... E>
	inline typename std::enable_if<std::is_same<std::error_code, decltype(make_error_code(std::declval<E1>()))>::value, error_id>::type new_error( E1 const & e1, E && ... e ) noexcept
	{
		return error_id(make_error_code(e1)).load(std::forward<E>(e)...);
	}

	inline error_id next_error() noexcept
	{
		return leaf_detail::make_error_id(leaf_detail::next_id());
	}

	namespace leaf_detail
	{
		template <class... E>
		inline error_id new_error_at( char const * file, int line, char const * function ) noexcept
		{
			assert(file&&*file);
			assert(line>0);
			assert(function&&*function);
			e_source_location sl { file, line, function }; // Temp object MSVC workaround
			return new_error(std::move(sl));
		}
	}

	////////////////////////////////////////////

	class polymorphic_context
	{
	protected:
		polymorphic_context() noexcept = default;
		~polymorphic_context() noexcept = default;
	public:
		virtual error_id propagate_captured_errors() noexcept = 0;
		virtual void activate() noexcept = 0;
		virtual void deactivate( bool propagate_errors ) noexcept = 0;
		virtual bool is_active() const noexcept = 0;
		virtual void print( std::ostream & ) const = 0;
		error_id captured_id_;
	};

	using context_ptr = std::shared_ptr<polymorphic_context>;

	////////////////////////////////////////////

	enum class on_deactivation
	{
		propagate,
		do_not_propagate,
		propagate_if_uncaught_exception
	};

	template <class Ctx>
	class context_activator
	{
		context_activator( context_activator const & ) = delete;
		context_activator & operator=( context_activator const & ) = delete;

		Ctx * ctx_;
		bool const ctx_was_active_;
		on_deactivation on_deactivate_;

	public:

		context_activator(Ctx & ctx, on_deactivation on_deactivate) noexcept:
			ctx_(&ctx),
			ctx_was_active_(ctx.is_active()),
			on_deactivate_(on_deactivate)
		{
			if( !ctx_was_active_ )
				ctx.activate();
		}

		context_activator( context_activator && x ) noexcept:
			ctx_(x.ctx_),
			ctx_was_active_(x.ctx_was_active_),
			on_deactivate_(x.on_deactivate_)
		{
			x.ctx_ = 0;
		}

		~context_activator() noexcept
		{
			if( ctx_ )
			{
				assert(
					on_deactivate_ == on_deactivation::propagate ||
					on_deactivate_ == on_deactivation::do_not_propagate ||
					on_deactivate_ == on_deactivation::propagate_if_uncaught_exception);
				if( !ctx_was_active_ )
					if( on_deactivate_ == on_deactivation::propagate_if_uncaught_exception )
					{
#ifdef LEAF_NO_EXCEPTIONS
						ctx_->deactivate(false);
#else
						bool has_exception = std::uncaught_exception();
						ctx_->deactivate(has_exception);
						if( !has_exception )
							(void) leaf_detail::new_id();
#endif
					}
					else
						ctx_->deactivate(on_deactivate_ == on_deactivation::propagate);
			}
		}

		void set_on_deactivate( on_deactivation on_deactivate ) noexcept
		{
			on_deactivate_ = on_deactivate;
		}
	};

	template <class Ctx>
	context_activator<Ctx> activate_context( Ctx & ctx, on_deactivation on_deactivate ) noexcept
	{
		return context_activator<Ctx>(ctx, on_deactivate);
	}

	////////////////////////////////////////////

	template <class R>
	struct is_result_type: std::false_type
	{
	};

	namespace leaf_detail
	{
		template <class R, bool IsResult = is_result_type<R>::value>
		struct is_result_tag;

		template <class R>
		struct is_result_tag<R, false>
		{
		};

		template <class R>
		struct is_result_tag<R, true>
		{
		};
	}

} }

#undef LEAF_THREAD_LOCAL

#endif
// <<< #include <boost/leaf/error.hpp>
#line 10 "boost/leaf/exception.hpp"
#include <exception>

#define LEAF_EXCEPTION(...) ::boost::leaf::leaf_detail::exception_at(__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LEAF_THROW(...) ::boost::leaf::throw_exception(LEAF_EXCEPTION(__VA_ARGS__))

#ifdef LEAF_NO_EXCEPTIONS

namespace boost
{
	[[noreturn]] void throw_exception( std::exception const & ); // user defined
}

namespace boost { namespace leaf {

	template <class T>
	[[noreturn]] void throw_exception( T const & e )
	{
		::boost::throw_exception(e);
	}

} }

#else

namespace boost { namespace leaf {

	template <class T>
	[[noreturn]] void throw_exception( T const & e )
	{
		throw e;
	}

} }

#endif

////////////////////////////////////////

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		inline void enforce_std_exception( std::exception const & ) noexcept { }

		template <class Ex>
		class exception:
			public Ex,
			public error_id
		{
		public:

			exception( exception const & ) = default;
			exception( exception && ) = default;

			template <class... E>
			exception( Ex && ex, E && ... e ) noexcept:
				Ex(std::move(ex)),
				error_id(new_error(std::forward<E>(e)...))
			{
				leaf_detail::enforce_std_exception(*this);
			}
		};

		template <class Ex, class... E>
		inline exception<Ex> exception_at( char const * file, int line, char const * function, Ex && ex, E && ... e ) noexcept
		{
			assert(file&&*file);
			assert(line>0);
			assert(function&&*function);
			return exception<Ex>( std::forward<Ex>(ex), e_source_location{file,line,function}, std::forward<E>(e)... );
		}
	}

	template <class Ex, class... E>
	inline leaf_detail::exception<Ex> exception( Ex && ex, E && ... e ) noexcept
	{
		return leaf_detail::exception<Ex>( std::forward<Ex>(ex), std::forward<E>(e)... );
	}

} }

#endif
// <<< #include <boost/leaf/exception.hpp>
#line 10 "boost/leaf/capture.hpp"
#include <memory>

namespace boost { namespace leaf {

#ifndef LEAF_NO_EXCEPTIONS

	namespace leaf_detail
	{
		class capturing_exception:
			public std::exception
		{
			std::exception_ptr ex_;
			context_ptr ctx_;

		public:

			capturing_exception(std::exception_ptr && ex, context_ptr && ctx) noexcept:
				ex_(std::move(ex)),
				ctx_(std::move(ctx))
			{
				assert(ex_);
				assert(ctx_);
			}

			[[noreturn]] void unload_and_rethrow_original_exception() const
			{
				auto active_context = activate_context(*ctx_, on_deactivation::propagate);
				std::rethrow_exception(ex_);
			}

			void print( std::ostream & os ) const
			{
				ctx_->print(os);
			}
		};

		template <class R, class F, class... A>
		inline decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...)) capture_impl(is_result_tag<R, false>, context_ptr && ctx, F && f, A... a)
		{
			auto active_context = activate_context(*ctx, on_deactivation::do_not_propagate);
			try
			{
				return std::forward<F>(f)(std::forward<A>(a)...);
			}
			catch( capturing_exception const & )
			{
				throw;
			}
			catch(...)
			{
				throw_exception( capturing_exception(std::current_exception(), std::move(ctx)) );
			}
		}

		template <class R, class F, class... A>
		inline decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...)) capture_impl(is_result_tag<R, true>, context_ptr && ctx, F && f, A... a)
		{
			auto active_context = activate_context(*ctx, on_deactivation::do_not_propagate);
			try
			{
				if( auto r = std::forward<F>(f)(std::forward<A>(a)...) )
					return r;
				else
				{
					ctx->captured_id_ = r.error();
					return std::move(ctx);
				}
			}
			catch( capturing_exception const & )
			{
				throw;
			}
			catch(...)
			{
				throw_exception( capturing_exception(std::current_exception(), std::move(ctx)) );
			}
		}
	}

#else

	namespace leaf_detail
	{
		template <class R, class F, class... A>
		inline decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...)) capture_impl(is_result_tag<R, false>, context_ptr && ctx, F && f, A... a)
		{
			auto active_context = activate_context(*ctx, on_deactivation::do_not_propagate);
			return std::forward<F>(f)(std::forward<A>(a)...);
		}

		template <class R, class F, class... A>
		inline decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...)) capture_impl(is_result_tag<R, true>, context_ptr && ctx, F && f, A... a)
		{
			auto active_context = activate_context(*ctx, on_deactivation::do_not_propagate);
			if( auto r = std::forward<F>(f)(std::forward<A>(a)...) )
				return r;
			else
			{
				ctx->captured_id_ = r.error();
				return std::move(ctx);
			}
		}
	}

#endif

	template <class F, class... A>
	inline decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...)) capture(context_ptr && ctx, F && f, A... a)
	{
		using namespace leaf_detail;
		return capture_impl(is_result_tag<decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...))>(), std::move(ctx), std::forward<F>(f), std::forward<A>(a)...);
	}

	////////////////////////////////////////

#ifndef LEAF_NO_EXCEPTIONS

	template <class T>
	class result;

	namespace leaf_detail
	{
		inline error_id catch_exceptions_helper( std::exception const & ex, leaf_detail_mp11::mp_list<> )
		{
			return leaf::new_error(std::current_exception());
		}

		template <class Ex1, class... Ex>
		inline error_id catch_exceptions_helper( std::exception const & ex, leaf_detail_mp11::mp_list<Ex1,Ex...> )
		{
			if( Ex1 const * p = dynamic_cast<Ex1 const *>(&ex) )
				return catch_exceptions_helper(ex, leaf_detail_mp11::mp_list<Ex...>{ }).load(*p);
			else
				return catch_exceptions_helper(ex, leaf_detail_mp11::mp_list<Ex...>{ });
		}

		template <class T>
		struct deduce_exception_to_result_return_type_impl
		{
			using type = result<T>;
		};

		template <class T>
		struct deduce_exception_to_result_return_type_impl<result<T>>
		{
			using type = result<T>;
		};

		template <class T>
		using deduce_exception_to_result_return_type = typename deduce_exception_to_result_return_type_impl<T>::type;
	}

	template <class... Ex, class F>
	inline leaf_detail::deduce_exception_to_result_return_type<leaf_detail::fn_return_type<F>> exception_to_result( F && f ) noexcept
	{
		try
		{
			return std::forward<F>(f)();
		}
		catch( std::exception const & ex )
		{
			return leaf_detail::catch_exceptions_helper(ex, leaf_detail_mp11::mp_list<Ex...>());
		}
		catch(...)
		{
			return leaf::new_error(std::current_exception());
		}
	};

#endif

} }

#endif
// <<< #include <boost/leaf/capture.hpp>
#line 11 "../../include/boost/leaf/detail/all.hpp"
// >>> #include <boost/leaf/common.hpp>
#line 1 "boost/leaf/common.hpp"
#ifndef LEAF_EBA7EF10B6F311E8AAD493990D39171A
#define LEAF_EBA7EF10B6F311E8AAD493990D39171A

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <cerrno>
#include <cassert>
#ifdef _WIN32
#include <Windows.h>
#include <cstring>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#endif

namespace boost { namespace leaf {

	struct e_api_function { char const * value; };

	struct e_file_name { std::string value; };

	struct e_errno
	{
		int value;

		friend std::ostream & operator<<( std::ostream & os, e_errno const & err )
		{
			return os << type<e_errno>() << ": " << err.value << ", \"" << std::strerror(err.value) << '"';
		}
	};

	struct e_type_info_name { char const * value; };

	struct e_at_line { int value; };

	namespace windows
	{
		struct e_LastError
		{
			unsigned value;

#ifdef _WIN32
			friend std::ostream & operator<<( std::ostream & os, e_LastError const & err )
			{
				struct msg_buf
				{
					LPVOID * p;
					msg_buf(): p(0) { }
					~msg_buf() noexcept { if(p) LocalFree(p); }
				};
				msg_buf mb;
				if( FormatMessageA(
					FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
					0,
					err.value,
					MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
					(LPSTR)&mb.p,
					0,
					0) )
				{
					assert(mb.p!=0);
					char * z = std::strchr((LPSTR)mb.p,0);
					if( z[-1] == '\n' )
						*--z = 0;
					if( z[-1] == '\r' )
						*--z = 0;
					return os << type<e_LastError>() << ": " << err.value << ", \"" << (LPCSTR)mb.p << '"';
				}
				return os;
			}
#else
			// TODO : Other platforms
#endif
		};
	}

} }

#endif
// <<< #include <boost/leaf/common.hpp>
#line 12 "../../include/boost/leaf/detail/all.hpp"
// >>> #include <boost/leaf/context.hpp>
#line 1 "boost/leaf/context.hpp"
#ifndef LEAF_E72958AC28C711E9998B3465EBB1FB94
#define LEAF_E72958AC28C711E9998B3465EBB1FB94

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <int I, class Tuple>
		struct tuple_for_each
		{
			static void activate( Tuple & tup ) noexcept
			{
				tuple_for_each<I-1,Tuple>::activate(tup);
				std::get<I-1>(tup).activate();
			}

			static void deactivate( Tuple & tup, bool propagate_errors ) noexcept
			{
				std::get<I-1>(tup).deactivate(propagate_errors);
				tuple_for_each<I-1,Tuple>::deactivate(tup, propagate_errors);
			}

			static void propagate( Tuple & tup, int err_id ) noexcept
			{
				auto & sl = std::get<I-1>(tup);
				if( sl.has_value(err_id) )
					leaf_detail::load_slot(err_id, std::move(sl).value(err_id));
				tuple_for_each<I-1,Tuple>::propagate(tup, err_id);
			}

			static void print( std::ostream & os, Tuple const & tup ) noexcept
			{
				tuple_for_each<I-1,Tuple>::print(os, tup);
				std::get<I-1>(tup).print(os);
			}
		};

		template <class Tuple>
		struct tuple_for_each<0, Tuple>
		{
			static void activate( Tuple & ) noexcept { }
			static void deactivate( Tuple &, bool ) noexcept { }
			static void propagate( Tuple & tup, int ) noexcept { }
			static void print( std::ostream &, Tuple const & ) noexcept { }
		};
	}

	////////////////////////////////////////////

	namespace leaf_detail
	{
		class e_unexpected_count;
		class e_unexpected_info;

		template <class T> struct requires_unexpected { constexpr static bool value = false; };
		template <class T> struct requires_unexpected<T const> { constexpr static bool value = requires_unexpected<T>::value; };
		template <class T> struct requires_unexpected<T const &> { constexpr static bool value = requires_unexpected<T>::value; };
		template <class T> struct requires_unexpected<T const *> { constexpr static bool value = requires_unexpected<T>::value; };
		template <> struct requires_unexpected<e_unexpected_count> { constexpr static bool value = true; };
		template <> struct requires_unexpected<e_unexpected_info> { constexpr static bool value = true; };

		template <class L>
		struct unexpected_requested;

		template <template <class ...> class L>
		struct unexpected_requested<L<>>
		{
			constexpr static bool value = false;
		};

		template <template <class...> class L, template <class> class S, class Car, class... Cdr>
		struct unexpected_requested<L<S<Car>, S<Cdr>...>>
		{
			constexpr static bool value = requires_unexpected<Car>::value || unexpected_requested<L<S<Cdr>...>>::value;
		};
	}

	////////////////////////////////////////////

	class error_info;
	class diagnostic_info;
	class verbose_diagnostic_info;

	namespace leaf_detail
	{
		template <class T> struct translate_type_impl { using type = T; };
		template <class T> struct translate_type_impl<T const> { using type = T; };
		template <class T> struct translate_type_impl<T const *> { using type = T; };
		template <class T> struct translate_type_impl<T const &> { using type = T; };

		template <> struct translate_type_impl<diagnostic_info>;
		template <> struct translate_type_impl<diagnostic_info const>;
		template <> struct translate_type_impl<diagnostic_info const *>;
		template <> struct translate_type_impl<diagnostic_info const &> { using type = e_unexpected_count; };

		template <> struct translate_type_impl<verbose_diagnostic_info>;
		template <> struct translate_type_impl<verbose_diagnostic_info const>;
		template <> struct translate_type_impl<verbose_diagnostic_info const *>;
		template <> struct translate_type_impl<verbose_diagnostic_info const &> { using type = e_unexpected_info; };

		struct e_original_ec;
		template <> struct translate_type_impl<std::error_code> { using type = e_original_ec; };
		template <> struct translate_type_impl<std::error_code const> { using type = e_original_ec; };
		template <> struct translate_type_impl<std::error_code const *> { using type = e_original_ec; };
		template <> struct translate_type_impl<std::error_code const &> { using type = e_original_ec; };

		template <class T>
		using translate_type = typename translate_type_impl<T>::type;

		template <class... T>
		struct translate_list_impl;

		template <template<class...> class L, class... T>
		struct translate_list_impl<L<T...>>
		{
			using type = leaf_detail_mp11::mp_list<translate_type<T>...>;
		};

		template <class L> using translate_list = typename translate_list_impl<L>::type;

		template <class T> struct does_not_participate_in_context_deduction: std::false_type { };
		template <> struct does_not_participate_in_context_deduction<error_info>: std::true_type { };
		template <> struct does_not_participate_in_context_deduction<std::error_code>: std::true_type { };
		template <> struct does_not_participate_in_context_deduction<void>: std::true_type { };
#ifdef LEAF_DISCARD_UNEXPECTED
		template <> struct does_not_participate_in_context_deduction<e_unexpected_count>: std::true_type { };
		template <> struct does_not_participate_in_context_deduction<e_unexpected_info>: std::true_type { };
#endif

		template <class L>
		struct transform_e_type_list_impl;

		template <template<class...> class L, class... T>
		struct transform_e_type_list_impl<L<T...>>
		{
			using type =
				leaf_detail_mp11::mp_remove_if<
					leaf_detail_mp11::mp_unique<
						translate_list<L<T...>>
					>,
					does_not_participate_in_context_deduction
				>;
		};

		template <class L> using transform_e_type_list = typename transform_e_type_list_impl<L>::type;

		template <class L>
		struct deduce_e_tuple_impl;

		template <template <class...> class L, class... E>
		struct deduce_e_tuple_impl<L<E...>>
		{
			using type = std::tuple<slot<E>...>;
		};

		template <class... E>
		using deduce_e_tuple = typename deduce_e_tuple_impl<leaf_detail::transform_e_type_list<leaf_detail_mp11::mp_list<E...>>>::type;
	}

	////////////////////////////////////////////

	template <class... Ex>
	class catch_;

	template <class TryBlock, class... H>
	decltype(std::declval<TryBlock>()()) try_catch( TryBlock &&, H && ... );

	template <class TryBlock, class RemoteH>
	decltype(std::declval<TryBlock>()()) remote_try_catch( TryBlock &&, RemoteH && );

	namespace leaf_detail
	{
		template <class... E>
		class context_base
		{
			context_base( context_base const & ) = delete;
			context_base & operator=( context_base const & ) = delete;

			template <class TryBlock, class... H>
			friend decltype(std::declval<TryBlock>()()) leaf::try_catch( TryBlock &&, H && ... );

			template <class TryBlock, class RemoteH>
			friend decltype(std::declval<TryBlock>()()) leaf::remote_try_catch( TryBlock &&, RemoteH && );

		public:

			using Tup = leaf_detail::deduce_e_tuple<E...>;

		private:

			Tup tup_;
#if !defined(LEAF_NO_THREADS) && !defined(NDEBUG)
			std::thread::id thread_id_;
#endif
			bool is_active_;

		public:

			context_base() noexcept:
				is_active_(false)
			{
			}

			context_base( context_base && x ) noexcept:
				tup_(std::move(x.tup_)),
				is_active_(false)
			{
				assert(!x.is_active());
			}

			~context_base() noexcept
			{
				assert(!is_active());
			}

			Tup const & tup() const noexcept
			{
				return tup_;
			}

			void activate() noexcept
			{
				using namespace leaf_detail;
				assert(!is_active());
				tuple_for_each<std::tuple_size<Tup>::value,Tup>::activate(tup_);
#ifndef LEAF_DISCARD_UNEXPECTED
				if( unexpected_requested<Tup>::value )
					++tl_unexpected_enabled_counter();
#endif
#if !defined(LEAF_NO_THREADS) && !defined(NDEBUG)
				thread_id_ = std::this_thread::get_id();
#endif
				is_active_ = true;
			}

			void deactivate( bool propagate_errors ) noexcept
			{
				using namespace leaf_detail;
				assert(is_active());
				is_active_ = false;
#if !defined(LEAF_NO_THREADS) && !defined(NDEBUG)
				assert(std::this_thread::get_id() == thread_id_);
				thread_id_ = std::thread::id();
#endif
#ifndef LEAF_DISCARD_UNEXPECTED
				if( unexpected_requested<Tup>::value )
					--tl_unexpected_enabled_counter();
#endif
				tuple_for_each<std::tuple_size<Tup>::value,Tup>::deactivate(tup_, propagate_errors);
			}

			bool is_active() const noexcept
			{
				return is_active_;
			}

			void print( std::ostream & os ) const
			{
				leaf_detail::tuple_for_each<std::tuple_size<Tup>::value,Tup>::print(os, tup_);
			}

		protected:

			error_id propagate_captured_errors( error_id err_id ) noexcept
			{
				tuple_for_each<std::tuple_size<Tup>::value,Tup>::propagate(tup_, err_id.value());
				return err_id;
			}

			template <class TryBlock, class... H>
			typename std::decay<decltype(std::declval<TryBlock>()().value())>::type try_handle_all_( TryBlock &&, H && ... ) const;

			template <class TryBlock, class RemoteH>
			typename std::decay<decltype(std::declval<TryBlock>()().value())>::type remote_try_handle_all_( TryBlock &&, RemoteH && ) const;

			template <class TryBlock, class... H, class Ctx>
			typename std::decay<decltype(std::declval<TryBlock>()())>::type try_handle_some_( context_activator<Ctx> &, TryBlock &&, H && ... ) const;

			template <class TryBlock, class RemoteH, class Ctx>
			typename std::decay<decltype(std::declval<TryBlock>()())>::type remote_try_handle_some_( context_activator<Ctx> &, TryBlock &&, RemoteH && ) const;

		public:

			template <class R, class... H>
			typename std::decay<decltype(std::declval<R>().value())>::type handle_all( R &, H && ... ) const;

			template <class R, class RemoteH>
			typename std::decay<decltype(std::declval<R>().value())>::type remote_handle_all( R &, RemoteH && ) const;

			template <class R, class... H>
			R handle_some( R &&, H && ... ) const;

			template <class R, class RemoteH>
			R remote_handle_some( R &&, RemoteH && ) const;

			template <class TryBlock, class... H>
			decltype(std::declval<TryBlock>()()) try_catch_( TryBlock &&, H && ... ) const;

			template <class TryBlock, class RemoteH>
			decltype(std::declval<TryBlock>()()) remote_try_catch_( TryBlock &&, RemoteH && ) const;

			template <class R, class... H>
			R handle_current_exception( H && ... ) const;

			template <class R, class RemoteH>
			R remote_handle_current_exception( RemoteH && ) const;

			template <class R, class... H>
			R handle_exception( std::exception_ptr const &, H && ... ) const;

			template <class R, class RemoteH>
			R remote_handle_exception( std::exception_ptr const &, RemoteH &&  ) const;
		};

		template <class... E>
		class nocatch_context: public context_base<E...>
		{
		public:

			template <class TryBlock, class... H>
			typename std::decay<decltype(std::declval<TryBlock>()().value())>::type try_handle_all( TryBlock &&, H && ... );

			template <class TryBlock, class RemoteH>
			typename std::decay<decltype(std::declval<TryBlock>()().value())>::type remote_try_handle_all( TryBlock &&, RemoteH && );

			template <class TryBlock, class... H>
			typename std::decay<decltype(std::declval<TryBlock>()())>::type try_handle_some( TryBlock &&, H && ... );

			template <class TryBlock, class RemoteH>
			typename std::decay<decltype(std::declval<TryBlock>()())>::type remote_try_handle_some( TryBlock &&, RemoteH && );
		};

		template <class... E>
		class catch_context: public context_base<E...>
		{
		public:

			template <class TryBlock, class... H>
			typename std::decay<decltype(std::declval<TryBlock>()().value())>::type try_handle_all( TryBlock && try_block, H && ... h );

			template <class TryBlock, class RemoteH>
			typename std::decay<decltype(std::declval<TryBlock>()().value())>::type remote_try_handle_all( TryBlock && try_block, RemoteH && h );

			template <class TryBlock, class... H>
			typename std::decay<decltype(std::declval<TryBlock>()())>::type try_handle_some( TryBlock && try_block, H && ... h );

			template <class TryBlock, class RemoteH>
			typename std::decay<decltype(std::declval<TryBlock>()())>::type remote_try_handle_some( TryBlock && try_block, RemoteH && h );
		};

		template <class T> struct requires_catch { constexpr static bool value = false; };
		template <class T> struct requires_catch<T const> { constexpr static bool value = requires_catch<T>::value; };
		template <class T> struct requires_catch<T const &> { constexpr static bool value = requires_catch<T>::value; };
		template <class... Ex> struct requires_catch<catch_<Ex...>> { constexpr static bool value = true; };

		template <class... E>
		struct catch_requested;

		template <>
		struct catch_requested<>
		{
			constexpr static bool value = false;
		};

		template <class Car, class... Cdr>
		struct catch_requested<Car, Cdr...>
		{
			constexpr static bool value = requires_catch<Car>::value || catch_requested<Cdr...>::value;
		};

		template <bool CatchRequested, class... E>
		struct select_context_base_impl;

		template <class... E>
		struct select_context_base_impl<false, E...>
		{
			using type = nocatch_context<E...>;
		};

		template <class... E>
		struct select_context_base_impl<true, E...>
		{
			using type = catch_context<E...>;
		};

		template <class... E>
		using select_context_base = typename select_context_base_impl<catch_requested<E...>::value, E...>::type;
	}

	template <class... E>
	class context: public leaf_detail::select_context_base<E...>
	{
	};

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class HandlerL>
		struct handler_args_impl;

		template <template <class...> class L, class... H>
		struct handler_args_impl<L<H...>>
		{
			using type = leaf_detail_mp11::mp_append<fn_mp_args<H>...>;
		};

		template <class HandlerL>
		using handler_args = typename handler_args_impl<HandlerL>::type;

		template <class TypeList>
		struct deduce_context_impl;

		template <template <class...> class L, class... E>
		struct deduce_context_impl<L<E...>>
		{
			using type = context<E...>;
		};

		template <class TypeList>
		using deduce_context = typename deduce_context_impl<TypeList>::type;

		template <class RemoteH>
		struct context_type_from_remote_handler_impl;

		template <template <class...> class L, class... H>
		struct context_type_from_remote_handler_impl<L<H...>>
		{
			using type = deduce_context<leaf_detail_mp11::mp_append<fn_mp_args<H>...>>;
		};

		template <class... H>
		struct context_type_from_handlers_impl
		{
			using type = deduce_context<leaf_detail_mp11::mp_append<fn_mp_args<H>...>>;
		};

		template <class Ctx>
		struct polymorphic_context_impl: polymorphic_context, Ctx
		{
			error_id propagate_captured_errors() noexcept final override { return Ctx::propagate_captured_errors(captured_id_); }
			void activate() noexcept final override { Ctx::activate(); }
			void deactivate( bool propagate_errors ) noexcept final override { Ctx::deactivate(propagate_errors); }
			bool is_active() const noexcept final override { return Ctx::is_active(); }
			void print( std::ostream & os ) const final override { return Ctx::print(os); }
		};
	}

	template <class... H>
	using context_type_from_handlers = typename leaf_detail::context_type_from_handlers_impl<H...>::type;

	template <class RemoteH>
	using context_type_from_remote_handler = typename leaf_detail::context_type_from_remote_handler_impl<leaf_detail::fn_return_type<RemoteH>>::type;

	template <class...  H>
	inline context_type_from_handlers<H...> make_context()
	{
		return { };
	}

	template <class RemoteH>
	inline context_type_from_remote_handler<RemoteH> make_context( RemoteH const * = 0 )
	{
		return { };
	}

	template <class RemoteH>
	inline context_ptr make_shared_context( RemoteH const * = 0 )
	{
		return std::make_shared<leaf_detail::polymorphic_context_impl<context_type_from_remote_handler<RemoteH>>>();
	}

	template <class RemoteH, class Alloc>
	inline context_ptr allocate_shared_context( Alloc alloc, RemoteH const * = 0 )
	{
		return std::make_shared<leaf_detail::polymorphic_context_impl<context_type_from_remote_handler<RemoteH>>>(alloc);
	}
} }

#endif
// <<< #include <boost/leaf/context.hpp>
#line 13 "../../include/boost/leaf/detail/all.hpp"
// >>> #include <boost/leaf/handle_error.hpp>
#line 1 "boost/leaf/handle_error.hpp"
#ifndef LEAF_539464A021D411E9BC8A79361E29EE6E
#define LEAF_539464A021D411E9BC8A79361E29EE6E

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/leaf/detail/handle.hpp>
#line 1 "boost/leaf/detail/handle.hpp"
#ifndef LEAF_AFBBD676B2FF11E8984C7976AE35F1A2
#define LEAF_AFBBD676B2FF11E8984C7976AE35F1A2

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace leaf {

	namespace leaf_detail
	{
		class exception_info_base
		{
		protected:

			explicit exception_info_base( std::exception const * ) noexcept;
			~exception_info_base() noexcept;

		public:

			std::exception const * const ex_;

			virtual void print( std::ostream & os ) const = 0;
		};

		class exception_info_: public exception_info_base
		{
			exception_info_( exception_info_ const & ) = delete;
			exception_info_ & operator=( exception_info_ const & ) = delete;

			void print( std::ostream & os ) const final override;

		public:

			explicit exception_info_( std::exception const * ex ) noexcept;
		};
	}

	class error_info
	{
		error_info & operator=( error_info const & ) = delete;

	protected:

		void print( std::ostream & os ) const
		{
			os << "Error ID: " << err_id_.value() << std::endl;
			if( xi_ )
				xi_->print(os);
#ifndef LEAF_NO_DIAGNOSTIC_INFO
			leaf_detail::slot_base::print_all(os,err_id_.value());
#endif
		}

	public:

		void const * remote_handling_ctx_;
		leaf_detail::exception_info_base const * const xi_;
		error_id const err_id_;

		explicit error_info( void const * remote_handling_ctx, error_id id ) noexcept:
			remote_handling_ctx_(remote_handling_ctx),
			xi_(0),
			err_id_(id)
		{
		}

		explicit error_info( void const *, leaf_detail::exception_info_ const & ) noexcept;

		explicit error_info( error_info const & x ) noexcept:
			remote_handling_ctx_(x.remote_handling_ctx_),
			xi_(x.xi_),
			err_id_(x.err_id_)
		{
		}

		int err_id() const noexcept
		{
			return err_id_.value();
		}

		error_id error() const noexcept
		{
			return err_id_;
		}

		std::error_code error_code() const noexcept
		{
			return err_id_;
		}

		bool exception_caught() const noexcept
		{
			return xi_!=0;
		}

		std::exception const * exception() const noexcept
		{
			assert(exception_caught());
			return xi_->ex_;
		}

		friend std::ostream & operator<<( std::ostream & os, error_info const & x )
		{
			os << "leaf::error_info:" << std::endl;
			x.print(os);
			return os;
		}
	};

	////////////////////////////////////////

#ifdef LEAF_DISCARD_UNEXPECTED

	class diagnostic_info: public error_info
	{
	public:

		diagnostic_info( error_info const & ei ) noexcept:
			error_info(ei)
		{
		}

		friend std::ostream & operator<<( std::ostream & os, diagnostic_info const & x )
		{
			return os << "leaf::diagnostic_info not available due to LEAF_DISCARD_UNEXPECTED" << std::endl;
		}
	};

	class verbose_diagnostic_info: public error_info
	{
	public:

		verbose_diagnostic_info( error_info const & ei ) noexcept:
			error_info(ei)
		{
		}

		friend std::ostream & operator<<( std::ostream & os, verbose_diagnostic_info const & x )
		{
			return os << "leaf::verbose_diagnostic_info not available due to LEAF_DISCARD_UNEXPECTED" << std::endl;
		}
	};

#else

	class diagnostic_info: public error_info
	{
		leaf_detail::e_unexpected_count const * e_uc_;

	public:

		diagnostic_info( error_info const & ei, leaf_detail::e_unexpected_count const * e_uc ) noexcept:
			error_info(ei),
			e_uc_(e_uc)
		{
		}

		friend std::ostream & operator<<( std::ostream & os, diagnostic_info const & x )
		{
			os << "leaf::diagnostic_info:";
			if( x.err_id_ )
			{
				os << std::endl;
				x.print(os);
				if( x.e_uc_  )
					x.e_uc_->print(os);
			}
			else
				os << " {No Error}" << std::endl;
			return os;
		}
	};

	class verbose_diagnostic_info: public error_info
	{
		leaf_detail::e_unexpected_info const * e_ui_;

	public:

		verbose_diagnostic_info( error_info const & ei, leaf_detail::e_unexpected_info const * e_ui ) noexcept:
			error_info(ei),
			e_ui_(e_ui)
		{
		}

		friend std::ostream & operator<<( std::ostream & os, verbose_diagnostic_info const & x )
		{
			os << "leaf::verbose_diagnostic_info:";
			if( x.err_id_ )
			{
				os << std::endl;
				x.print(os);
				if( x.e_ui_ )
					x.e_ui_->print(os);
			}
			else
				os << " {No Error}" << std::endl;
			return os;
		}
	};

#endif

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class T, class... List>
		struct type_index;

		template <class T, class... Cdr>
		struct type_index<T, T, Cdr...>
		{
			static const int value = 0;
		};

		template <class T, class Car, class... Cdr>
		struct type_index<T, Car, Cdr...>
		{
			static const int value = 1 + type_index<T,Cdr...>::value;
		};

		template <class T, class Tuple>
		struct tuple_type_index;

		template <class T, class... TupleTypes>
		struct tuple_type_index<T,std::tuple<TupleTypes...>>
		{
			static const int value = type_index<T,TupleTypes...>::value;
		};

		template <class E, class SlotsTuple>
		inline E const * peek( SlotsTuple const & tup, int err_id ) noexcept
		{
			return err_id ? std::get<tuple_type_index<slot<E>,SlotsTuple>::value>(tup).has_value(err_id) : 0;
		}
	}

	////////////////////////////////////////

	template <class E, class ErrorConditionEnum = E>
	struct condition
	{
	};

	namespace leaf_detail
	{
		template <class Enum, bool HasValue = has_value<Enum>::value>
		struct match_traits
		{
			using enumerator = Enum;
			using e_type = enumerator;
			using match_type = enumerator;

			template <class SlotsTuple>
			static match_type const * read( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return peek<e_type>(tup, ei.err_id());
			}
		};

		template <class E>
		struct match_traits<E, true>
		{
			using enumerator = decltype(E::value);
			using e_type = E;
			using match_type = enumerator;

			template <class SlotsTuple>
			static match_type const * read( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				if( auto pv = peek<e_type>(tup, ei.err_id()) )
					return &pv->value;
				else
					return 0;
			}
		};

		template <class ErrorConditionEnum>
		struct match_traits<condition<ErrorConditionEnum, ErrorConditionEnum>, false>
		{
			static_assert(std::is_error_condition_enum<ErrorConditionEnum>::value, "If leaf::condition is instantiated with one type, that type must be a std::error_condition_enum");

			using enumerator = ErrorConditionEnum;
			using e_type = e_original_ec;
			using match_type = std::error_code;

			template <class SlotsTuple>
			static match_type const * read( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				if( e_type const * ec = peek<e_type>(tup, ei.err_id()) )
					return &ec->value;
				else
					return 0;
			}
		};

		template <class E, class ErrorConditionEnum>
		struct match_traits<condition<E, ErrorConditionEnum>, false>
		{
			static_assert(leaf_detail::has_value<E>::value, "If leaf::condition is instantiated with two types, the first one must have a member std::error_code value");
			static_assert(std::is_error_condition_enum<ErrorConditionEnum>::value, "If leaf::condition is instantiated with two types, the second one must be a std::error_condition_enum");

			using enumerator = ErrorConditionEnum;
			using e_type = E;
			using match_type = std::error_code;

			template <class SlotsTuple>
			static match_type const * read( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				if( auto pv = peek<e_type>(tup, ei.err_id()) )
					return &pv->value;
				else
					return 0;
			}
		};

		template <class MatchType, class Enumerator>
		inline bool check_value_pack( MatchType const & x, Enumerator v ) noexcept
		{
			return x==v;
		}

		template <class MatchType, class Enumerator, class... EnumeratorRest>
		inline bool check_value_pack( MatchType const & x, Enumerator v1, EnumeratorRest ... v_rest ) noexcept
		{
			return x==v1 || check_value_pack(x,v_rest...);
		}
	}

	template <class E, typename leaf_detail::match_traits<E>::enumerator... V>
	class match
	{
	public:
		using type = typename leaf_detail::match_traits<E>::match_type;

	private:
		type const * const value_;

	public:

		explicit match( type const * value ) noexcept:
			value_(value)
		{
		}

		bool operator()() const noexcept
		{
			return value_ && leaf_detail::check_value_pack(*value_,V...);
		}

		type const & value() const noexcept
		{
			assert(value_!=0);
			return *value_;
		}
	};

	namespace leaf_detail
	{
		template <class T, typename match_traits<T>::enumerator... V> struct translate_type_impl<match<T,V...>> { using type = typename match_traits<T>::e_type; };
		template <class T, typename match_traits<T>::enumerator... V> struct translate_type_impl<match<T,V...> const>;
		template <class T, typename match_traits<T>::enumerator... V> struct translate_type_impl<match<T,V...> const *> { static_assert(sizeof(match<T,V...>)==0, "Handlers should take match<> by value, not as match<> const *"); };
		template <class T, typename match_traits<T>::enumerator... V> struct translate_type_impl<match<T,V...> const &> { static_assert(sizeof(match<T,V...>)==0, "Handlers should take match<> by value, not as match<> const &"); };
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class SlotsTuple,class T>
		struct check_one_argument
		{
			static bool check( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return peek<T>(tup, ei.err_id())!=0;
			}
		};

		template <class SlotsTuple,class T>
		struct check_one_argument<SlotsTuple,T *>
		{
			static bool check( SlotsTuple const &, error_info const & ) noexcept
			{
				return true;
			}
		};

		template <class SlotsTuple>
		struct check_one_argument<SlotsTuple,error_info>
		{
			static constexpr bool check( SlotsTuple const &, error_info const & )
			{
				return true;
			}
		};

		template <class SlotsTuple>
		struct check_one_argument<SlotsTuple,diagnostic_info>
		{
			static bool check( SlotsTuple const &, error_info const & ) noexcept
			{
				return true;
			}
		};

		template <class SlotsTuple>
		struct check_one_argument<SlotsTuple,verbose_diagnostic_info>
		{
			static bool check( SlotsTuple const &, error_info const & ) noexcept
			{
				return true;
			}
		};

		template <class SlotsTuple>
		struct check_one_argument<SlotsTuple,std::error_code>
		{
			static bool check( SlotsTuple const &, error_info const & ) noexcept
			{
				return true;
			}
		};

		template <class SlotsTuple, class T, typename match_traits<T>::enumerator... V>
		struct check_one_argument<SlotsTuple,match<T,V...>>
		{
			static bool check( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return match<T,V...>(match_traits<T>::read(tup,ei))();
			}
		};

		template <class SlotsTuple, class... List>
		struct check_arguments;

		template <class SlotsTuple, class Car, class... Cdr>
		struct check_arguments<SlotsTuple, Car, Cdr...>
		{
			static bool check( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return check_one_argument<SlotsTuple,Car>::check(tup,ei) && check_arguments<SlotsTuple,Cdr...>::check(tup,ei);
			}
		};

		template <class SlotsTuple>
		struct check_arguments<SlotsTuple>
		{
			static constexpr bool check( SlotsTuple const &, error_info const & ) noexcept
			{
				return true;
			}
		};
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class T>
		struct get_one_argument
		{
			template <class SlotsTuple>
			static T const & get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				T const * arg = peek<T>(tup, ei.err_id());
				assert(arg!=0);
				return *arg;
			}
		};

		template <class T>
		struct get_one_argument<T const *>
		{
			template <class SlotsTuple>
			static T const * get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return peek<T>(tup, ei.err_id());
			}
		};

		template <>
		struct get_one_argument<error_info>
		{
			template <class SlotsTuple>
			static error_info const & get( SlotsTuple const &, error_info const & ei ) noexcept
			{
				return ei;
			}
		};

#ifdef LEAF_DISCARD_UNEXPECTED

		template <>
		struct get_one_argument<diagnostic_info>
		{
			template <class SlotsTuple>
			static diagnostic_info get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return diagnostic_info(ei);
			}
		};

		template <>
		struct get_one_argument<verbose_diagnostic_info>
		{
			template <class SlotsTuple>
			static verbose_diagnostic_info get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return verbose_diagnostic_info(ei);
			}
		};

#else

		template <>
		struct get_one_argument<diagnostic_info>
		{
			template <class SlotsTuple>
			static diagnostic_info get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return diagnostic_info(ei, peek<e_unexpected_count>(tup, ei.err_id()));
			}
		};

		template <>
		struct get_one_argument<verbose_diagnostic_info>
		{
			template <class SlotsTuple>
			static verbose_diagnostic_info get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				return verbose_diagnostic_info(ei, peek<e_unexpected_info>(tup, ei.err_id()));
			}
		};

#endif

		template <>
		struct get_one_argument<std::error_code>
		{
			template <class SlotsTuple>
			static std::error_code get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				leaf_detail::e_original_ec const * org = peek<e_original_ec>(tup, ei.err_id());
				assert(org!=0);
				return org->value;
			}
		};

		template <class T, typename match_traits<T>::enumerator... V>
		struct get_one_argument<match<T,V...>>
		{
			template <class SlotsTuple>
			static match<T,V...> get( SlotsTuple const & tup, error_info const & ei ) noexcept
			{
				auto const * arg = match_traits<T>::read(tup, ei);
				assert(arg!=0);
				return match<T,V...>(arg);
			}
		};
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class T> struct argument_matches_any_error: std::false_type { };
		template <class T> struct argument_matches_any_error<T const *>: is_e_type<T> { };
		template <> struct argument_matches_any_error<error_info const &>: std::true_type { };
		template <> struct argument_matches_any_error<diagnostic_info const &>: std::true_type { };
		template <> struct argument_matches_any_error<verbose_diagnostic_info const &>: std::true_type { };
		template <> struct argument_matches_any_error<std::error_code const &>: std::true_type { };

		template <class>
		struct handler_matches_any_error: std::false_type
		{
		};

		template <template<class...> class L, class Car, class... Cdr>
		struct handler_matches_any_error<L<Car,Cdr...>>
		{
			constexpr static bool value = argument_matches_any_error<Car>::value && handler_matches_any_error<L<Cdr...>>::value;
		};

		template <template<class...> class L>
		struct handler_matches_any_error<L<>>: std::true_type
		{
		};
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class Tup, class... T>
		inline bool check_handler_( Tup const & e_objects, error_info const & ei, leaf_detail_mp11::mp_list<T...> ) noexcept
		{
			return check_arguments<Tup,typename std::remove_cv<typename std::remove_reference<T>::type>::type...>::check(e_objects, ei);
		}

		template <class R, class F, bool IsResult = is_result_type<R>::value, class FReturnType = fn_return_type<F>>
		struct handler_caller
		{
			template <class Tup, class... T>
			static R call( Tup const & e_objects, error_info const & ei, F && f, leaf_detail_mp11::mp_list<T...> )
			{
				return std::forward<F>(f)( get_one_argument<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::get(e_objects, ei)... );
			}
		};

		template <template <class...> class Result, class... E, class F>
		struct handler_caller<Result<void, E...>, F, true, void>
		{
			using R = Result<void, E...>;

			template <class Tup,class... T>
			static R call( Tup const & e_objects, error_info const & ei, F && f, leaf_detail_mp11::mp_list<T...> )
			{
				std::forward<F>(f)( get_one_argument<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::get(e_objects, ei)... );
				return { };
			}
		};

		template <class R, class Tup, class F>
		inline R handle_error_( Tup const & e_objects, error_info const & ei, F && f )
		{
			static_assert( handler_matches_any_error<fn_mp_args<F>>::value, "The last handler passed to handle_all must match any error." );
			return handler_caller<R, F>::call( e_objects, ei, std::forward<F>(f), fn_mp_args<F>{ } );
		}

		template <class R, class Tup, class CarF, class... CdrF>
		inline R handle_error_( Tup const & e_objects, error_info const & ei, CarF && car_f, CdrF && ... cdr_f )
		{
			if( handler_matches_any_error<fn_mp_args<CarF>>::value || check_handler_( e_objects, ei, fn_mp_args<CarF>{ } ) )
				return handler_caller<R, CarF>::call( e_objects, ei, std::forward<CarF>(car_f), fn_mp_args<CarF>{ } );
			else
				return handle_error_<R>( e_objects, ei, std::forward<CdrF>(cdr_f)...);
		}
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class T, template <class...> class R, class... E>
		struct add_result
		{
			using type = R<T, E...>;
		};

		template <class T, template <class...> class R, class... E>
		struct add_result<R<T, E...>, R, E...>
		{
			using type = R<T, E...>;
		};

		template <class... T>
		struct handler_pack_return_impl;

		template <class T>
		struct handler_pack_return_impl<T>
		{
			using type = T;
		};

		template <class Car, class... Cdr>
		struct handler_pack_return_impl<Car, Car, Cdr...>
		{
			using type = typename handler_pack_return_impl<Car, Cdr...>::type;
		};

		template <template <class...> class R, class... E, class Car, class... Cdr>
		struct handler_pack_return_impl<R<Car,E...>, Car, Cdr...>
		{
			using type = typename handler_pack_return_impl<R<Car,E...>, typename add_result<Cdr,R,E...>::type...>::type;
		};

		template <template <class...> class R, class... E, class Car, class... Cdr>
		struct handler_pack_return_impl<Car, R<Car,E...>, Cdr...>
		{
			using type = typename handler_pack_return_impl<R<Car,E...>, typename add_result<Cdr,R,E...>::type...>::type;
		};

		template <class... H>
		using handler_pack_return = typename handler_pack_return_impl<typename std::decay<fn_return_type<H>>::type...>::type;

		template <class... H>
		struct handler_result
		{
			using R = handler_pack_return<H...>;

			R r;

			R get() noexcept
			{
				return std::move(r);
			}
		};

		template <class... H>
		struct handler_result_void
		{
			void get() noexcept
			{
			}
		};
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class... E>
		template <class R, class... H>
		inline typename std::decay<decltype(std::declval<R>().value())>::type context_base<E...>::handle_all( R & r, H && ... h ) const
		{
			using namespace leaf_detail;
			using Ret = typename std::decay<decltype(std::declval<R>().value())>::type;
			static_assert(is_result_type<R>::value, "The R type used with a handle_all function must be registered with leaf::is_result_type");
			return handle_error_<Ret>(tup(), error_info(0, r.error()), std::forward<H>(h)...);
		}

		template <class... E>
		template <class R, class RemoteH>
		inline typename std::decay<decltype(std::declval<R>().value())>::type context_base<E...>::remote_handle_all( R & r, RemoteH && h ) const
		{
			static_assert(is_result_type<R>::value, "The R type used with a handle_all function must be registered with leaf::is_result_type");
			return std::forward<RemoteH>(h)(error_info(this, r.error())).get();
		}

		template <class... E>
		template <class R, class... H>
		inline R context_base<E...>::handle_some( R && r, H && ... h ) const
		{
			using namespace leaf_detail;
			static_assert(is_result_type<R>::value, "The R type used with a handle_some function must be registered with leaf::is_result_type");
			return handle_error_<R>(tup(), error_info(0, r.error()), std::forward<H>(h)...,
				[&r]()->R { return std::move(r); });
		}

		template <class... E>
		template <class R, class RemoteH>
		inline R context_base<E...>::remote_handle_some( R && r, RemoteH && h ) const
		{
			static_assert(is_result_type<R>::value, "The R type used with a handle_some function must be registered with leaf::is_result_type");
			return std::forward<RemoteH>(h)(error_info(this, r.error())).get();
		}

		////////////////////////////////////////////

		template <class... E>
		template <class TryBlock, class... H>
		inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type context_base<E...>::try_handle_all_( TryBlock && try_block, H && ... h ) const
		{
			using namespace leaf_detail;
			static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_all function must be registered with leaf::is_result_type");
			assert(this->is_active());
			if( auto r = std::forward<TryBlock>(try_block)() )
				return r.value();
			else
				return handle_all(r, std::forward<H>(h)...);
		}

		template <class... E>
		template <class TryBlock, class RemoteH>
		inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type context_base<E...>::remote_try_handle_all_( TryBlock && try_block, RemoteH && h ) const
		{
			using namespace leaf_detail;
			static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a remote_try_handle_all function must be registered with leaf::is_result_type");
			assert(this->is_active());
			if( auto r = std::forward<TryBlock>(try_block)() )
				return r.value();
			else
				return remote_handle_all(r, std::forward<RemoteH>(h));
		}

		template <class... E>
		template <class TryBlock, class... H, class Ctx>
		inline typename std::decay<decltype(std::declval<TryBlock>()())>::type context_base<E...>::try_handle_some_( context_activator<Ctx> & active_context, TryBlock && try_block, H && ... h ) const
		{
			using namespace leaf_detail;
			static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_some function must be registered with leaf::is_result_type");
			assert(this->is_active());
			if( auto r = std::forward<TryBlock>(try_block)() )
				return r;
			else
			{
				auto rr = handle_some(std::move(r), std::forward<H>(h)...);
				if( !rr )
					active_context.set_on_deactivate(on_deactivation::propagate);
				return rr;
			}
		}

		template <class... E>
		template <class TryBlock, class RemoteH, class Ctx>
		inline typename std::decay<decltype(std::declval<TryBlock>()())>::type context_base<E...>::remote_try_handle_some_( context_activator<Ctx> & active_context, TryBlock && try_block, RemoteH && h ) const
		{
			using namespace leaf_detail;
			static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a remote_try_handle_some function must be registered with leaf::is_result_type");
			assert(this->is_active());
			if( auto r = std::forward<TryBlock>(try_block)() )
				return r;
			else
			{
				auto rr = remote_handle_some(std::move(r), std::forward<RemoteH>(h));
				if( !rr )
					active_context.set_on_deactivate(on_deactivation::propagate);
				return rr;
			}
		}
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class R, class... H>
		struct remote_error_dispatch_impl
		{
			using result_type = handler_result<H...>;

			//When can HH... be different than H...? It isn't, except that the _some
			//versions internally need to add a match-all handler at the end, which we
			//know is not going to affect the deduced context type Ctx.
			template <class... HH>
			static result_type handle( error_info const & err, HH && ... h )
			{
				using Ctx = context_type_from_handlers<HH...>;
				using CtxHH = context_type_from_handlers<HH...>;
				static_assert(std::is_same<Ctx,CtxHH>::value, "Buggy context deduction logic");
				return { handle_error_<R>(static_cast<Ctx const *>(err.remote_handling_ctx_)->tup(), err, std::forward<HH>(h)...) };
			}
		};

		template <class... H>
		struct remote_error_dispatch_impl<void, H...>
		{
			using result_type = handler_result_void<H...>;

			//When can HH... be different than H...? It isn't, except that the _some
			//versions internally need to add a match-all handler at the end, which we
			//know is not going to affect the deduced context type Ctx.
			template <class... HH>
			static result_type handle( error_info const & err, HH && ... h )
			{
				using Ctx = context_type_from_handlers<HH...>;
				using CtxHH = context_type_from_handlers<HH...>;
				static_assert(std::is_same<Ctx,CtxHH>::value, "Buggy context deduction logic");
				handle_error_<void>(static_cast<Ctx const *>(err.remote_handling_ctx_)->tup(), err, std::forward<HH>(h)...);
				return { };
			}
		};

		template <class... H>
		using remote_error_dispatch = remote_error_dispatch_impl<handler_pack_return<H...>, H...>;
	}

	template <class... H>
	inline typename leaf_detail::remote_error_dispatch<H...>::result_type remote_handle_all( error_info const & err, H && ... h )
	{
		return leaf_detail::remote_error_dispatch<H...>::handle(err, std::forward<H>(h)... );
	}

	template <class... H>
	inline typename leaf_detail::remote_error_dispatch<H...>::result_type remote_handle_some( error_info const & err, H && ... h )
	{
		using R = decltype(std::declval<typename leaf_detail::remote_error_dispatch<H...>::result_type>().get());
		return leaf_detail::remote_error_dispatch<H...>::handle(err, std::forward<H>(h)...,
			[&err]() -> R { return err.error_code(); } );
	}

	////////////////////////////////////////

	template <class TryBlock, class... H>
	inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type try_handle_all( TryBlock && try_block, H && ... h )
	{
		return context_type_from_handlers<H...>().try_handle_all( std::forward<TryBlock>(try_block), std::forward<H>(h)... );
	}

	template <class TryBlock, class RemoteH>
	inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type remote_try_handle_all( TryBlock && try_block, RemoteH && h )
	{
		return context_type_from_remote_handler<RemoteH>().remote_try_handle_all( std::forward<TryBlock>(try_block), std::forward<RemoteH>(h) );
	}

	template <class TryBlock, class... H>
	inline typename std::decay<decltype(std::declval<TryBlock>()())>::type try_handle_some( TryBlock && try_block, H && ... h )
	{
		return context_type_from_handlers<H...>().try_handle_some( std::forward<TryBlock>(try_block), std::forward<H>(h)... );
	}

	template <class TryBlock, class RemoteH>
	inline typename std::decay<decltype(std::declval<TryBlock>()())>::type remote_try_handle_some( TryBlock && try_block, RemoteH && h )
	{
		return context_type_from_remote_handler<RemoteH>().remote_try_handle_some( std::forward<TryBlock>(try_block), std::forward<RemoteH>(h) );
	}

} }

#endif
// <<< #include <boost/leaf/detail/handle.hpp>
#line 10 "boost/leaf/handle_error.hpp"

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <class... E>
		template <class TryBlock, class... H>
		inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type nocatch_context<E...>::try_handle_all( TryBlock && try_block, H && ... h )
		{
			auto active_context = activate_context(*this, on_deactivation::do_not_propagate);
			return this->try_handle_all_( std::forward<TryBlock>(try_block), std::forward<H>(h)... );
		}

		template <class... E>
		template <class TryBlock, class RemoteH>
		inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type nocatch_context<E...>::remote_try_handle_all( TryBlock && try_block, RemoteH && h )
		{
			auto active_context = activate_context(*this, on_deactivation::do_not_propagate);
			return this->remote_try_handle_all_( std::forward<TryBlock>(try_block), std::forward<RemoteH>(h) );
		}

		template <class... E>
		template <class TryBlock, class... H>
		inline typename std::decay<decltype(std::declval<TryBlock>()())>::type nocatch_context<E...>::try_handle_some( TryBlock && try_block, H && ... h )
		{
			auto active_context = activate_context(*this, on_deactivation::propagate_if_uncaught_exception);
			return this->try_handle_some_( active_context, std::forward<TryBlock>(try_block), std::forward<H>(h)... );
		}

		template <class... E>
		template <class TryBlock, class RemoteH>
		inline typename std::decay<decltype(std::declval<TryBlock>()())>::type nocatch_context<E...>::remote_try_handle_some( TryBlock && try_block, RemoteH && h )
		{
			auto active_context = activate_context(*this, on_deactivation::propagate_if_uncaught_exception);
			return this->remote_try_handle_some_( active_context, std::forward<TryBlock>(try_block), std::forward<RemoteH>(h) );
		}
	}

} }

#endif
// <<< #include <boost/leaf/handle_error.hpp>
#line 16 "../../include/boost/leaf/detail/all.hpp"
#ifndef LEAF_NO_EXCEPTIONS
// >>> #	include <boost/leaf/handle_exception.hpp>
#line 1 "boost/leaf/handle_exception.hpp"
#ifndef LEAF_87F274C4D4BA11E89928D55AC82C3C47
#define LEAF_87F274C4D4BA11E89928D55AC82C3C47

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef LEAF_NO_EXCEPTIONS
#	error This header requires exception handling
#endif

// >>> #include <boost/leaf/detail/demangle.hpp>
#line 1 "boost/leaf/detail/demangle.hpp"
#ifndef LEAF_E7999136FCD911E8B7F308A7642D5A5F
#define LEAF_E7999136FCD911E8B7F308A7642D5A5F

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// core::demangle
//
// Copyright 2014 Peter Dimov
// Copyright 2014 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <string>

#if !defined(_MSC_VER)
#	if defined(__has_include) && __has_include(<cxxabi.h>)
#		define LEAF_HAS_CXXABI_H
#	endif
#endif

#if defined( LEAF_HAS_CXXABI_H )
#	include <cxxabi.h>
// For some archtectures (mips, mips64, x86, x86_64) cxxabi.h in Android NDK is implemented by gabi++ library
// (https://android.googlesource.com/platform/ndk/+/master/sources/cxx-stl/gabi++/), which does not implement
// abi::__cxa_demangle(). We detect this implementation by checking the include guard here.
#	if defined( __GABIXX_CXXABI_H__ )
#		undef LEAF_HAS_CXXABI_H
#	else
#		include <cstdlib>
#		include <cstddef>
#	endif
#endif

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		inline char const * demangle_alloc( char const * name ) noexcept;
		inline void demangle_free( char const * name ) noexcept;

		class scoped_demangled_name
		{
		private:
			char const * m_p;

		public:
			explicit scoped_demangled_name( char const * name ) noexcept :
				m_p( demangle_alloc( name ) )
			{
			}

			~scoped_demangled_name() noexcept
			{
				demangle_free( m_p );
			}

			char const * get() const noexcept
			{
				return m_p;
			}

			scoped_demangled_name( scoped_demangled_name const& ) = delete;
			scoped_demangled_name& operator= ( scoped_demangled_name const& ) = delete;
		};

#if defined( LEAF_HAS_CXXABI_H )

		inline char const * demangle_alloc( char const * name ) noexcept
		{
			int status = 0;
			std::size_t size = 0;
			return abi::__cxa_demangle( name, NULL, &size, &status );
		}

		inline void demangle_free( char const * name ) noexcept
		{
			std::free( const_cast< char* >( name ) );
		}

		inline std::string demangle( char const * name )
		{
			scoped_demangled_name demangled_name( name );
			char const * p = demangled_name.get();
			if( !p )
				p = name;
			return p;
		}

#else

		inline char const * demangle_alloc( char const * name ) noexcept
		{
			return name;
		}

		inline void demangle_free( char const * ) noexcept
		{
		}

		inline std::string demangle( char const * name )
		{
			return name;
		}

#endif
	}

} }

#ifdef LEAF_HAS_CXXABI_H
#	undef LEAF_HAS_CXXABI_H
#endif

#endif
// <<< #include <boost/leaf/detail/demangle.hpp>
#line 17 "boost/leaf/handle_exception.hpp"

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <class Ex>
		inline bool check_exception_pack( std::exception const * ex, Ex const * ) noexcept
		{
			return dynamic_cast<Ex const *>(ex)!=0;
		}

		template <class Ex, class... ExRest>
		inline bool check_exception_pack( std::exception const * ex, Ex const *, ExRest const * ... ex_rest ) noexcept
		{
			return dynamic_cast<Ex const *>(ex)!=0 || check_exception_pack(ex, ex_rest...);
		}

		inline bool check_exception_pack( std::exception const * )
		{
			return true;
		}
	}

	template <class... Ex>
	class catch_
	{
		std::exception const * const value_;

	public:

		explicit catch_( std::exception const * value ) noexcept:
			value_(value)
		{
		}

		bool operator()() const noexcept
		{
			return value_ && leaf_detail::check_exception_pack(value_,static_cast<Ex const *>(0)...);
		}

		std::exception const & value() const noexcept
		{
			assert(value_!=0);
			return *value_;
		}
	};

	template <class Ex>
	class catch_<Ex>
	{
		Ex const * const value_;

	public:

		explicit catch_( std::exception const * value ) noexcept:
			value_(dynamic_cast<Ex const *>(value))
		{
		}

		bool operator()() const noexcept
		{
			return this->value_!=0;
		}

		Ex const & value() const noexcept
		{
			assert(this->value_!=0);
			return *this->value_;
		}
	};

	namespace leaf_detail
	{
		template <class... Exceptions> struct translate_type_impl<catch_<Exceptions...>> { using type = void; };
		template <class... Exceptions> struct translate_type_impl<catch_<Exceptions...> const>;
		template <class... Exceptions> struct translate_type_impl<catch_<Exceptions...> const *> { static_assert(sizeof(catch_<Exceptions...>)==0, "Handlers should take catch_<> by value, not as catch_<> const *"); };
		template <class... Exceptions> struct translate_type_impl<catch_<Exceptions...> const &> { static_assert(sizeof(catch_<Exceptions...>)==0, "Handlers should take catch_<> by value, not as catch_<> const &"); };

		template <class SlotsTuple, class... Ex>
		struct check_one_argument<SlotsTuple,catch_<Ex...>>
		{
			static bool check( SlotsTuple const &, error_info const & ei ) noexcept
			{
				if( ei.exception_caught() )
					return catch_<Ex...>(ei.exception())();
				else
					return false;
			}
		};

		template <class... Ex>
		struct get_one_argument<catch_<Ex...>>
		{
			template <class SlotsTuple>
			static catch_<Ex...> get( SlotsTuple const &, error_info const & ei ) noexcept
			{
				std::exception const * ex = ei.exception();
				assert(ex!=0);
				return catch_<Ex...>(ex);
			}
		};
	}

	////////////////////////////////////////

	template <class TryBlock, class... H>
	inline decltype(std::declval<TryBlock>()()) try_catch( TryBlock && try_block, H && ... h )
	{
		using namespace leaf_detail;
		context_type_from_handlers<H...> ctx;
		auto active_context = activate_context(ctx, on_deactivation::propagate_if_uncaught_exception);
		return ctx.try_catch_(
			[&]
			{
				return std::forward<TryBlock>(try_block)();
			},
			std::forward<H>(h)...);
	}

	template <class TryBlock, class RemoteH>
	inline decltype(std::declval<TryBlock>()()) remote_try_catch( TryBlock && try_block, RemoteH && h )
	{
		using namespace leaf_detail;
		context_type_from_remote_handler<RemoteH> ctx;
		auto active_context = activate_context(ctx, on_deactivation::propagate_if_uncaught_exception);
		return ctx.remote_try_catch_(
			[&]
			{
				return std::forward<TryBlock>(try_block)();
			},
			std::forward<RemoteH>(h));
	}

	namespace leaf_detail
	{
		template <class... E>
		template <class R, class... H>
		inline R context_base<E...>::handle_current_exception( H && ... h ) const
		{
			return this->try_catch_(
				[]{ throw; },
				std::forward<H>(h)...);
		}

		template <class... E>
		template <class R, class RemoteH>
		inline R context_base<E...>::remote_handle_current_exception( RemoteH && h ) const
		{
			return this->remote_try_catch_(
				[]() -> R { throw; },
				std::forward<RemoteH>(h));
		}

		template <class... E>
		template <class R, class... H>
		inline R context_base<E...>::handle_exception( std::exception_ptr const & ep, H && ... h ) const
		{
			return this->try_catch_(
				[&]{ std::rethrow_exception(ep); },
				std::forward<H>(h)...);
		}

		template <class... E>
		template <class R, class RemoteH>
		inline R context_base<E...>::remote_handle_exception( std::exception_ptr const & ep, RemoteH && h  ) const
		{
			return this->remote_try_catch_(
				[&]() -> R { std::rethrow_exception(ep); },
				std::forward<RemoteH>(h));
		}

		////////////////////////////////////////

		template <class... E>
		template <class TryBlock, class... H>
		inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type catch_context<E...>::try_handle_all( TryBlock && try_block, H && ... h )
		{
			using namespace leaf_detail;
			static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_all function must be registered with leaf::is_result_type");
			auto active_context = activate_context(*this, on_deactivation::propagate_if_uncaught_exception);
			if(	auto r = this->try_catch_(
					[&]
					{
						return std::forward<TryBlock>(try_block)();
					},
					std::forward<H>(h)...) )
				return r.value();
			else
				return this->handle_all(r, std::forward<H>(h)...);
		}

		template <class... E>
		template <class TryBlock, class RemoteH>
		inline typename std::decay<decltype(std::declval<TryBlock>()().value())>::type catch_context<E...>::remote_try_handle_all( TryBlock && try_block, RemoteH && h )
		{
			using namespace leaf_detail;
			static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_all function must be registered with leaf::is_result_type");
			auto active_context = activate_context(*this, on_deactivation::propagate_if_uncaught_exception);
			if(	auto r = this->remote_try_catch_(
					[&]
					{
						return std::forward<TryBlock>(try_block)();
					},
					std::forward<RemoteH>(h)) )
				return r.value();
			else
				return this->remote_handle_all(r, std::forward<RemoteH>(h));
		}

		template <class... E>
		template <class TryBlock, class... H>
		inline typename std::decay<decltype(std::declval<TryBlock>()())>::type catch_context<E...>::try_handle_some( TryBlock && try_block, H && ... h )
		{
			using namespace leaf_detail;
			static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_some function must be registered with leaf::is_result_type");
			auto active_context = activate_context(*this, on_deactivation::propagate_if_uncaught_exception);
			if(	auto r = this->try_catch_(
					[&]
					{
						return std::forward<TryBlock>(try_block)();
					},
					std::forward<H>(h)...) )
				return r;
			else
			{
				auto rr = this->handle_some(std::move(r), std::forward<H>(h)...);
				if( !rr )
					active_context.set_on_deactivate(on_deactivation::propagate);
				return rr;
			}
		}

		template <class... E>
		template <class TryBlock, class RemoteH>
		inline typename std::decay<decltype(std::declval<TryBlock>()())>::type catch_context<E...>::remote_try_handle_some( TryBlock && try_block, RemoteH && h )
		{
			auto active_context = activate_context(*this, on_deactivation::propagate_if_uncaught_exception);
			if( auto r = this->remote_try_catch_(
					[&]
					{
						return std::forward<TryBlock>(try_block)();
					},
					std::forward<RemoteH>(h)) )
				return r;
			else
			{
				auto rr = this->remote_handle_some(std::move(r), std::forward<RemoteH>(h));
				if( !rr )
					active_context.set_on_deactivate(on_deactivation::propagate);
				return rr;
			}
		}

		////////////////////////////////////////

		inline void exception_info_::print( std::ostream & os ) const
		{
			if( ex_ )
			{
				os <<
					"Exception dynamic type: " << leaf_detail::demangle(typeid(*ex_).name()) << std::endl <<
					"std::exception::what(): " << ex_->what() << std::endl;
			}
			else
				os << "Unknown exception type (not a std::exception)" << std::endl;
		}

		inline exception_info_::exception_info_( std::exception const * ex ) noexcept:
			exception_info_base(ex)
		{
		}

		template <class... E>
		template <class TryBlock, class... H>
		inline decltype(std::declval<TryBlock>()()) context_base<E...>::try_catch_( TryBlock && try_block, H && ... h ) const
		{
			using namespace leaf_detail;
			using R = decltype(std::declval<TryBlock>()());
			try
			{
				return std::forward<TryBlock>(try_block)();
			}
			catch( capturing_exception const & cap )
			{
				try
				{
					cap.unload_and_rethrow_original_exception();
				}
				catch( std::exception const & ex )
				{
					return leaf_detail::handle_error_<R>(this->tup(), error_info(0, exception_info_(&ex)), std::forward<H>(h)...,
						[]() -> R { throw; } );
				}
				catch(...)
				{
					return leaf_detail::handle_error_<R>(this->tup(), error_info(0, exception_info_(0)), std::forward<H>(h)...,
						[]() -> R { throw; } );
				}
			}
			catch( std::exception const & ex )
			{
				return leaf_detail::handle_error_<R>(this->tup(), error_info(0, exception_info_(&ex)), std::forward<H>(h)...,
					[]() -> R { throw; } );
			}
			catch(...)
			{
				return leaf_detail::handle_error_<R>(this->tup(), error_info(0, exception_info_(0)), std::forward<H>(h)...,
					[]() -> R { throw; } );
			}
		}

		template <class... E>
		template <class TryBlock, class RemoteH>
		inline decltype(std::declval<TryBlock>()()) context_base<E...>::remote_try_catch_( TryBlock && try_block, RemoteH && h ) const
		{
			using namespace leaf_detail;
			try
			{
				return std::forward<TryBlock>(try_block)();
			}
			catch( capturing_exception const & cap )
			{
				try
				{
					cap.unload_and_rethrow_original_exception();
				}
				catch( std::exception const & ex )
				{
					return std::forward<RemoteH>(h)(error_info(this, exception_info_(&ex))).get();
				}
				catch(...)
				{
					return std::forward<RemoteH>(h)(error_info(this, exception_info_(0))).get();
				}
			}
			catch( std::exception const & ex )
			{
				return std::forward<RemoteH>(h)(error_info(this, exception_info_(&ex))).get();
			}
			catch(...)
			{
				return std::forward<RemoteH>(h)(error_info(this, exception_info_(0))).get();
			}
		}
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class R, class... H>
		struct remote_handle_exception_dispatch_impl
		{
			using result_type = handler_result<H...>;

			static result_type handle( error_info const & err, H && ... h )
			{
				using Ctx = context_type_from_handlers<H...>;
				return { leaf_detail::handle_error_<R>(static_cast<Ctx const *>(err.remote_handling_ctx_)->tup(), err, std::forward<H>(h)...,
					[]() -> R { throw; } ) };
			}
		};

		template <class... H>
		struct remote_handle_exception_dispatch_impl<void, H...>
		{
			using result_type = handler_result_void<H...>;

			static result_type handle( error_info const & err, H && ... h )
			{
				using Ctx = context_type_from_handlers<H...>;
				leaf_detail::handle_error_<void>(static_cast<Ctx const *>(err.remote_handling_ctx_)->tup(), err, std::forward<H>(h)...,
					[]{ throw; } );
				return { };
			}
		};

		template <class... H>
		using remote_handle_exception_dispatch = remote_handle_exception_dispatch_impl<handler_pack_return<H...>, H...>;
	}

	template <class... H>
	inline typename leaf_detail::remote_handle_exception_dispatch<H...>::result_type remote_handle_exception( error_info const & err, H && ... h )
	{
		using namespace leaf_detail;
		return remote_handle_exception_dispatch<H...>::handle(err, std::forward<H>(h)...);
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		inline error_id unpack_error_id( std::exception const * ex )
		{
			if( std::system_error const * se = dynamic_cast<std::system_error const *>(ex) )
				return error_id(se->code());
			else if( std::error_code const * ec = dynamic_cast<std::error_code const *>(ex) )
				return error_id(*ec);
			else if( error_id const * err_id = dynamic_cast<error_id const *>(ex) )
				return *err_id;
			else
				return next_error();
		}

		inline exception_info_base::exception_info_base( std::exception const * ex ) noexcept:
			ex_(ex)
		{
			assert(!dynamic_cast<capturing_exception const *>(ex_));
		}

		inline exception_info_base::~exception_info_base() noexcept
		{
		}
	}

	inline error_info::error_info( void const * remote_handling_ctx, leaf_detail::exception_info_ const & xi ) noexcept:
		remote_handling_ctx_(remote_handling_ctx),
		xi_(&xi),
		err_id_(leaf_detail::unpack_error_id(xi_->ex_))
	{
	}

} }

#endif
// <<< #	include <boost/leaf/handle_exception.hpp>
#line 18 "../../include/boost/leaf/detail/all.hpp"
#endif
// >>> #include <boost/leaf/preload.hpp>
#line 1 "boost/leaf/preload.hpp"
#ifndef LEAF_25AF99F6DC6F11E8803DE9BC9723C688
#define LEAF_25AF99F6DC6F11E8803DE9BC9723C688

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <int I, class Tuple>
		struct tuple_for_each_preload
		{
			static void trigger( Tuple & tup, int err_id ) noexcept
			{
				assert((err_id&3)==1);
				tuple_for_each_preload<I-1,Tuple>::trigger(tup,err_id);
				std::get<I-1>(tup).trigger(err_id);
			}
		};

		template <class Tuple>
		struct tuple_for_each_preload<0, Tuple>
		{
			static void trigger( Tuple const &, int ) noexcept { }
		};
	} // leaf_detail

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class E>
		class preloaded_item
		{
			slot<E> * s_;
			E e_;

		public:

			explicit preloaded_item( E && e ) noexcept:
				s_(tl_slot_ptr<E>()),
				e_(std::forward<E>(e))
			{
			}

			void trigger( int err_id ) noexcept
			{
				assert((err_id&3)==1);
				if( s_ )
				{
					if( !s_->has_value(err_id) )
						s_->put(err_id, std::move(e_));
				}
#ifndef LEAF_DISCARD_UNEXPECTED
				else
				{
					int c = tl_unexpected_enabled_counter();
					assert(c>=0);
					if( c )
						no_expect_slot(err_id, std::forward<E>(e_));
				}
#endif
			}
		};

		template <class... E>
		class preloaded
		{
			preloaded & operator=( preloaded const & ) = delete;

			std::tuple<preloaded_item<E>...> p_;
			bool moved_;
			int err_id_;

		public:

			explicit preloaded( E && ... e ) noexcept:
				p_(preloaded_item<E>(std::forward<E>(e))...),
				moved_(false),
				err_id_(last_id())
			{
			}

			preloaded( preloaded && x ) noexcept:
				p_(std::move(x.p_)),
				moved_(false),
				err_id_(x.err_id_)
			{
				x.moved_ = true;
			}

			~preloaded() noexcept
			{
				if( moved_ )
					return;
				int const err_id = last_id();
				if( err_id==err_id_ )
				{
#ifndef LEAF_NO_EXCEPTIONS
					if( std::uncaught_exception() )
						leaf_detail::tuple_for_each_preload<sizeof...(E),decltype(p_)>::trigger(p_,next_id());
#endif
				}
				else
					leaf_detail::tuple_for_each_preload<sizeof...(E),decltype(p_)>::trigger(p_,err_id);
			}
		};
	} // leaf_detail

	template <class... E>
	inline leaf_detail::preloaded<E...> preload( E && ... e ) noexcept
	{
		return leaf_detail::preloaded<E...>(std::forward<E>(e)...);
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class F>
		class deferred_item
		{
			typedef decltype(std::declval<F>()()) E;
			slot<E> * s_;
			F f_;

		public:

			explicit deferred_item( F && f ) noexcept:
				s_(tl_slot_ptr<E>()),
				f_(std::forward<F>(f))
			{
			}

			void trigger( int err_id ) noexcept
			{
				assert((err_id&3)==1);
				if( s_ )
				{
					if( !s_->has_value(err_id) )
						s_->put(err_id, f_());
				}
#ifndef LEAF_DISCARD_UNEXPECTED
				else
				{
					int c = tl_unexpected_enabled_counter();
					assert(c>=0);
					if( c )
						no_expect_slot(err_id, std::forward<E>(f_()));
				}
#endif
			}
		};

		template <class... F>
		class deferred
		{
			deferred & operator=( deferred const & ) = delete;
			std::tuple<deferred_item<F>...> d_;
			bool moved_;
			int err_id_;

		public:

			explicit deferred( F && ... f ) noexcept:
				d_(deferred_item<F>(std::forward<F>(f))...),
				moved_(false),
				err_id_(last_id())
			{
			}

			deferred( deferred && x ) noexcept:
				d_(std::move(x.d_)),
				moved_(false),
				err_id_(x.err_id_)
			{
				x.moved_ = true;
			}

			~deferred() noexcept
			{
				if( moved_ )
					return;
				int const err_id = last_id();
				if( err_id==err_id_ )
				{
#ifndef LEAF_NO_EXCEPTIONS
					if( std::uncaught_exception() )
						leaf_detail::tuple_for_each_preload<sizeof...(F),decltype(d_)>::trigger(d_,next_id());
#endif
				}
				else
					leaf_detail::tuple_for_each_preload<sizeof...(F),decltype(d_)>::trigger(d_,err_id);
			}
		};
	} // leaf_detail

	template <class... F>
	inline leaf_detail::deferred<F...> defer( F && ... f ) noexcept
	{
		return leaf_detail::deferred<F...>(std::forward<F>(f)...);
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class F, class A0 = fn_arg_type<F,0>, int arity = function_traits<F>::arity>
		class accumulating_item;

		template <class F, class A0>
		class accumulating_item<F, A0 &, 1>
		{
			using E = A0;
			slot<E> * s_;
			F f_;

		public:

			explicit accumulating_item( F && f ) noexcept:
				s_(tl_slot_ptr<E>()),
				f_(std::forward<F>(f))
			{
			}

			void trigger( int err_id ) noexcept
			{
				assert((err_id&3)==1);
				if( s_ )
					if( E * e = s_->has_value(err_id) )
						(void) f_(*e);
					else
						(void) f_(s_->put(err_id, E()));
			}
		};

		template <class... F>
		class accumulating
		{
			accumulating & operator=( accumulating const & ) = delete;
			std::tuple<accumulating_item<F>...> a_;
			bool moved_;
			int err_id_;

		public:

			explicit accumulating( F && ... f ) noexcept:
				a_(accumulating_item<F>(std::forward<F>(f))...),
				moved_(false),
				err_id_(last_id())
			{
			}

			accumulating( accumulating && x ) noexcept:
				a_(std::move(x.a_)),
				moved_(false),
				err_id_(x.err_id_)
			{
				x.moved_ = true;
			}

			~accumulating() noexcept
			{
				if( moved_ )
					return;
				int const err_id = last_id();
				if( err_id==err_id_ )
				{
#ifndef LEAF_NO_EXCEPTIONS
					if( std::uncaught_exception() )
						leaf_detail::tuple_for_each_preload<sizeof...(F),decltype(a_)>::trigger(a_,next_id());
#endif
				}
				else
					leaf_detail::tuple_for_each_preload<sizeof...(F),decltype(a_)>::trigger(a_,err_id);
			}
		};
	} // leaf_detail

	template <class... F>
	inline leaf_detail::accumulating<F...> accumulate( F && ... f ) noexcept
	{
		return leaf_detail::accumulating<F...>(std::forward<F>(f)...);
	}

} }

#endif
// <<< #include <boost/leaf/preload.hpp>
#line 20 "../../include/boost/leaf/detail/all.hpp"
// >>> #include <boost/leaf/result.hpp>
#line 1 "boost/leaf/result.hpp"
#ifndef LEAF_2CD8E6B8CA8D11E8BD3B80D66CE5B91B
#define LEAF_2CD8E6B8CA8D11E8BD3B80D66CE5B91B

// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <climits>

namespace boost { namespace leaf {

	class bad_result:
		public std::exception,
		public error_id
	{
		char const * what() const noexcept final override
		{
			return "boost::leaf::bad_result";
		}

	public:

		explicit bad_result( error_id id ) noexcept:
			error_id(id)
		{
			assert(value());
		}
	};

	////////////////////////////////////////

	namespace leaf_detail
	{
		class result_discriminant
		{
			unsigned state_;

		public:

			enum kind_t
			{
				no_error = 0,
				err_id = 1,
				ctx_ptr = 2,
				val = 3
			};

			result_discriminant() noexcept
			{
			}

			explicit result_discriminant( error_id id ) noexcept:
				state_(id.value())
			{
				assert(state_==0 || (state_&3)==1);
			}

			struct kind_val { };
			explicit result_discriminant( kind_val ) noexcept:
				state_(val)
			{
			}

			struct kind_ctx_ptr { };
			explicit result_discriminant( kind_ctx_ptr ) noexcept:
				state_(ctx_ptr)
			{
			}

			kind_t kind() const noexcept
			{
				return kind_t(state_&3);
			}

			error_id get_error_id() const noexcept
			{
				assert(kind()==no_error || kind()==err_id);
				return leaf_detail::make_error_id(state_);
			}
		};
	}

	////////////////////////////////////////

	template <class T>
	class result
	{
		template <class U>
		friend class result;

		struct error_result
		{
			error_result( error_result && ) = default;
			error_result( error_result const & ) = delete;
			error_result & operator=( error_result const & ) = delete;

			result & r_;

			template <class U>
			operator result<U>() noexcept
			{
				assert(!r_);
				if( r_.what_.kind() == leaf_detail::result_discriminant::ctx_ptr )
					return result<U>(std::move(r_.ctx_));
				else
					return result<U>(std::move(r_.what_));
			}

			operator error_id() noexcept
			{
				assert(!r_);
				if( r_.what_.kind() == leaf_detail::result_discriminant::ctx_ptr )
					return r_.ctx_->propagate_captured_errors();
				else
					return r_.what_.get_error_id();
			}
		};

		leaf_detail::result_discriminant what_;

		union
		{
			T value_;
			context_ptr ctx_;
		};

		void destroy() const noexcept
		{
			using leaf_detail::result_discriminant;
			switch(this->what_.kind())
			{
			case result_discriminant::val:
				value_.~T();
				break;
			case result_discriminant::ctx_ptr:
				assert(!ctx_ || ctx_->captured_id_);
				ctx_.~context_ptr();
			default:
				break;
			}
		}

		template <class U>
		void move_from( result<U> && x ) noexcept
		{
			using leaf_detail::result_discriminant;
			auto x_what = x.what_;
			switch(x_what.kind())
			{
			case result_discriminant::val:
				(void) new(&value_) T(std::move(x.value_));
				break;
			case result_discriminant::ctx_ptr:
				assert(!x.ctx_ || x.ctx_->captured_id_);
				(void) new(&ctx_) context_ptr(std::move(x.ctx_));
			default:
				break;
			}
			what_ = x_what;
		}

		result( leaf_detail::result_discriminant && what ) noexcept:
			what_(std::move(what))
		{
			using leaf_detail::result_discriminant;
			assert(what_.kind()==result_discriminant::err_id || what_.kind()==result_discriminant::no_error);
		}

	public:

		typedef T value_type;

		~result() noexcept
		{
			destroy();
		}

		result( result && x ) noexcept
		{
			move_from(std::move(x));
		}

		template <class U>
		result( result<U> && x ) noexcept
		{
			move_from(std::move(x));
		}

		result():
			what_(leaf_detail::result_discriminant::kind_val{}),
			value_(T())
		{
		}

		result( T && v ) noexcept:
			what_(leaf_detail::result_discriminant::kind_val{}),
			value_(std::move(v))
		{
		}

		result( T const & v ):
			what_(leaf_detail::result_discriminant::kind_val{}),
			value_(v)
		{
		}

		result( error_id err ) noexcept:
			what_(err)
		{
		}

		result( std::error_code const & ec ) noexcept:
			what_(error_id(ec))
		{
		}

		result( context_ptr && ctx ) noexcept:
			what_(leaf_detail::result_discriminant::kind_ctx_ptr{}),
			ctx_(std::move(ctx))
		{
		}

		result & operator=( result && x ) noexcept
		{
			destroy();
			move_from(std::move(x));
			return *this;
		}

		template <class U>
		result & operator=( result<U> && x ) noexcept
		{
			destroy();
			move_from(std::move(x));
			return *this;
		}

		explicit operator bool() const noexcept
		{
			using leaf_detail::result_discriminant;
			return what_.kind() == result_discriminant::val;
		}

		T const & value() const
		{
			if( what_.kind() == leaf_detail::result_discriminant::val )
				return value_;
			else
				::boost::leaf::throw_exception(bad_result(get_error_id()));
		}

		T & value()
		{
			if( what_.kind() == leaf_detail::result_discriminant::val )
				return value_;
			else
				::boost::leaf::throw_exception(bad_result(get_error_id()));
		}

		T const & operator*() const
		{
			return value();
		}

		T & operator*()
		{
			return value();
		}

		T const * operator->() const
		{
			return &value();
		}

		T * operator->()
		{
			return &value();
		}

		error_id get_error_id() const noexcept
		{
			using leaf_detail::result_discriminant;
			assert(what_.kind()!=result_discriminant::val);
			return what_.kind()==result_discriminant::ctx_ptr ? ctx_->captured_id_ : what_.get_error_id();
		}

		error_result error() noexcept
		{
			return error_result{*this};
		}

		template <class... E>
		error_id load( E && ... e ) noexcept
		{
			return error_id(error()).load(std::forward<E>(e)...);
		}

		template <class... F>
		error_id accumulate( F && ... f ) noexcept
		{
			return error_id(error()).accumulate(std::forward<F>(f)...);
		}
	};

	////////////////////////////////////////

	template <>
	class result<void>:
		result<bool>
	{
		typedef result<bool> base;

		template <class U>
		friend class result;

		result( result<bool> && rb ):
			base(std::move(rb))
		{
		}

		result( leaf_detail::result_discriminant && what ) noexcept:
			base(std::move(what))
		{
		}

	public:

		typedef void value_type;

		~result() noexcept
		{
		}

		result( result && x ) noexcept:
			base(std::move(x))
		{
		}

		result() noexcept
		{
		}

		result( error_id err ) noexcept:
			base(err)
		{
		}

		result( std::error_code const & ec ) noexcept:
			base(ec)
		{
		}

		result( context_ptr && ctx ) noexcept:
			base(std::move(ctx))
		{
		}

		void value() const
		{
			(void) base::value();
		}

		void operator*() const
		{
			return value();
		}


		void operator->() const
		{
			return value();
		}

		using base::operator=;
		using base::operator bool;
		using base::get_error_id;
		using base::error;
		using base::load;
		using base::accumulate;
	};

	////////////////////////////////////////

	template <class R>
	struct is_result_type;

	template <class T>
	struct is_result_type<result<T>>: std::true_type
	{
	};
} }

#endif
// <<< #include <boost/leaf/result.hpp>
#line 21 "../../include/boost/leaf/detail/all.hpp"

#endif
