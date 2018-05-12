#include "catch/catch.hpp"
#include "nostl/set.hxx"

using namespace nostl;

TEST_CASE("Empty set can be created", "[set][sanity]")
{
	// create empty set and check if its size is 0
	Set<int> foo;
	REQUIRE( foo.size() == 0 );
}

TEST_CASE("A set can be filled", "[set]")
{
	// create new set with different doubles, namely {0, .5, 1, ..., 50}
	Set<double> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.insert(static_cast<double>(i) / 2.0);
	}

	SECTION("Filling works")
	{
		REQUIRE( foo.size() == 100 );
	}

	SECTION("Same elements cannot be readded")
	{
		foo.insert(1.0);
		foo.insert(0);

		REQUIRE( foo.size() == 100 );
	}
}

TEST_CASE("A set can be cleared", "[set]")
{
	// fill new set with doubles and test clearing
	Set<double> foo;
	for (unsigned int i = 0; i < 420; ++i)
	{
		foo.insert(static_cast<double>(i) / -2.718281828459);
	}

	REQUIRE( foo.size() == 420 );

	foo.clear();
	REQUIRE( foo.size() == 0 );
}

TEST_CASE("A set can be correctly copied", "[set]")
{
	// create Set with a few ints like {0, 1, ... 99}
	Set<int> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.insert(i);
	}

	// create another Set by copying the first one
	Set<int> bar = foo;

	// change a few elements in the copy and make sure original instance is left
	// unchaged
	bar.insert(30);
	bar.remove(13);
	bar.remove(0);
	REQUIRE( foo.size() != bar.size() );

	bar.clear();
	REQUIRE( bar.size() == 0 );
	REQUIRE( foo.size() == 100 );
}

TEST_CASE("A set can be correctly assigned to another one", "[set]")
{
	// create Set with a few ints like {0, 1, ..., 99}
	Set<int> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.insert(i);
	}

	// create another Set with a few other ints like {100, 101, ..., 999}
	Set<int> bar;
	for (unsigned int i = 100; i < 1000; ++i)
	{
		bar.insert(i);
	}

	// set foo to be the same as bar
	foo = bar;

	// see if assignment was correct and the two Lists are still different
	// instances
	REQUIRE( foo.size() == bar.size() );

	bar.insert(1000);
	REQUIRE_FALSE( foo.size() == bar.size() );
}

TEST_CASE("A set can be iterated", "[set][iteration]")
{
	// create new Set and fill with ints like {200, 5, 1}
	Set<int> foo;
	foo.insert(200);
	foo.insert(5);
	foo.insert(1);

	SECTION("Set iterator preindexing works")
	{
		Set<int>::Iterator i = foo.begin();
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

	SECTION("Set iterator postindexing works")
	{
		Set<int>::Iterator i = foo.begin();
		--i;
		REQUIRE( *(i++) == 200 );
		REQUIRE( *i == 5 );

		i = foo.end();
		--i;
		REQUIRE( *(i--) == 1 );
		REQUIRE( *i == 5 );
	}
}

TEST_CASE("Set iterators don't go out of range", "[set][iterators]")
{
	// create new Set and fill with doubles like {10.5, 15.5, 20.5}
	Set<double> foo;
	foo.insert(10.5);
	foo.insert(15.5);
	foo.insert(20.5);

	SECTION("Set iterators don't go below minimal value")
	{
		Set<double>::Iterator i = foo.begin();
		--i;
		REQUIRE( *(i--) == 10.5 );
		REQUIRE( *i == 10.5 );
	}

	SECTION("Set iterators don't go above maximal value")
	{
		Set<double>::Iterator i = foo.end();
		Set<double>::Iterator j = i;
		++i;
		REQUIRE( i == j );
	}
}

TEST_CASE("Elements can be removed from a set", "[set]")
{
	// create new Set with a few elements like {3, 4, 5, 40}
	Set<int> foo;
	foo.insert(3);
	foo.insert(4);
	foo.insert(5);
	foo.insert(40);

	// remove an element
	foo.remove(4); // --> {3, 5, 40}
	REQUIRE( foo.size() == 3 );

	Set<int>::Iterator i = foo.begin();
	REQUIRE( *(i++) == 3 );
	REQUIRE( *(i++) == 5 );
	REQUIRE( *i == 40 );

	// remove two more just for fun
	foo.remove(40); // --> {3, 5}
	REQUIRE( foo.size() == 2 );

	foo.remove(3); // --> {5}
	REQUIRE( foo.size() == 1 );

	i = foo.begin();
	REQUIRE( *i == 5 );

	// remove a nonexistent one
	foo.remove(3030); // --> {3, 5}
	REQUIRE( foo.size() == 1 );

	// remove the last one
	foo.remove(5); // --> {}
	REQUIRE( foo.size() == 0 );
}
