#include "gtest/gtest.h"
#include "nostl/list.hxx"

TEST(ListTest, CreateEmptyIntList)
{
	nostl::List<int> * foo = new nostl::List<int>;
	EXPECT_EQ(0, foo->size());
	delete foo;
}

TEST(ListTest, FillList)
{
	nostl::List<double> * foo = new nostl::List<double>;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo->append((double) i / 2);
	}
	EXPECT_EQ(100, foo->size());
	delete foo;
}

TEST(ListTest, ClearList)
{
	nostl::List<long> * foo = new nostl::List<long>;
	for (unsigned int i = 0; i < 20; ++i)
	{
		foo->append((long) i / 3.1415);
	}
	EXPECT_EQ(20, foo->size());
	foo->clear();
	EXPECT_EQ(0, foo->size());
	delete foo;
}

TEST(ListTest, Iteration)
{
	nostl::List<int> * foo = new nostl::List<int>;
	foo->append(5);
	foo->append(1);
	foo->prepend(200);
	nostl::List<int>::Iterator i = foo->begin();
	EXPECT_EQ(200, *i);
	++i;
	EXPECT_EQ(5, *i);
	++i;
	EXPECT_EQ(1, *i);

	delete foo;
}

TEST(ListTest, IterationOutOfRange)
{
	nostl::List<double> * foo = new nostl::List<double>;
	foo->prepend(20.5);
	foo->prepend(15.5);
	foo->prepend(10.5);

	nostl::List<double>::Iterator i = foo->begin();
	--i;
	EXPECT_EQ(10.5, *i);

	i = foo->end();
	++i;
	EXPECT_EQ(20.5, *i);

	delete foo;
}
