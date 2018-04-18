#include "gtest/gtest.h"

TEST(MeasureTest, SanityCheck)
{
	// create a few allowed Measures
	Measure<int> foo("kg", 120);
	Measure<double> bar("L", 3.4)

	// create disallowed Measures
	EXPECT_DEATH(Measure<nostl::String> baz("fail", "fail"),
					"Invalid template parameter assertion works!";)

	// print Measures
	std::stringstream ss;
	ss << foo;
	EXPECT_STREQ("120 kg", ss.str().c_str());
	ss.str("");
	ss.clear();
	ss << bar;
	EXPECT_STREQ("3.4 L", ss.str().c_str());
}
