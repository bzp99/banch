#include "gtest/gtest.h"
#include "banch/banch.hxx"

using namespace banch;

TEST(RecipeBookTest, Basic)
{
	// create some placeholder recipes and put them into the book
	Recipe * foo = new Recipe("foo");
	Recipe * bar = new Recipe("bar");

	RecipeBook qux;
	qux.add(foo);
	qux.add(bar);

	EXPECT_EQ(2, qux.number_of_entries());

	// add a few ingredients and test listing
	foo->add(new Beverage("mineral water", 10));
	foo->add(new Extra("lemon slices"));
	bar->add(new Beverage("milk", 8));

	std::stringstream ss;
	qux.list(ss);
	EXPECT_STREQ("Recipe: foo\n" \
					"10 units of mineral water\n" \
					"lemon slices\n" \
					"\n" \
					"Recipe: bar\n" \
					"8 units of milk\n" \
					"\n",
					ss.str().c_str());
}

TEST(RecipeBookTest, Remove)
{
	// create some placeholder recipes with stuff and add in a book
	Recipe * foo = new Recipe("foo");
	Recipe * oldCrippledMan = new Recipe("I'm so dead");
	Recipe * bar = new Recipe("bar");

	RecipeBook qux;
	qux.add(foo);
	qux.add(oldCrippledMan);
	qux.add(bar);

	EXPECT_EQ(3, qux.number_of_entries());

	qux.remove(oldCrippledMan); // haha, you're dead ^^

	EXPECT_EQ(2, qux.number_of_entries());

	std::stringstream ss;
	qux.list(ss);
	EXPECT_STREQ("Recipe: foo\n" \
					"\n" \
					"Recipe: bar\n" \
					"\n",
					ss.str().c_str());
}

TEST(RecipeBookTest, Serialize)
{
	// create a realistic book
	Recipe * lastWord = new Recipe("Last word");
	lastWord->add(new Beverage("gin", 1));
	lastWord->add(new Beverage("fresh squeezed lime juice", 1));
	lastWord->add(new Beverage("maraschino liqueur", 1));
	lastWord->add(new Beverage("green Chartreuse", 1));

	Recipe * brooklyn = new Recipe("Brooklyn");
	brooklyn->add(new Beverage("rye whiskey", 8));
	brooklyn->add(new Beverage("dry vermouth", 4));
	brooklyn->add(new Beverage("maraschino liqueur", 1));
	brooklyn->add(new Extra("a few dashes of angoustra"));

	RecipeBook myDrinks;
	myDrinks.add(lastWord);
	myDrinks.add(brooklyn);

	// serialize into stringstream
	std::stringstream ss;
	myDrinks.serialize(ss);
	EXPECT_STREQ("startrecipe\n" \
					"Last word\n" \
					"beverage\ngin\n1\n" \
					"beverage\nfresh squeezed lime juice\n1\n" \
					"beverage\nmaraschino liqueur\n1\n" \
					"beverage\ngreen Chartreuse\n1\n" \
					"endrecipe\n" \
					"startrecipe\n" \
					"Brooklyn\n" \
					"beverage\nrye whiskey\n8\n" \
					"beverage\ndry vermouth\n4\n" \
					"beverage\nmaraschino liqueur\n1\n" \
					"extra\na few dashes of angoustra\n" \
					"endrecipe\n",
					ss.str().c_str());

	// check deserialization
	RecipeBook myDrinksCopy;
	myDrinksCopy.deserialize(ss);
	EXPECT_EQ(2, myDrinksCopy.number_of_entries());
}
