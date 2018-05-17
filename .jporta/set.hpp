#ifndef BANCH_NOSTL_SET_HXX
#define BANCH_NOSTL_SET_HXX

/// \file set.hpp
///
/// \brief re-implementation of std::Set<T>

#include "list.hpp"

/// \brief namespace for STL reimplementations
namespace nostl {

/// \brief re-implementation of std::Set<T>
///
/// @tparam T type of elements that the Set contains
///
/// I had to re-implement the Set class because using STL containers was
/// prohibited. This set uses the previously made custom List class. The
/// only addition is that it checks for multiple addition (a Set may only
/// contain each element only once).
template <typename T>
class Set {
public:
	/// \brief add element to the Set
	///
	/// \param value of new element
	inline void insert(T const &);

	/// \brief remove an element from the Set
	///
	/// \param value of element to remove
	inline void remove(T const & val) { this->list_.remove(val); }

	/// \brief clear the Set (i.e. remove all of its elements)
	inline void clear() { this->list_.clear(); }


	/// \brief equality operator
	///
	/// \param Set to check equality with
	///
	/// \return true if the two Sets are equal
	inline bool operator==(Set<T> const &) const;

	/// \brief ineqality operator
	///
	/// \param Set to check ineqality with
	///
	/// \return true if the two Sets differ somehow
	inline bool operator!=(Set<T> const &) const;


	/// \brief get the size of the Set (i.e. the number of its elements)
	///
	/// \return the Set's size
	inline unsigned int size() const { return this->list_.size(); }

public:
	/// \brief use the List class's Iterator
	using Iterator = typename nostl::List<T>::Iterator;

	/// \brief get Iterator to the first element of the Set
	///
	/// \return Iterator to first element
	inline Iterator begin() const;

	/// \brief get Iterator to the last element of the Set
	///
	/// \return Iterator to last element
	inline Iterator end() const;


private:
	List<T> list_; ///< Set is implemented using a doubly-linked List
}; // class Set



////////////////////////
// INLINE DEFINITIONS //
////////////////////////

template <typename T>
void Set<T>::insert(T const & val)
{
	// make sure list/set doesn't contain item yet
	if (this->size() != 0)
	{
		for (typename List<T>::Iterator i = this->list_.begin();
				i != this->list_.end(); ++i)
		{
			if (*i == val)
			{
				return;
			}
		}
	}

	this->list_.append(val);
}

template <typename T>
bool Set<T>::operator==(Set<T> const & rhs) const
{
	return (this->list_ == rhs.list_);
}

template <typename T>
bool Set<T>::operator!=(Set<T> const & rhs) const
{
	return !(*this == rhs);
}

template <typename T>
typename Set<T>::Iterator Set<T>::begin() const
{
	typename List<T>::Iterator i = this->list_.begin();
	return i;
}

template <typename T>
typename Set<T>::Iterator Set<T>::end() const
{
	typename List<T>::Iterator i = this->list_.end();
	return i;
}

} // namespace nostl

#endif // BANCH_NOSTL_SET_HXX
