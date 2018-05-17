#include "gtest_lite.h"
#include "list.hpp"
#include "set.hpp"
#include "banch.hpp"

#include "memtrace.h"

#include <sstream>

using namespace nostl;
using namespace banch;
using std::string;

// catch tests have been carelessly converted to gtests

int main()
{
	/*
	///////////////////////////
	// TESTS FOR nostl::List //
	///////////////////////////

	TEST("Empty list can be created", "[list][sanity]")
		// create empty List and check if its size is 0
		List<int> foo;
		EXPECT_EQ( 0, foo.size() );
	END

	TEST("A list can be filled", "[list]")
		// create List with doubles like {0, .5, 1, 1.5, ..., 50}
		List<double> foo;
		for (unsigned int i = 0; i < 100; ++i)
		{
			foo.append(static_cast<double>(i) / 2.0);
		}

		EXPECT_EQ( 100, foo.size() );
	END

	TEST("A list can be cleared", "[list]")
		// create List with longs and test clearing
		List<long> foo;
		for (unsigned int i = 0; i < 20; ++i)
		{
			foo.append(static_cast<long>(i) / 3.141592654);
		}

		EXPECT_EQ( 20, foo.size() );

		foo.clear();

		EXPECT_EQ( 0, foo.size() );
	END

	TEST("A list can be correctly copied", "[list]")
		// create List with a few ints like {0, 1, ..., 99}
		List<int> foo;
		for (unsigned int i = 0; i < 100; ++i)
		{
			foo.append(i);
		}

		// create another List by copying the first one
		List<int> bar = foo;

		// change a few elements in the copy and make sure original instance is left
		// unchanged
		bar.remove(13);
		bar.remove(0);

		EXPECT_NE( foo.size() , bar.size() );

		bar.clear();

		EXPECT_EQ( 0, bar.size() );
		EXPECT_EQ( 100, foo.size() );
	END

	TEST("A list can be assigned another list", "[list]")
		// create List with a few ints like {0, 1, ..., 99}
		List<int> foo;
		for (unsigned int i = 0; i < 100; ++i)
		{
			foo.append(i);
		}

		// create another List with a few other ints like {100, 101, ..., 999}
		List<int> bar;
		for (unsigned int i = 100; i < 1000; ++i)
		{
			bar.append(i);
		}

		// make sure the two Lists differ (obviously...)
		EXPECT_NE( foo.size() , bar.size() );

		// set foo to be the same as bar
		foo = bar;

		// see if assignment was correct and the two Lists are still different
		// instances
		EXPECT_EQ( foo.size() , bar.size() );

		bar.append(1000);

		EXPECT_NE( foo.size() , bar.size() );
	END

	TEST("A list can be iterated", "[list][iterators]")
		// create new List and fill with ints like {200, 5, 1}
		List<int> foo;
		foo.append(5);
		foo.append(1);
		foo.prepend(200);

			List<int>::Iterator i = foo.begin();
			EXPECT_EQ( 200, *i  );

			++i;
			EXPECT_EQ( 5, *i );

			++i;
			EXPECT_EQ( 1, *i  );

			--i;
			EXPECT_EQ( 5, *i );

			i = foo.end();
			--i;
			EXPECT_EQ( 1, *i );

			--i;
			EXPECT_EQ( 5, *i  );

			i = foo.begin();
			EXPECT_EQ( 200, *(i++)  );
			EXPECT_EQ( 5, *i );

			i = foo.end();
			--i;
			EXPECT_EQ( 1, *(i--) );
			EXPECT_EQ( 5, *i  );
	END

	TEST("List iterators don't go out of range", "[list][iterators]")
		// create new List and fill with doubles like {10.5, 15.5, 20.5}
		List<double> foo;
		foo.prepend(20.5);
		foo.prepend(15.5);
		foo.prepend(10.5);

			List<double>::Iterator i = foo.begin();
			--i;
			EXPECT_EQ( 10.5, *(i--)  );
			EXPECT_EQ( 10.5 , *i );

			i = foo.end();
			//List<double>::Iterator j = i;
			++i;
	//EXPECT_EQ( i , j );
	END

	TEST("Elements can be removed from a list", "[list]")
		// create new List with a few elements like {3, 30, 3, 30}
		List<int> foo;
		foo.append(3);
		foo.append(30);
		foo.append(3);
		foo.append(30);

		// remove an element
		foo.remove(30); // --> {3, 3, 30}
		EXPECT_EQ( 3, foo.size()  );

		List<int>::Iterator i = foo.begin();
		EXPECT_EQ( 3, *(i++) );
		EXPECT_EQ( 3, *(i++) );
		EXPECT_EQ( 30, *i  );

		// remove two more just for fun
		foo.remove(30); // --> {3, 3}
		EXPECT_EQ( 2, foo.size()  );

		foo.remove(3); // --> {3}
		EXPECT_EQ( 1, foo.size()  );

		i = foo.begin();
		EXPECT_EQ( 3, *i );
	END

	//////////////////////////
	// TESTS FOR nostl::Set //
	//////////////////////////

	TEST("Empty set can be created", "[set][sanity]")
		// create empty set and check if its size is 0
		Set<int> foo;
		EXPECT_EQ( 0, foo.size()  );
	END

	TEST("A set can be filled", "[set]")
		// create new set with different doubles, namely {0, .5, 1, ..., 50}
		Set<double> foo;
		for (unsigned int i = 0; i < 100; ++i)
		{
			foo.insert(static_cast<double>(i) / 2.0);
		}

			EXPECT_EQ( 100 , foo.size()  );

			foo.insert(1.0);
			foo.insert(0);

			EXPECT_EQ( 100, foo.size()  );
	END

	TEST("A set can be cleared", "[set]")
		// fill new set with doubles and test clearing
		Set<double> foo;
		for (unsigned int i = 0; i < 420; ++i)
		{
			foo.insert(static_cast<double>(i) / -2.718281828459);
		}

		EXPECT_EQ( 420 , foo.size()  );

		foo.clear();
		EXPECT_EQ( 0, foo.size() );
	END

	TEST("A set can be correctly copied", "[set]")
		// create Set with a few ints like {0, 1, ... 99}
		Set<int> foo;
		for (unsigned int i = 0; i < 100; ++i)
		{
			foo.insert(i);
		}

		// create another Set by copying the first one
		Set<int> bar = foo;

		// change a few elements in the copy and make sure original instance is left
		// unchaged
		bar.insert(30);
		bar.remove(13);
		bar.remove(0);
		EXPECT_NE( foo.size() , bar.size() );

		bar.clear();
		EXPECT_EQ( 0, bar.size()  );
		EXPECT_EQ( 100, foo.size() );
	END

	TEST("A set can be correctly assigned to another one", "[set]")
		// create Set with a few ints like {0, 1, ..., 99}
		Set<int> foo;
		for (unsigned int i = 0; i < 100; ++i)
		{
			foo.insert(i);
		}

		// create another Set with a few other ints like {100, 101, ..., 999}
		Set<int> bar;
		for (unsigned int i = 100; i < 1000; ++i)
		{
			bar.insert(i);
		}

		// set foo to be the same as bar
		foo = bar;

		// see if assignment was correct and the two Lists are still different
		// instances
		EXPECT_EQ( foo.size() , bar.size() );

		bar.insert(1000);
		EXPECT_NE( foo.size() , bar.size() );
	END

	TEST("A set can be iterated", "[set][iteration]")
		// create new Set and fill with ints like {200, 5, 1}
		Set<int> foo;
		foo.insert(200);
		foo.insert(5);
		foo.insert(1);

			Set<int>::Iterator i = foo.begin();
			EXPECT_EQ( 200, *i  );

			++i;
			EXPECT_EQ( 5, *i  );

			++i;
			EXPECT_EQ( 1, *i  );

			--i;
			EXPECT_EQ( 5, *i  );

			i = foo.end();
			--i;
			EXPECT_EQ( 1, *i );

			--i;
			EXPECT_EQ(5,  *i  );

			i = foo.begin();
			--i;
			EXPECT_EQ( 200, *(i++)  );
			EXPECT_EQ( 5, *i );

			i = foo.end();
			--i;
			EXPECT_EQ( 1, *(i--) );
			EXPECT_EQ( 5, *i );
	END

	TEST("Set iterators don't go out of range", "[set][iterators]")
		// create new Set and fill with doubles like {10.5, 15.5, 20.5}
		Set<double> foo;
		foo.insert(10.5);
		foo.insert(15.5);
		foo.insert(20.5);

			Set<double>::Iterator i = foo.begin();
			--i;
			EXPECT_EQ( 10.5 ,*(i--) );
			EXPECT_EQ( 10.5 ,*i  );

			i = foo.end();
			//Set<double>::Iterator j = i;
			++i;
	//		EXPECT_EQ( i , j );
	END

	TEST("Elements can be removed from a set", "[set]")
		// create new Set with a few elements like {3, 4, 5, 40}
		Set<int> foo;
		foo.insert(3);
		foo.insert(4);
		foo.insert(5);
		foo.insert(40);

		// remove an element
		foo.remove(4); // --> {3, 5, 40}
		EXPECT_EQ( 3, foo.size()  );

		Set<int>::Iterator i = foo.begin();
		EXPECT_EQ( 3, *(i++)  );
		EXPECT_EQ( 5, *(i++)  );
		EXPECT_EQ( 40, *i  );

		// remove two more just for fun
		foo.remove(40); // --> {3, 5}
		EXPECT_EQ( 2, foo.size()  );

		foo.remove(3); // --> {5}
		EXPECT_EQ( 1, foo.size()  );

		i = foo.begin();
		EXPECT_EQ( 5, *i );

		// remove a nonexistent one
		foo.remove(3030); // --> {3, 5}
		EXPECT_EQ( 1, foo.size()  );

		// remove the last one
		foo.remove(5); // --> {}
		EXPECT_EQ( 0, foo.size() );
	END

	/////////////////////////////
	// TESTS FOR banch::Recipe //
	/////////////////////////////

	TEST("A recipe can be made", "[recipe]")
		// create recipe and fill with stuff
		Recipe dryMartini("Dry Martini");
		dryMartini.add(new Beverage("gin", 5));
		dryMartini.add(new Beverage("dry vermouth", 1));
		dryMartini.add(new Extra("a few olives"));

		EXPECT_EQ( 3, dryMartini.number_of_ingredients()  );

		// test printing recipe
		std::stringstream ss;
		dryMartini.show(ss);
	END

	TEST("Ingredients can be removed froma a recipe", "[recipe]")
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

		EXPECT_EQ( 8, ramosGinFizz.number_of_ingredients()  );

		// test if removal actually works
		EXPECT_EQ( 7, ramosGinFizz.number_of_ingredients()  );
		ramosGinFizz.remove(dirt);
		EXPECT_EQ( 6, ramosGinFizz.number_of_ingredients() );
	END

	TEST("A recipe can be persistent", "[recipe][serialization]")
		// create recipe and fill with stuff
		Recipe piscoSour("Pisco sour");
		piscoSour.add(new Beverage("pisco", 3));
		piscoSour.add(new Beverage("fresh squeezed lime juice", 1));
		piscoSour.add(new Beverage("simple syrup", 1));
		piscoSour.add(new Extra("a fresh egg white"));
		piscoSour.add(new Extra("a dash of angoustra"));

		std::stringstream ss;
		piscoSour.serialize(ss);

		Recipe sidecar;

		sidecar.deserialize(ss);
	END

	/////////////////////////////////
	// TESTS FOR banch::RecipeBook //
	/////////////////////////////////

	TEST("A recipe book can be created", "[recipebook]")
		// create some placeholder recipes and put them into the book
		Recipe * foo = new Recipe("foo");
		foo->add(new Beverage("mineral water", 10));
		foo->add(new Extra("lemon slices"));

		Recipe * bar = new Recipe("bar");
		bar->add(new Beverage("milk", 8));

		RecipeBook qux;
		qux.add(foo);
		qux.add(bar);

		EXPECT_EQ( 2, qux.number_of_entries()  );
	END

	TEST("Recipes can be removed from a recipe book", "[recipebook]")
		// create some placeholder recipes with stuff and add in a book
		Recipe * foo = new Recipe("foo");
		Recipe * oldCrippledMan = new Recipe("I'm so dead");
		Recipe * bar =  new Recipe("bar");

		RecipeBook qux;
		qux.add(foo);
		qux.add(oldCrippledMan);
		qux.add(bar);

		EXPECT_EQ(3,  qux.number_of_entries()  );

		qux.remove(oldCrippledMan); // haha, you're dead ^^

		EXPECT_EQ( 2, qux.number_of_entries()  );
	END

	TEST("A recipe book can be persistent", "[recipebook][serialization]")
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

		RecipeBook myDrinksCopy;
		myDrinksCopy.deserialize(ss);

			EXPECT_EQ( 2, myDrinksCopy.number_of_entries()  );
	END
	*/
}
