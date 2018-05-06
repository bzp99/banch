#include "gtest/gtest.h"
#include "nostl/list.hxx"

using namespace nostl;

TEST(ListTest, CreateEmpty)
{
	// create empty List and check if its size is 0
	List<int> foo;
	EXPECT_EQ(0, foo.size());
}

TEST(ListTest, Fill)
{
	// create List with doubles like {0, .5, 1, 1.5, ..., 50}
	List<double> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.append(static_cast<double>(i) / 2.0);
	}
	EXPECT_EQ(100, foo.size());
}

TEST(ListTest, Clear)
{
	// create List with longs and test clearing
	List<long> foo;
	for (unsigned int i = 0; i < 20; ++i)
	{
		foo.append(static_cast<long>(i) / 3.141592654);
	}
	EXPECT_EQ(20, foo.size());
	foo.clear();
	EXPECT_EQ(0, foo.size());
}

TEST(ListTest, Copy)
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
	EXPECT_NE(foo.size(), bar.size());
	bar.clear();
	EXPECT_EQ(0, bar.size());
	EXPECT_EQ(100, foo.size());
}

TEST(ListTest, Assign)
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
	EXPECT_NE(foo.size(), bar.size());

	// set foo to be the same as bar
	foo = bar;

	// see if assignment was correct and the two Lists are still different
	// instances
	EXPECT_EQ(foo.size(), bar.size());
	bar.append(1000);
	EXPECT_NE(foo.size(), bar.size());
}

TEST(ListTest, Iteration)
{
	// create new List and fill with ints like {200, 5, 1}
	List<int> foo;
	foo.append(5);
	foo.append(1);
	foo.prepend(200);

	// test preindex iteration
	List<int>::Iterator i = foo.begin();
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

TEST(ListTest, IterationOutOfRange)
{
	// create new List and fill with doubles like {10.5, 15.5, 20.5}
	List<double> foo;
	foo.prepend(20.5);
	foo.prepend(15.5);
	foo.prepend(10.5);

	// try to under-iterate
	List<double>::Iterator i = foo.begin();
	--i;
	EXPECT_EQ(10.5, *(i--));
	EXPECT_EQ(10.5, *i);

	// try to over-iterate
	i = foo.end();
	++i;
	EXPECT_EQ(20.5, *(i++));
	EXPECT_EQ(20.5, *i);
}

TEST(ListTest, Removal)
{
	// create new List with a few elements like {3, 30, 3, 30}
	List<int> foo;
	foo.append(3);
	foo.append(30);
	foo.append(3);
	foo.append(30);
	EXPECT_EQ(4, foo.size());

	// remove an element
	foo.remove(30); // --> {3, 3, 30}
	List<int>::Iterator i = foo.begin();
	EXPECT_EQ(3, *(i++));
	EXPECT_EQ(3, *(i++));
	EXPECT_EQ(30, *i);
	EXPECT_EQ(3, foo.size());

	// remove two more just for fun
	foo.remove(30); // --> {3, 3}
	EXPECT_EQ(2, foo.size()); // FIXME this fails
	foo.remove(3); // --> {3}
	i = foo.begin();
	EXPECT_EQ(3, *i);
	EXPECT_EQ(1, foo.size());
}
