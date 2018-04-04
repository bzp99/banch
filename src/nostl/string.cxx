// TODO is strcpy unsafe in these cases?

#include "string.hxx"

// constructor w/o parameters
inline nostl::String::String()
{
	this->length_ = 0;
	this->arr_ = new char[this->length_ + 1];

	arr_[0] = '\0';
}

// constructor from char
inline nostl::String::String(const char ch)
{
	this->length_ = 1;
	this->arr_ = new char[this->length_ + 1];

	arr_[0] = ch;
	arr_[1] = '\0';
}

// constructor from c-string
inline nostl::String::String(const char * chs)
{
	this->length_ = strlen(chs);
	this->arr_ = new char[this->length_ + 1];

	strcpy(this->arr_, chs);
}

// copy constructor
inline nostl::String::String(const String& obj)
{
	this->length_ = obj.length_;
	this->arr_ = new char[this->length_ + 1];

	strcpy(this->arr_, obj.arr_);
}

// length getter
inline unsigned int nostl::String::len() const
{
	return this->length_;
}

// assignment
inline nostl::String& nostl::String::operator=(const String& rhs)
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

// indexing (const)
inline char nostl::String::operator[](const unsigned int idx) const
{
	if (idx >= this->length_)
	{
		throw std::out_of_range("this string is not that long"); 
	}

	return this->arr_[idx];
}

// indexing (var)
inline char& nostl::String::operator[](const unsigned int idx)
{
	if (idx >= this->length_)
	{
		throw std::out_of_range("this string is not that long"); 
	}

	return this->arr_[idx];
}

// additive concatenation with char
inline void nostl::String::operator+=(const char ch)
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
	for (unsigned int i = 0; i < obj.length_; ++i)
	{
		*this += obj.arr_[i];
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
	return os << obj.arr_;
}

// extractor
inline std::istream& operator>>(std::istream& is, nostl::String& obj)
{
	return is >> obj.arr_;
}

// destructor
inline nostl::String::~String()
{
	delete[] this->arr_;
}
