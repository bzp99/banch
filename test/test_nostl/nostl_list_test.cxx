#include "gtest/gtest.h"
#include "nostl/list.hxx"

TEST(ListTest, CreateEmptyIntList)
{
	// create empty list and check if its size is 0
	nostl::List<int> * foo = new nostl::List<int>;
	EXPECT_EQ(0, foo->size());
	delete foo;
}

TEST(ListTest, FillList)
{
	// fill new list with doubles like {0, .5, 1, 1.5, ..., 50}
	nostl::List<double> * foo = new nostl::List<double>;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo->append(static_cast<double>(i) / 2.0);
	}
	EXPECT_EQ(100, foo->size());
	delete foo;
}

TEST(ListTest, ClearList)
{
	// fill test with longs and test clearing
	nostl::List<long> * foo = new nostl::List<long>;
	for (unsigned int i = 0; i < 20; ++i)
	{
		foo->append(static_cast<long>(i) / 3.141592654);
	}
	EXPECT_EQ(20, foo->size());
	foo->clear();
	EXPECT_EQ(0, foo->size());
	delete foo;
}

TEST(ListTest, Iteration)
{
	// create new list and fill with ints like {200, 5, 1}
	nostl::List<int> * foo = new nostl::List<int>;
	foo->append(5);
	foo->append(1);
	foo->prepend(200);

	// test preindex iteration
	nostl::List<int>::Iterator i = foo->begin();
	EXPECT_EQ(200, *i);
	++i;
	EXPECT_EQ(5, *i);
	++i;
	EXPECT_EQ(1, *i);
	--i;
	EXPECT_EQ(5, *i);

	i = foo->end();
	EXPECT_EQ(1, *i);
	--i;
	EXPECT_EQ(5, *i);

	// test postindex iteration
	i = foo->begin();
	EXPECT_EQ(200, *(i++));
	EXPECT_EQ(5, *i);

	i = foo->end();
	EXPECT_EQ(1, *(i--));
	EXPECT_EQ(5, *i);

	delete foo;
}

TEST(ListTest, IterationOutOfRange)
{
	// create new list and fill with doubles like {10.5, 15.5, 20.5}
	nostl::List<double> * foo = new nostl::List<double>;
	foo->prepend(20.5);
	foo->prepend(15.5);
	foo->prepend(10.5);

	// try to under-iterate
	nostl::List<double>::Iterator i = foo->begin();
	--i;
	EXPECT_EQ(10.5, *(i--));
	EXPECT_EQ(10.5, *i);

	// try to over-iterate
	i = foo->end();
	++i;
	EXPECT_EQ(20.5, *(i++));
	EXPECT_EQ(20.5, *i);

	delete foo;
}
