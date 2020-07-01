#ifndef BOOST_LEAF_DETAIL_HANDLER_ARGUMENT_TRAITS_HPP_INCLUDED
#define BOOST_LEAF_DETAIL_HANDLER_ARGUMENT_TRAITS_HPP_INCLUDED

// Copyright (c) 2018-2020 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if defined(__clang__)
#	pragma clang system_header
#elif (__GNUC__*100+__GNUC_MINOR__>301) && !defined(BOOST_LEAF_ENABLE_WARNINGS)
#	pragma GCC system_header
#elif defined(_MSC_VER) && !defined(BOOST_LEAF_ENABLE_WARNINGS)
#	pragma warning(push,1)
#endif

#include <boost/leaf/detail/unexpected.hpp>
#include <utility>
#include <exception>

namespace boost { namespace leaf {

	class error_info;
	class diagnostic_info;
	class verbose_diagnostic_info;

	namespace leaf_detail
	{
		template <class MatchType>
		BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE bool cmp_value_pack( MatchType const & x, bool (*pred)(MatchType const &) noexcept ) noexcept
		{
			BOOST_LEAF_ASSERT(pred != 0);
			return pred(x);
		}

		template <class MatchType, class V>
		BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE bool cmp_value_pack( MatchType const & x, V v ) noexcept
		{
			return x == v;
		}

		template <class MatchType, class VCar, class... VCdr>
		BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE bool cmp_value_pack( MatchType const & x, VCar car, VCdr ... cdr ) noexcept
		{
			return cmp_value_pack(x, car) || cmp_value_pack(x, cdr...);
		}
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		struct diagnostic_info_;
		struct verbose_diagnostic_info_;

		template <class A, bool RequiresCatch = std::is_base_of<std::exception, typename std::decay<A>::type>::value>
		struct handler_argument_traits_defaults
		{
			using error_type = typename std::decay<A>::type;
			constexpr static bool requires_catch = RequiresCatch;
			constexpr static bool always_available = false;

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static error_type const * check( Tup const &, error_info const & ) noexcept;

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static error_type * check( Tup &, error_info const & ) noexcept;

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static A get( Tup & tup, error_info const & ei ) noexcept
			{
				return *check(tup, ei);
			}

			static_assert(!std::is_same<A, error_info>::value, "Handlers must take leaf::error_info arguments by const &");
			static_assert(!std::is_same<A, diagnostic_info>::value, "Handlers must take leaf::diagnostic_info arguments by const &");
			static_assert(!std::is_same<A, verbose_diagnostic_info>::value, "Handlers must take leaf::verbose_diagnostic_info arguments by const &");
		};

		template <class A>
		struct handler_argument_always_available
		{
			using error_type = A;
			constexpr static bool requires_catch = false;
			constexpr static bool always_available = true;

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static bool check( Tup &, error_info const & ) noexcept
			{
				return true;
			};
		};

		template <class A>
		struct handler_argument_traits: handler_argument_traits_defaults<A>
		{
		};

		template <class A>
		struct handler_argument_traits<A &&>
		{
			static_assert(sizeof(A) == 0, "Error handlers may not take rvalue ref arguments");
		};

		template <class A>
		struct handler_argument_traits<A *>: handler_argument_always_available<typename std::remove_const<A>::type>
		{
			template <class Tup>
			static A * get( Tup & tup, error_info const & ei) noexcept
			{
				return handler_argument_traits_defaults<A>::check(tup, ei);
			}
		};

		template <>
		struct handler_argument_traits<error_info const &>: handler_argument_always_available<void>
		{
			template <class Tup>
			static error_info const & get( Tup const &, error_info const & ei ) noexcept
			{
				return ei;
			}
		};

		template <>
		struct handler_argument_traits<diagnostic_info const &>: handler_argument_always_available<e_unexpected_count>
		{
			template <class Tup>
			BOOST_LEAF_CONSTEXPR static diagnostic_info_ get( Tup const & tup, error_info const & ei ) noexcept;
		};

		template <>
		struct handler_argument_traits<verbose_diagnostic_info const &>: handler_argument_always_available<e_unexpected_info>
		{
			template <class Tup>
			BOOST_LEAF_CONSTEXPR static verbose_diagnostic_info_ get( Tup const & tup, error_info const & ei ) noexcept;
		};

		template <class P, class A, bool RequiresCatch>
		struct handler_argument_pred
		{
			using error_type = typename handler_argument_traits<A>::error_type;
			constexpr static bool requires_catch = RequiresCatch;
			constexpr static bool always_available = false;

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static bool check( Tup & tup, error_info const & ei ) noexcept
			{
				if( auto * a = handler_argument_traits<A>::check(tup, ei) )
					if( P(*a) )
						return true;
				return false;
			};

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static P get( Tup const & tup, error_info const & ei ) noexcept
			{
				return P(*handler_argument_traits<A>::check(tup, ei));
			}
		};

		template <class T>
		struct bad_predicate
		{
			static_assert(sizeof(T) == 0, "Error handlers must take predicates by value");
		};
	}

	////////////////////////////////////////

#if __cplusplus >= 201703L
#	define BOOST_LEAF_MATCH_ARGS(t,v1,v) auto v1, auto... v
#else
#	define BOOST_LEAF_MATCH_ARGS(t,v1,v) typename leaf_detail::t<E>::enum_type v1, typename leaf_detail::t<E>::enum_type... v
#endif

	namespace leaf_detail
	{
		template <class E>
		struct match_traits;
	}

	template <class E, BOOST_LEAF_MATCH_ARGS(match_traits, V1, V)>
	struct match;

	namespace leaf_detail
	{
		template <class E, BOOST_LEAF_MATCH_ARGS(match_traits, V1, V)>
		struct handler_argument_traits<match<E, V1, V...>>: handler_argument_pred<match<E, V1, V...>, typename match_traits<E>::error_type, handler_argument_traits<E>::requires_catch>
		{
			static_assert(std::is_same<bool, decltype(cmp_value_pack(std::declval<typename match_traits<E>::error_type>(), V1))>::value,
				"The predicate match<E, V...> requires that objects of type E can be compared to the values V...");
		};

		template <class E, BOOST_LEAF_MATCH_ARGS(match_traits, V1, V)> struct handler_argument_traits<match<E, V1, V...> const &>: bad_predicate<match<E, V1, V...>> { };
		template <class E, BOOST_LEAF_MATCH_ARGS(match_traits, V1, V)> struct handler_argument_traits<match<E, V1, V...> const *>: bad_predicate<match<E, V1, V...>> { };
		template <class E, BOOST_LEAF_MATCH_ARGS(match_traits, V1, V)> struct handler_argument_traits<match<E, V1, V...> &>: bad_predicate<match<E, V1, V...>> { };
		template <class E, BOOST_LEAF_MATCH_ARGS(match_traits, V1, V)> struct handler_argument_traits<match<E, V1, V...> *>: bad_predicate<match<E, V1, V...>> { };
	}

	////////////////////////////////////////

	namespace leaf_detail
	{
		template <class E>
		struct match_value_traits;
	}

	template <class E, BOOST_LEAF_MATCH_ARGS(match_value_traits, V1, V)>
	struct match_value;

	namespace leaf_detail
	{
		template <class E, BOOST_LEAF_MATCH_ARGS(match_value_traits, V1, V)>
		struct handler_argument_traits<match_value<E, V1, V...>>: handler_argument_pred<match_value<E, V1, V...>, typename match_value_traits<E>::error_type, handler_argument_traits<E>::requires_catch>
		{
			static_assert(std::is_same<bool, decltype(cmp_value_pack(std::declval<typename match_value_traits<E>::error_type>().value, V1))>::value,
				"The predicate match_value<E, V...> requires that objects of type E have a data member .value that can be compared to the values V...");
		};

		template <class E, BOOST_LEAF_MATCH_ARGS(match_value_traits, V1, V)> struct handler_argument_traits<match_value<E, V1, V...> const &>: bad_predicate<match_value<E, V1, V...>> { };
		template <class E, BOOST_LEAF_MATCH_ARGS(match_value_traits, V1, V)> struct handler_argument_traits<match_value<E, V1, V...> const *>: bad_predicate<match_value<E, V1, V...>> { };
		template <class E, BOOST_LEAF_MATCH_ARGS(match_value_traits, V1, V)> struct handler_argument_traits<match_value<E, V1, V...> &>: bad_predicate<match_value<E, V1, V...>> { };
		template <class E, BOOST_LEAF_MATCH_ARGS(match_value_traits, V1, V)> struct handler_argument_traits<match_value<E, V1, V...> *>: bad_predicate<match_value<E, V1, V...>> { };
	}

	////////////////////////////////////////

#if __cplusplus >= 201703L

	template <auto, auto, auto...>
	struct match_member;

	template <class T, class E, T E::* P, auto V1, auto... V>
	struct match_member<P, V1, V...>;

	namespace leaf_detail
	{
		template <class T, class E, T E::* P, auto V1, auto... V>
		struct handler_argument_traits<match_member<P, V1, V...>>: handler_argument_pred<match_member<P, V1, V...>, E const &, handler_argument_traits<E>::requires_catch>
		{
			static_assert(std::is_same<bool, decltype(cmp_value_pack(std::declval<E>().*P, V1))>::value,
				"The predicate match_member<&E::m, V...> requires that objects of type E have a data member m that can be compared to the values V...");
		};

		template <class T, class E, T E::* P, auto V1, auto... V> struct handler_argument_traits<match_member<P, V1, V...> const &>: bad_predicate<match_member<P, V1, V...>> { };
		template <class T, class E, T E::* P, auto V1, auto... V> struct handler_argument_traits<match_member<P, V1, V...> const *>: bad_predicate<match_member<P, V1, V...>> { };
		template <class T, class E, T E::* P, auto V1, auto... V> struct handler_argument_traits<match_member<P, V1, V...> &>: bad_predicate<match_member<P, V1, V...>> { };
		template <class T, class E, T E::* P, auto V1, auto... V> struct handler_argument_traits<match_member<P, V1, V...> *>: bad_predicate<match_member<P, V1, V...>> { };
	}

#endif

	////////////////////////////////////////

	template <class... Ex>
	class catch_;

	namespace leaf_detail
	{
		template <class... Ex>
		struct handler_argument_traits<catch_<Ex...>>: handler_argument_pred<catch_<Ex...>, std::exception, true>
		{
		};

		template <class... Ex> struct handler_argument_traits<catch_<Ex...> const &>: bad_predicate<catch_<Ex...>> { };
		template <class... Ex> struct handler_argument_traits<catch_<Ex...> const *>: bad_predicate<catch_<Ex...>> { };
		template <class... Ex> struct handler_argument_traits<catch_<Ex...> &>: bad_predicate<catch_<Ex...>> { };
		template <class... Ex> struct handler_argument_traits<catch_<Ex...> *>: bad_predicate<catch_<Ex...>> { };
	}

} }

// Boost Exception Integration below

namespace boost { template <class Tag,class T> class error_info; }

namespace boost { namespace leaf {

	namespace leaf_detail
	{
		template <class Tag, class T>
		struct handler_argument_traits<boost::error_info<Tag, T>>
		{
			using error_type = void;
			constexpr static bool requires_catch = true;
			constexpr static bool always_available = false;

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static T * check( Tup &, error_info const & ) noexcept;

			template <class Tup>
			BOOST_LEAF_CONSTEXPR static boost::error_info<Tag, T> get( Tup const &, error_info const & ) noexcept;
		};

		template <class T>
		struct bad_boost_error_info
		{
			static_assert(sizeof(T) == 0, "Error handlers must take boost::error_info<> by value");
		};

		template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> const &>: bad_boost_error_info<boost::error_info<Tag, T>> { };
		template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> const *>: bad_boost_error_info<boost::error_info<Tag, T>> { };
		template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> &>: bad_boost_error_info<boost::error_info<Tag, T>> { };
		template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> *>: bad_boost_error_info<boost::error_info<Tag, T>> { };
	}

} }

#endif
