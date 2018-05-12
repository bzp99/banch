#include "catch/catch.hpp"
#include "menu/menu.hxx"

#include <sstream> // test uses stringstreams

using namespace Catch;
using namespace menu;

// function object to test with
class say_hello {
public:
	say_hello(std::ostream & os) : os_(os) {}

	void operator()() const { os_ << "hello" << std::endl; }


private:
	std::ostream & os_;
};

TEST_CASE("An empty menu can be created", "[menu][sanity]")
{
	/*
	// create stringstreams for testing
	std::stringstream menustream;
	std::stringstream fnctstream;

	// create a menu and add our function object
	Menu foo(menustream, menustream);
	foo.add(Option("greet me", std::function<void()>(say_hello(fnctstream))));

	// display menu
	foo();
	CHECK_THAT( menustream.str().c_str(),
				Equals(	"\n" \
							"0) exit menu\n" \
							"1) greet me\n" \
							"\n" \
							">> "
			)
	);

	// select an option
	menustream << "1" << std::endl;
	CHECK_THAT( fnctstream.str().c_str(),
				Equals( "hello" )
	);
	*/
}
