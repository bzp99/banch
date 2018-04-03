// TODO is strcpy unsafe in these cases?

#include "string.hxx"

// constructor w/o parameters
inline nostl::String::String()
{
	this->length = 0;
	this->arr = new char[this->length + 1];

	arr[0] = '\0';
}

// constructor from char
inline nostl::String::String(const char ch)
{
	this->length = 1;
	this->arr = new char[this->length + 1];

	arr[0] = ch;
	arr[1] = '\0';
}

// constructor from c-string
inline nostl::String::String(const char * chs)
{
	this->length = strlength(chs);
	this->arr = new char[this->length + 1];

	strcpy(this->arr, chs);
}

// copy constructor
inline nostl::String::String(const String& obj)
{
	this->length = obj.length;
	this->arr = new char[this->length + 1];

	strcpy(this->arr, obj.arr);
}

// length getter
inline unsigned int nostl::String::len() const
{
	return this->length;
}

// assignment
inline nostl::String& nostl::String::operator=(const String& rhs)
{
	// check for self assignment
	if (this == &rhs)
	{
		return *this;
	}

	delete[] this->arr;
	this->length = rhs.length;
	this->arr = new char[this->length + 1];

	strcpy(this->arr, rhs.arr);

	return *this;
}

// indexing (const)
inline char nostl::String::operator[](const unsigned int idx) const
{
	if (idx >= this->length)
	{
		throw std::out_of_range("this string is not that long"); 
	}

	return this->arr[idx];
}

// indexing (var)
inline char& nostl::String::operator[](const unsigned int idx)
{
	if (idx >= this->length)
	{
		throw std::out_of_range("this string is not that long"); 
	}

	return this->arr[idx];
}

// additive concatenation with char
inline void nostl::String::operator+=(const char ch)
{
	// copy current array contents to temporary array
	char * tmp = new char[this->length + 1];
	strcpy(tmp, this->arr);

	// allocate memory for new array
	++this->length;
	this->arr = new char[this->length + 1];
	strcpy(this->arr, tmp);
	
	// add new character
	this->arr[this->length] = ch;
	this->arr[this->length + 1] = '\0';
	
	// free temporarily allocated memory
	delete[] tmp;
}

// additive concatenation with c-string
void nostl::String::operator+=(const char * chs)
{
	for (unsigned int i = 0; i < strlen(chs); ++i)
	{
		*this += chs[i];
	}
}

// additive concatenation with other String
void nostl::String::operator+=(const nostl::String& obj)
{
	for (unsigned int i = 0; i < obj.length; ++i)
	{
		*this += obj.arr[i];
	}
}

// concatenation with char
inline nostl::String nostl::String::operator+(const char ch) const
{
	String rv(*this);
	rv += ch;
	return rv;
}

// concatenation with c-string
nostl::String nostl::String::operator+(const char * chs) const
{
	String rv(*this);
	rv += chs;
	return rv;
}

// concatenation with other String
nostl::String nostl::String::operator+(const String& obj) const
{
	String rv(*this);
	rv += obj;
	return rv;
}

// inserter
inline std::ostream& operator<<(std::ostream& os, const nostl::String& obj)
{
	return os << obj.arr;
}

// extractor
inline std::istream& operator>>(std::istream& is, nostl::String& obj)
{
	return is >> obj.arr;
}

// destructor
inline nostl::String::~String()
{
	delete[] this->arr;
}
