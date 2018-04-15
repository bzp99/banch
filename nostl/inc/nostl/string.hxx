#ifndef STRING_HXX
#define STRING_HXX

/// \file list.hxx
///
/// \brief re-implementation of std::String

#include <iostream>
#include <cstring>

namespace nostl {

/// \brief re-implementation of std::String
///
/// I had to re-implement the String class because using STL containers was
/// prohibited.
class String {
public:
	/// \brief constructor w/o parameters --- creates empty String
	String() : length_(0)
	{
		this->arr_ = new char[this->length_ + 1];
		arr_[0] = '\0';
	}

	/// \brief construct from a single character
	///
	/// \param ch character to construct String from
	String(char const ch) : length_(1)
	{
		this->arr_ = new char[this->length_ + 1];
		arr_[0] = ch;
		arr_[1] = '\0';
	}

	/// \brief construct from c-string
	///
	/// \param chs c-string to construct String from
	String(char const * chs) : length_(strlen(chs))
	{
		this->arr_ = new char[this->length_ + 1];
		strcpy(this->arr_, chs);
	}

	/// \brief copy constructor
	///
	/// \param obj String to copy
	///
	/// The default copy constructor needs to be overridden because the class
	/// uses dynamic memory allocation.
	String(String const & obj) : length_(obj.length_)
	{
		this->arr_ = new char[this->length_ + 1];
		strcpy(this->arr_, obj.arr_);
	}


	/// \brief get length of String
	///
	/// \return lenght of String
	unsigned int len() const { return this->length_; }

	/// \brief get classic c-string
	///
	/// \return the c-string equivalent of the String
	char * cstr() const { return this->arr_; }


	/// \brief assignment operator
	///
	/// \param String to set *this* String to be equal to
	///
	/// \return the String itself
	String & operator=(String const &);

	/// \brief assignment operator w/ c-string
	///
	/// \param c-string to set *this* String to have
	///
	/// \return the String itself
	String & operator=(char const *);

	/// \brief constant index operator
	///
	/// \param index of requested char
	///
	/// \return char at index (a value)
	char operator[](unsigned int const) const;

	/// \brief variable index operator
	///
	/// \param index of requested char
	///
	/// \return char at index (variable)
	char & operator[](unsigned int const);

	/// \brief additive concatenation with a single character
	///
	/// \param character to add to the String
	void operator+=(char const);

	/// \brief additive concatenation with c-string
	///
	/// \param c-string to add to the String
	void operator+=(char const *);

	/// \brief additive concatenation with another String
	///
	/// \param String to add to *this* String
	void operator+=(String const &);

	/// \brief concatenation with a single character
	///
	/// \param character to add
	///
	/// \return new String also containing the new character
	String operator+(char const) const;

	/// \brief concatenation with c-string
	///
	/// \param c-string to add
	///
	/// \return new String that has *this* String's contents, plus the c-string
	String operator+(char const *) const;

	/// \brief concatenation with another String
	///
	/// \param String to add
	///
	/// \return new String that has *this* String's contents, plus the contents
	/// of the other String
	String operator+(String const &) const;


	/// \brief inserter operator
	///
	/// \param stream to insert into
	/// \param String to insert
	///
	/// \return the stream object
	inline friend std::ostream & operator<<(std::ostream &, String const &);

	/// \brief extractor operator
	///
	/// \param stream to extract from
	/// \param String to extract into
	///
	/// \return the stream object
	inline friend std::istream & operator>>(std::istream &, String &);

	/// \brief destructor
	///
	/// The default destructor needs to be overridden because the class uses
	/// dynamic memory allocation and that memory has to be freed.
	~String();

private:
	unsigned int length_; ///< lenght of String
	char * arr_; ///< char array (AKA c-string) containing data
}; // class String

String & String::operator=(String const & rhs)
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

String & String::operator=(char const * rhs)
{
	*this = String(rhs);
}

inline char String::operator[](unsigned int const idx) const
{
	if (idx >= this->length_)
	{
		throw std::out_of_range("this string is not that long");
	}

	return this->arr_[idx];
}

inline char & String::operator[](unsigned int const idx)
{
	if (idx >= this->length_)
	{
		throw std::out_of_range("this string is not that long");
	}

	return this->arr_[idx];
}

void String::operator+=(char const ch)
{
	// copy current array contents to temporary array
	char * tmp = new char[this->length_ + 1];
	strcpy(tmp, this->arr_);

	// allocate memory for new array
	++this->length_;
	delete[] this->arr_;
	this->arr_ = new char[this->length_ + 1];
	strcpy(this->arr_, tmp);

	// add new character
	this->arr_[this->length_ - 1] = ch;
	this->arr_[this->length_] = '\0';

	// free temporarily allocated memory
	delete[] tmp;
}

void String::operator+=(char const * chs)
{
	unsigned int chs_len = strlen(chs);
	for (unsigned int i = 0; i < chs_len; ++i)
	{
		*this += chs[i];
	}
}

void String::operator+=(String const & obj)
{
	for (unsigned int i = 0; i < obj.length_; ++i)
	{
		*this += obj.arr_[i];
	}
}

String String::operator+(char const ch) const
{
	String rv(*this);
	rv += ch;
	return rv;
}

String String::operator+(char const * chs) const
{
	String rv(*this);
	rv += chs;
	return rv;
}

String String::operator+(String const & obj) const
{
	String rv(*this);
	rv += obj;
	return rv;
}

inline std::ostream & operator<<(std::ostream & os, String const & obj)
{
	return os << obj.arr_;
}

inline std::istream & operator>>(std::istream & is, String & obj)
{
	return is >> obj.arr_;
}

inline nostl::String::~String()
{
	delete[] this->arr_;
}

} // namespace nostl

#endif // STRING_HXX
