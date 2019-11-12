// Copyright (c) 2018-2019 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/result.hpp>
#include <boost/leaf/capture.hpp>
#include <boost/leaf/handle_error.hpp>
#include "lightweight_test.hpp"

namespace leaf = boost::leaf;

struct val
{
	static int id_count;
	static int count;
	int id;

	val():
		id(++id_count)
	{
		++count;
	}

	val( val const & x ):
		id(x.id)
	{
		++count;
	}

	val( val && x ):
		id(x.id)
	{
		++count;
	}

	~val()
	{
		--count;
	}

	friend bool operator==( val const & a, val const & b )
	{
		return a.id==b.id;
	}
};
int val::count = 0;
int val::id_count = 0;

struct err
{
	static int count;

	err()
	{
		++count;
	}

	err( err const & )
	{
		++count;
	}

	err( err && )
	{
		++count;
	}

	~err()
	{
		--count;
	}
};
int err::count = 0;
struct e_err { err value; };

bool eq_value( leaf::result<val> & r1, leaf::result<val> & r2 )
{
	leaf::result<val> const & cr1 = r1;
	leaf::result<val> const & cr2 = r2;
	return
		r1.value()==r2.value() &&
		cr1.value()==cr2.value() &&
		*r1==*r2 &&
		*cr1==*cr2 &&
		r1->id==r2->id &&
		cr1->id==cr2->id;
}

int main()
{
	{ // value default -> copy
		leaf::result<val> r1;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> copy
		leaf::result<val> r1 = val();
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> copy
		val v;
		leaf::result<val> r1 = v;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		leaf::result<val> r2 = r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 3);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // value default -> move
		leaf::result<val> r1;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> move
		leaf::result<val> r1 = val();
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> move
		val v;
		leaf::result<val> r1 = v;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 3);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // value default -> assign-copy
		leaf::result<val> r1;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> assign-copy
		leaf::result<val> r1 = val();
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> assign-copy
		val v;
		leaf::result<val> r1 = v;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 3);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // value default -> assign-move
		leaf::result<val> r1;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> assign-move
		leaf::result<val> r1 = val();
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> assign-move
		val v;
		leaf::result<val> r1 = v;
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 3);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	using context_type = leaf::leaf_detail::polymorphic_context_impl<leaf::context<e_err>>;

	{ // value default -> capture -> copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> capture -> copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(val()); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> capture -> copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ val v; return leaf::result<val>(v); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // value default -> capture -> move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> capture -> move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(val()); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> capture -> move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ val v; return leaf::result<val>(v); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // value default -> capture -> assign-copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> capture -> assign-copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(val()); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> capture -> assign-copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ val v; return leaf::result<val>(v); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		BOOST_TEST(eq_value(r1,r2));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // value default -> capture -> assign-move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value move -> capture -> assign-move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>(val()); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // value copy -> capture -> assign-move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ val v; return leaf::result<val>(v); } );
		BOOST_TEST(r1);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 1);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(r2);
		BOOST_TEST_EQ(err::count, 0);
		BOOST_TEST_EQ(val::count, 2);
		}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	// ^^ value ^^
	// vv error vv

	{ // error move -> copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::do_not_propagate);
		leaf::result<val> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::do_not_propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<val> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // error move -> move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::do_not_propagate);
		leaf::result<val> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<val> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // error move -> assign copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::result<val> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> assign copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<val> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // error move -> assign move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::result<val> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		{
			val x;
			BOOST_TEST(ctx.handle_all(r2, [&]{ return x; }) == x);
		}
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> assign move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<val> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // error move -> capture -> copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> capture -> copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), [] { leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<val>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // error move -> capture -> move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST(!r1);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> capture -> move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<val>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST(!r1);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // error move -> capture -> assign-copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> capture -> assign-copy
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<val>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	{ // error move -> capture -> assign-move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<val>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST(!r1);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);
	{ // error copy -> capture -> assign-move
		leaf::result<val> r1 = leaf::capture( std::make_shared<context_type>(), []{ leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<val>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		BOOST_TEST_EQ(val::count, 0);
		leaf::result<val> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST(!r1);
	}
	BOOST_TEST_EQ(err::count, 0);
	BOOST_TEST_EQ(val::count, 0);

	// ^^ result<T> ^^

	/////////////////////////////////////////////////////////////

	// vv result<void> vv

	{ // void default -> copy
		leaf::result<void> r1;
		BOOST_TEST(r1);
		leaf::result<void> r2 = r1;
		BOOST_TEST(r2);
	}

	{ // void default -> move
		leaf::result<void> r1;
		BOOST_TEST(r1);
		leaf::result<void> r2 = std::move(r1);
		BOOST_TEST(r2);
	}

	{ // void default -> assign-copy
		leaf::result<void> r1;
		BOOST_TEST(r1);
		leaf::result<void> r2; r2=r1;
		BOOST_TEST(r2);
	}

	{ // void default -> assign-move
		leaf::result<void> r1;
		BOOST_TEST(r1);
		leaf::result<void> r2; r2=std::move(r1);
		BOOST_TEST(r2);
	}

	{ // void default -> capture -> copy
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>(); } );
		BOOST_TEST(r1);
		leaf::result<void> r2 = r1;
		BOOST_TEST(r2);
	}

	{ // void default -> capture -> move
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>(); } );
		BOOST_TEST(r1);
		leaf::result<void> r2 = std::move(r1);
		BOOST_TEST(r2);
	}

	{ // void default -> capture -> assign-copy
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>(); } );
		BOOST_TEST(r1);
		leaf::result<void> r2; r2=r1;
		BOOST_TEST(r2);
	}

	{ // void default -> capture -> assign-move
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>(); } );
		BOOST_TEST(r1);
		leaf::result<void> r2; r2=std::move(r1);
		BOOST_TEST(r2);
	}

	// ^^ void default ^^
	// vv void error vv

	{ // void error move -> copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::do_not_propagate);
		leaf::result<void> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::do_not_propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<void> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{ // void error move -> move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::do_not_propagate);
		leaf::result<void> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<void> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{ // void error move -> assign copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::result<void> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> assign copy
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<void> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{ // void error move -> assign move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::result<void> r1 = leaf::new_error( e_err { } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		ctx.handle_all(r2, []{ });
		BOOST_TEST_EQ(err::count, 1);
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> assign move
		context_type ctx;
		auto active_context = activate_context(ctx, leaf::on_deactivation::propagate);
		leaf::error_id err = leaf::new_error( e_err{ } );
		leaf::result<void> r1 = err;
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{ // void error move -> capture -> copy
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> capture -> copy
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), [] { leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<void>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{ // void error move -> capture -> move
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> capture -> move
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<void>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2 = std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{ // void error move -> capture -> assign-copy
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> capture -> assign-copy
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<void>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=r1;
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{ // void error move -> capture -> assign-move
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ return leaf::result<void>( leaf::new_error( e_err { } ) ); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);
	{ // void error copy -> capture -> assign-move
		leaf::result<void> r1 = leaf::capture( std::make_shared<context_type>(), []{ leaf::error_id err = leaf::new_error( e_err{ } ); return leaf::result<void>(err); } );
		BOOST_TEST(!r1);
		BOOST_TEST_EQ(err::count, 1);
		leaf::result<void> r2; r2=std::move(r1);
		BOOST_TEST(!r2);
		BOOST_TEST_EQ(leaf::error_id(r1.error()), leaf::error_id(r2.error()));
	}
	BOOST_TEST_EQ(err::count, 0);

	{
		leaf::result<int> r;
		BOOST_TEST(r);
	}
	{
		leaf::result<void> r;
		BOOST_TEST(r);
	}

	return boost::report_errors();
}
