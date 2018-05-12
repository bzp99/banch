#include "catch/catch.hpp"
#include "banch/banch.hxx"

#include <sstream> // test uses stringstreams

using namespace Catch;
using namespace banch;

TEST_CASE("A recipe book can be created", "[recipebook]")
{
	// create some placeholder recipes and put them into the book
	Recipe * foo = new Recipe("foo");
	Recipe * bar = new Recipe("bar");

	RecipeBook qux;
	qux.add(foo);
	qux.add(bar);

	CHECK( qux.number_of_entries() == 2 );

	// add a few ingredients and test listing
	foo->add(new Beverage("mineral water", 10));
	foo->add(new Extra("lemon slices"));
	bar->add(new Beverage("milk", 8));

	std::stringstream ss;
	qux.list(ss);
	CHECK_THAT( ss.str().c_str(),
			Equals( "Recipe: foo\n" \
						"10 units of mineral water\n" \
						"lemon slices\n" \
						"\n" \
						"Recipe: bar\n" \
						"8 units of milk\n" \
						"\n"
			)
	);
}

TEST_CASE("Recipes can be removed from a recipe book", "[recipebook]")
{
	// create some placeholder recipes with stuff and add in a book
	Recipe * foo = new Recipe("foo");
	Recipe * oldCrippledMan = new Recipe("I'm so dead");
	Recipe * bar = new Recipe("bar");

	RecipeBook qux;
	qux.add(foo);
	qux.add(oldCrippledMan);
	qux.add(bar);

	CHECK( qux.number_of_entries() == 3 );

	qux.remove(oldCrippledMan); // haha, you're dead ^^

	CHECK( qux.number_of_entries() == 2 );

	std::stringstream ss;
	qux.list(ss);
	CHECK_THAT( ss.str().c_str(),
			Equals( "Recipe: foo\n" \
						"\n" \
						"Recipe: bar\n" \
						"\n"
			)
	);
}

TEST_CASE("A recipe book can be persistent", "[recipebook][serialization]")
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

	std::stringstream ss;
	myDrinks.serialize(ss);

	SECTION("A recipe book can be serialized")
	{
		CHECK_THAT( ss.str().c_str(),
				Equals( "startrecipe\n" \
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
							"endrecipe\n"
				)
		);
	}

	RecipeBook myDrinksCopy;
	myDrinksCopy.deserialize(ss);

	SECTION("A recipe book can be deserialized")
	{
		CHECK( myDrinksCopy.number_of_entries() == 2 );
	}
}
