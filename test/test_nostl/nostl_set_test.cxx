#include "gtest/gtest.h"
#include "nostl/set.hxx"

TEST(SetTest, CreateEmpty)
{
	// create empty set and check if its size is 0
	nostl::Set<int> * foo = new nostl::Set<int>;
	EXPECT_EQ(0, foo->size());
	delete foo;
}

TEST(SetTest, Fill)
{
	// fill new set with different doubles, namely {0, .5, 1, ..., 50}
	nostl::Set<double> * foo = new nostl::Set<double>;
	for (unsigned int i = 0; i < 100; ++i)
	{
		foo->insert(static_cast<double>(i) / 2.0);
	}
	EXPECT_EQ(100, foo->size());

	// now try to add already existing elements
	foo->insert(1.0);
	foo->insert(0);
	EXPECT_EQ(100, foo->size());

	delete foo;
}

TEST(SetTest, Clear)
{
	// fill new set with longs and test clearing
	nostl::Set<long> * foo = new nostl::Set<long>;
	for (unsigned int i = 0; i < 420; ++i)
	{
		foo->insert(static_cast<long>(i) / -2.718281828459);
	}
	EXPECT_EQ(420, foo->size());
	foo->clear();
	EXPECT_EQ(0, foo->size());
	delete foo;
}
