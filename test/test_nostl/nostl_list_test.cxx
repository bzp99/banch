#include "catch/catch.hpp"
#include "nostl/list.hxx"

using namespace nostl;

TEST_CASE("Empty list can be created", "[list][sanity]")
{
	// create empty List and check if its size is 0
	List<int> foo;
	REQUIRE( foo.size() == 0 );
}

TEST_CASE("A list can be filled", "[list]")
{
	// create List with doubles like {0, .5, 1, 1.5, ..., 50}
	List<double> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.append(static_cast<double>(i) / 2.0);
	}

	REQUIRE( foo.size() == 100 );
}

TEST_CASE("A list can be cleared", "[list]")
{
	// create List with longs and test clearing
	List<long> foo;
	for (unsigned int i = 0; i < 20; ++i)
	{
		foo.append(static_cast<long>(i) / 3.141592654);
	}

	REQUIRE( foo.size() == 20 );

	foo.clear();

	REQUIRE( foo.size() == 0);
}

TEST_CASE("A list can be correctly copied", "[list]")
{
	// create List with a few ints like {0, 1, ..., 99}
	List<int> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.append(i);
	}

	// create another List by copying the first one
	List<int> bar = foo;

	// change a few elements in the copy and make sure original instance is left
	// unchanged
	bar.remove(13);
	bar.remove(0);

	REQUIRE( foo.size() != bar.size() );

	bar.clear();

	REQUIRE( bar.size() == 0 );
	REQUIRE( foo.size() == 100 );
}

TEST_CASE("A list can be assigned another list", "[list]")
{
	// create List with a few ints like {0, 1, ..., 99}
	List<int> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.append(i);
	}

	// create another List with a few other ints like {100, 101, ..., 999}
	List<int> bar;
	for (unsigned int i = 100; i < 1000; ++i)
	{
		bar.append(i);
	}

	// make sure the two Lists differ (obviously...)
	REQUIRE( foo.size() != bar.size() );

	// set foo to be the same as bar
	foo = bar;

	// see if assignment was correct and the two Lists are still different
	// instances
	REQUIRE( foo.size() == bar.size() );

	bar.append(1000);

	REQUIRE_FALSE( foo.size() == bar.size() );
}

TEST_CASE("A list can be iterated", "[list][iterators]")
{
	// create new List and fill with ints like {200, 5, 1}
	List<int> foo;
	foo.append(5);
	foo.append(1);
	foo.prepend(200);

	SECTION("List iterators can be preindexed")
	{
		List<int>::Iterator i = foo.begin();
		REQUIRE( *i == 200 );

		++i;
		REQUIRE( *i == 5 );

		++i;
		REQUIRE( *i == 1 );

		--i;
		REQUIRE( *i == 5 );

		i = foo.end();
		--i;
		REQUIRE( *i == 1 );

		--i;
		REQUIRE( *i == 5 );
	}

	SECTION("List iterators can be postindexed")
	{
		List<int>::Iterator i = foo.begin();
		REQUIRE( *(i++) == 200 );
		REQUIRE( *i == 5 );

		i = foo.end();
		--i;
		REQUIRE( *(i--) == 1 );
		REQUIRE( *i == 5 );
	}
}

TEST_CASE("List iterators don't go out of range", "[list][iterators]")
{
	// create new List and fill with doubles like {10.5, 15.5, 20.5}
	List<double> foo;
	foo.prepend(20.5);
	foo.prepend(15.5);
	foo.prepend(10.5);

	SECTION("List iterators don't go below minimal value")
	{
		List<double>::Iterator i = foo.begin();
		--i;
		REQUIRE( *(i--) == 10.5 );
		REQUIRE( *i == 10.5 );
	}

	SECTION("List iterators don't go above maximal value")
	{
		List<double>::Iterator i = foo.end();
		List<double>::Iterator j = i;
		++i;
		REQUIRE( i == j );
	}
}

TEST_CASE("Elements can be removed from a list", "[list]")
{
	// create new List with a few elements like {3, 30, 3, 30}
	List<int> foo;
	foo.append(3);
	foo.append(30);
	foo.append(3);
	foo.append(30);

	// remove an element
	foo.remove(30); // --> {3, 3, 30}
	REQUIRE( foo.size() == 3 );

	List<int>::Iterator i = foo.begin();
	REQUIRE( *(i++) == 3 );
	REQUIRE( *(i++) == 3 );
	REQUIRE( *i == 30 );

	// remove two more just for fun
	foo.remove(30); // --> {3, 3}
	REQUIRE( foo.size() == 2 );

	foo.remove(3); // --> {3}
	REQUIRE( foo.size() == 1 );

	i = foo.begin();
	REQUIRE( *i == 3 );
}
