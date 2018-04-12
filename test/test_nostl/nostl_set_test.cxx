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
