#include "gtest/gtest.h"
#include "measure/measure.hxx"
#include "nostl/string.hxx"

TEST(MeasureTest, Print)
{
	// create a few allowed Measures
	measure::Measure<int> foo("kg", 120);
	measure::Measure<double> bar("L", 3.4);

	// print Measures
	std::stringstream ss;
	ss << foo;
	EXPECT_STREQ("120 kg", ss.str().c_str());
	ss.str("");
	ss.clear();
	ss << bar;
	EXPECT_STREQ("3.4 L", ss.str().c_str());
}
