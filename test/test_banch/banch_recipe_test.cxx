#include "gtest/gtest.h"
#include "banch/banch.hxx"

using namespace banch;

TEST(RecipeTest, Build)
{
	// create recipe and fill with stuff
	Recipe dryMartini("Dry Martini");
	dryMartini.add(new Beverage("gin", 5));
	dryMartini.add(new Beverage("dry vermouth", 1));
	dryMartini.add(new Extra("a few olives"));

	EXPECT_EQ(3, dryMartini.number_of_ingredients());

	// test printing recipe
	std::stringstream ss;
	dryMartini.show(ss);
	EXPECT_STREQ("Recipe: Dry Martini\n" \
					"5 units of gin\n" \
					"1 units of dry vermouth\n" \
					"a few olives\n", // these are auto-conctenated by compiler
					ss.str().c_str());
}

TEST(RecipeTest, Remove)
{
	// create recipe and fill with stuff + a few superfluous things
	Recipe ramosGinFizz("Ramos gin fizz");
	ramosGinFizz.add(new Beverage("gin", 4));
	ramosGinFizz.add(new Beverage("cream", 2));
	Beverage * nuka = new Beverage("nuka cola", 20);
	ramosGinFizz.add(nuka);
	ramosGinFizz.add(new Extra("an egg white"));
	ramosGinFizz.add(new Beverage("lemon juice", 1));
	ramosGinFizz.add(new Beverage("lime juice", 1));
	Extra * dirt = new Extra("a bit of dirt");
	ramosGinFizz.add(dirt);
	ramosGinFizz.add(new Extra("sugar"));

	EXPECT_EQ(8, ramosGinFizz.number_of_ingredients());

	// test if removal actually works
	std::stringstream ss;
	ramosGinFizz.remove(nuka);
	ramosGinFizz.show(ss);
	EXPECT_STREQ("Recipe: Ramos gin fizz\n" \
					"4 units of gin\n" \
					"2 units of cream\n" \
					"an egg white\n" \
					"1 units of lemon juice\n" \
					"1 units of lime juice\n" \
					"a bit of dirt\n" \
					"sugar\n",
					ss.str().c_str());

	ss.str("");
	ss.clear();
	ramosGinFizz.remove(dirt);
	ramosGinFizz.show(ss);
	EXPECT_STREQ("Recipe: Ramos gin fizz\n" \
					"4 units of gin\n" \
					"2 units of cream\n" \
					"an egg white\n" \
					"1 units of lemon juice\n" \
					"1 units of lime juice\n" \
					"sugar\n",
					ss.str().c_str());
}

TEST(RecipeTest, Serialize)
{
	// create recipe and fill with stuff
	Recipe piscoSour("Pisco sour");
	piscoSour.add(new Beverage("pisco", 3));
	piscoSour.add(new Beverage("fresh squeezed lime juice", 1));
	piscoSour.add(new Beverage("simple syrup", 1));
	piscoSour.add(new Extra("a fresh egg white"));
	piscoSour.add(new Extra("a dash of angoustra"));

	// serialize into a stringstream
	std::stringstream ss;
	piscoSour.serialize(ss);
	EXPECT_STREQ("startrecipe\n" \
					"Pisco sour\n" \
					"beverage\npisco\n3\n" \
					"beverage\nfresh squeezed lime juice\n1\n" \
					"beverage\nsimple syrup\n1\n" \
					"extra\na fresh egg white\n" \
					"extra\na dash of angoustra\n" \
					"endrecipe\n",
					ss.str().c_str());

	ss.str("");
	ss.clear();

	// deserialize from a stringstream
	ss.str("Sidecar\n" \
			"beverage\ncognac\n2\n" \
			"beverage\ncointreau\n1\n" \
			"beverage\nfresh lemon juice\n1\n" \
			"extra\nsuperfine sugar\n" \
			"endrecipe");
	Recipe sidecar;
	sidecar.deserialize(ss);

	std::stringstream ss2;
	sidecar.show(ss2);
	EXPECT_STREQ("Recipe: Sidecar\n" \
					"2 units of cognac\n" \
					"1 units of cointreau\n" \
					"1 units of fresh lemon juice\n" \
					"superfine sugar\n",
					ss2.str().c_str());
}
