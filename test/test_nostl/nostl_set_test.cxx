#include "gtest/gtest.h"
#include "nostl/set.hxx"

TEST(SetTest, CreateEmpty)
{
	// create empty set and check if its size is 0
	nostl::Set<int> foo;
	EXPECT_EQ(0, foo.size());
}

TEST(SetTest, Fill)
{
	// create new set with different doubles, namely {0, .5, 1, ..., 50}
	nostl::Set<double> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.insert(static_cast<double>(i) / 2.0);
	}
	EXPECT_EQ(100, foo.size());

	// now try to add already existing elements
	foo.insert(1.0);
	foo.insert(0);
	EXPECT_EQ(100, foo.size());
}

TEST(SetTest, Clear)
{
	// fill new set with doubles and test clearing
	nostl::Set<double> foo;
	for (unsigned int i = 0; i < 420; ++i)
	{
		foo.insert(static_cast<double>(i) / -2.718281828459);
	}
	EXPECT_EQ(420, foo.size());
	foo.clear();
	EXPECT_EQ(0, foo.size());
}

TEST(SetTest, Copy)
{
	// create Set with a few ints like {0, 1, ... 99}
	nostl::Set<int> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.insert(i);
	}

	// create another Set by copying the first one
	nostl::Set<int> bar = foo;

	// change a few elements in the copy and make sure original instance is left
	// unchaged
	bar.insert(30);
	bar.remove(13);
	bar.remove(0);
	EXPECT_NE(foo.size(), bar.size());
	bar.clear();
	EXPECT_EQ(0, bar.size());
	EXPECT_EQ(100, foo.size());
}

TEST(SetTest, Assign)
{
	// create Set with a few ints like {0, 1, ..., 99}
	nostl::Set<int> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.insert(i);
	}

	// create another Set with a few other ints like {100, 101, ..., 999}
	nostl::Set<int> bar;
	for (unsigned int i = 100; i < 1000; ++i)
	{
		bar.insert(i);
	}

	// make sure the two Sets differ (obviously...)
	EXPECT_NE(foo.size(), bar.size());

	// set foo to be the same as bar
	foo = bar;

	// see if assignment was correct and the two Lists are still different
	// instances
	EXPECT_EQ(foo.size(), bar.size());
	bar.insert(1000);
	EXPECT_NE(foo.size(), bar.size());
}

TEST(SetTest, Iteration)
{
	// create new Set and fill with ints like {200, 5, 1}
	nostl::Set<int> foo;
	foo.insert(200);
	foo.insert(5);
	foo.insert(1);

	// test preindex iteration
	nostl::Set<int>::Iterator i = foo.begin();
	EXPECT_EQ(200, *i);
	++i;
	EXPECT_EQ(5, *i);
	++i;
	EXPECT_EQ(1, *i);
	--i;
	EXPECT_EQ(5, *i);

	i = foo.end();
	EXPECT_EQ(1, *i);
	--i;
	EXPECT_EQ(5, *i);

	// test postindex iteration
	i = foo.begin();
	EXPECT_EQ(200, *(i++));
	EXPECT_EQ(5, *i);

	i = foo.end();
	EXPECT_EQ(1, *(i--));
	EXPECT_EQ(5, *i);
}

TEST(SetTest, IterationOutOfRange)
{
	// create new Set and fill with doubles like {10.5, 15.5, 20.5}
	nostl::Set<double> foo;
	foo.insert(10.5);
	foo.insert(15.5);
	foo.insert(20.5);

	// try to under-iterate
	nostl::Set<double>::Iterator i = foo.begin();
	--i;
	EXPECT_EQ(10.5, *(i--));
	EXPECT_EQ(10.5, *i);

	// try to over-iterate
	i = foo.end();
	++i;
	EXPECT_EQ(20.5, *(i++));
	EXPECT_EQ(20.5, *i);
}

TEST(SetTest, Removal)
{
	// create new Set with a few elements like {3, 30, 3, 30}
	nostl::Set<int> foo;
	foo.insert(3);
	foo.insert(30);
	foo.insert(3);
	foo.insert(30);
	EXPECT_EQ(4, foo.size());

	// remove an element
	foo.remove(30); // --> {3, 3, 30}
	nostl::Set<int>::Iterator i = foo.begin();
	EXPECT_EQ(3, *(i++));
	EXPECT_EQ(3, *(i++));
	EXPECT_EQ(30, *i);
	EXPECT_EQ(3, foo.size());

	// remove two more just for fun
	foo.remove(30); // --> {3, 3}
	EXPECT_EQ(2, foo.size());
	foo.remove(3); // --> {3}
	i = foo.begin();
	EXPECT_EQ(3, *i);
	EXPECT_EQ(1, foo.size());
}
