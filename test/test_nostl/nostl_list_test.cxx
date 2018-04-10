#include "gtest/gtest.h"
#include "nostl/list.hxx"

TEST(ListTest, CreateEmptyIntList)
{
	nostl::List<int> * foo = new nostl::List<int>;
	EXPECT_EQ(0, foo->size());
}
