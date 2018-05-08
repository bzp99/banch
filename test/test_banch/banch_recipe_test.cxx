#include "gtest/gtest.h"
#include "banch/banch.hxx"

using namespace banch;

TEST(RecipeTest, CreateRecipe)
{
	// create recipe and fill with stuff
	Recipe dryMartini("Dry Martini");
	dryMartini.add(new Beverage("gin", 5));
	dryMartini.add(new Beverage("dry vermouth", 1));
	dryMartini.add(new Extra("a few olives"));

	// test printing recipe
	std::stringstream ss;
	dryMartini.show(ss);
	EXPECT_STREQ("Recipe: Dry Martini\n" \
					"5 units of gin\n" \
					"1 units of dry vermouth\n" \
					"a few olives\n", // these are auto-conctenated by compiler
					ss.str().c_str());
}
