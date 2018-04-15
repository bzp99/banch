#include "gtest/gtest.h"
#include "nostl/list.hxx"

TEST(ListTest, CreateEmpty)
{
	// create empty list and check if its size is 0
	nostl::List<int> foo;
	EXPECT_EQ(0, foo.size());
}

TEST(ListTest, Fill)
{
	// fill new list with doubles like {0, .5, 1, 1.5, ..., 50}
	nostl::List<double> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.append(static_cast<double>(i) / 2.0);
	}
	EXPECT_EQ(100, foo.size());
}

TEST(ListTest, Clear)
{
	// fill list with longs and test clearing
	nostl::List<long> foo;
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
	// create empty list with a few ints like {1, 2, ..., 100}
	nostl::List<int> foo;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo.append(i);
	}

	// create another list by copying the first one
	nostl::List<int> bar = foo;

	// change a few elements in the copy and make sure original instance is left
	// unchanged
	bar.remove(13);
	bar.remove(0);
	EXPECT_NEQ(foo.size(), bar.size());
	bar.clear();
	EXPECT_EQ(0, bar.size());
	EXPECT_EQ(100, foo.size());
}

TEST(ListTest, Iteration)
{
	// create new list and fill with ints like {200, 5, 1}
	nostl::List<int> foo;
	foo.append(5);
	foo.append(1);
	foo.prepend(200);

	// test preindex iteration
	nostl::List<int>::Iterator i = foo.begin();
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
	// create new list and fill with doubles like {10.5, 15.5, 20.5}
	nostl::List<double> foo;
	foo.prepend(20.5);
	foo.prepend(15.5);
	foo.prepend(10.5);

	// try to under-iterate
	nostl::List<double>::Iterator i = foo.begin();
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
	// create new list with a few elements like {3, 30, 3, 30}
	nostl::List<int> foo;
	foo.append(3);
	foo.append(30);
	foo.append(3);
	foo.append(30);
	EXPECT_EQ(4, foo.size());

	// remove an element
	foo.remove(30);
	nostl::List<int>::Iterator i = foo.begin();
	EXPECT_EQ(3, *(i++));
	EXPECT_EQ(3, *(i++));
	EXPECT_EQ(30, *i);
	EXPECT_EQ(3, foo.size());

	// remove two more just for fun
	foo.remove(30);
	EXPECT_EQ(2, foo.size()); // FIXME this fails
	foo.remove(3);
	i = foo.begin();
	EXPECT_EQ(3, *i);
	EXPECT_EQ(1, foo.size());
}
