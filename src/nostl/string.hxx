#ifndef STRING_HXX
#define STRING_HXX

#include <iostream>
#include <cstring>

namespace nostl {

class String { // implementing String class because STL containers are prohibited
public:
	String(); // constructor w/o parameters
	String(const char); // constructor from char
	String(const char *); // constructor from c-string

	String(const String&); // copy constructor

	unsigned int len() const; // get length

	String& operator=(const String&); // assignment
	char operator[](const unsigned int) const; // indexing (const)
	char& operator[](const unsigned int); // indexing (var)
	void operator+=(const char); // additive concatenation with char
	void operator+=(const char *); // additiva concatenation with c-string
	void operator+=(const String&); // additive concatenation with other String
	String operator+(const char) const; // concatenation with char
	String operator+(const char *) const; // concatenation with c-string
	String operator+(const String&) const; // concatenation with other String

	friend std::ostream& operator<<(std::ostream&, const String&); // inserter
	friend std::istream& operator>>(std::istream&, String&); // extractor

	~String(); // destructor

private:
	unsigned int length_;
	char * arr_;
};

}

#endif // STRING_HXX
