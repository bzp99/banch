#ifndef STRING_HXX
#define STRING_HXX

#include <iostream>
#include <cstring>

namespace nostl {

class String { // implementing String class because STL containers are prohibited
public:
	/// CONSTRUCTORS ///
	String() : length_(0) // constructor w/o parameters
	{
		this->arr_ = new char[this->length_ + 1];
		arr_[0] = '\0';
	}

	String(const char ch) : length_(1) // constructor from char
	{
		this->arr_ = new char[this->length_ + 1];
		arr_[0] = ch;
		arr_[1] = '\0';
	}

	String(const char * chs) : length_(strlen(chs)) // constructor from c-string
	{
		this->arr_ = new char[this->length_ + 1];
		strcpy(this->arr_, chs);
	}

	String(const String& obj) : length_(obj.length_) // copy constructor
	{
		this->arr_ = new char[this->length_ + 1];
		strcpy(this->arr_, obj.arr_);
	}

	/// MEMBER FUNCTIONS ///
	unsigned int len() const // get length
	{
		return this->length_;
	}

	/// OPERATORS ///
	String& operator=(const String&); // assignment
	char operator[](const unsigned int) const; // indexing (const)
	char& operator[](const unsigned int); // indexing (var)
	void operator+=(const char); // additive concatenation with char
	void operator+=(const char *); // additiva concatenation with c-string
	void operator+=(const String&); // additive concatenation with other String
	String operator+(const char) const; // concatenation with char
	String operator+(const char *) const; // concatenation with c-string
	String operator+(const String&) const; // concatenation with other String

	inline friend std::ostream& operator<<(std::ostream&, const String&); // inserter
	inline friend std::istream& operator>>(std::istream&, String&); // extractor

	~String(); // destructor

private:
	unsigned int length_;
	char * arr_;
}; // class String

inline String& String::operator=(const String& rhs)
{
	// check for self assignment
	if (this == &rhs)
	{
		return *this;
	}

	delete[] this->arr_;
	this->length_ = rhs.length_;
	this->arr_ = new char[this->length_ + 1];

	strcpy(this->arr_, rhs.arr_);

	return *this;
}

inline char String::operator[](const unsigned int idx) const
{
	if (idx >= this->length_)
	{
		throw std::out_of_range("this string is not that long"); 
	}

	return this->arr_[idx];
}

inline char& String::operator[](const unsigned int idx)
{
	if (idx >= this->length_)
	{
		throw std::out_of_range("this string is not that long"); 
	}

	return this->arr_[idx];
}

inline void String::operator+=(const char ch)
{
	// copy current array contents to temporary array
	char * tmp = new char[this->length_ + 1];
	strcpy(tmp, this->arr_);

	// allocate memory for new array
	++this->length_;
	this->arr_ = new char[this->length_ + 1];
	strcpy(this->arr_, tmp);
	
	// add new character
	this->arr_[this->length_] = ch;
	this->arr_[this->length_ + 1] = '\0';
	
	// free temporarily allocated memory
	delete[] tmp;
}

void String::operator+=(const char * chs)
{
	for (unsigned int i = 0; i < strlen(chs); ++i)
	{
		*this += chs[i];
	}
}

void String::operator+=(const nostl::String& obj)
{
	for (unsigned int i = 0; i < obj.length_; ++i)
	{
		*this += obj.arr_[i];
	}
}

String String::operator+(const char ch) const
{
	String rv(*this);
	rv += ch;
	return rv;
}

String String::operator+(const char * chs) const
{
	String rv(*this);
	rv += chs;
	return rv;
}

String String::operator+(const String& obj) const
{
	String rv(*this);
	rv += obj;
	return rv;
}

inline std::ostream& operator<<(std::ostream& os, const nostl::String& obj)
{
	return os << obj.arr_;
}

inline std::istream& operator>>(std::istream& is, nostl::String& obj)
{
	return is >> obj.arr_;
}

inline nostl::String::~String()
{
	delete[] this->arr_;
}

} // namespace nostl

#endif // STRING_HXX
