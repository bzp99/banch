#ifndef BANCH_NOSTL_SET_HXX
#define BANCH_NOSTL_SET_HXX

/// \file set.hxx
///
/// \brief re-implementation of std::Set<T>

#include "nostl/list.hxx"

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
	void insert(T const &);

	/// \brief remove an element from the Set
	///
	/// \param value of element to remove
	void remove(T const &);

	/// \brief clear the Set (i.e. remove all of its elements)
	void clear();


	/// \brief get the size of the Set (i.e. the number of its elements)
	///
	/// \return the Set's size
	unsigned int size() const { return this->list_.size(); }

public:
	/// \brief use the List class's Iterator
	using Iterator = typename nostl::List<T>::Iterator;

	/// \brief get Iterator to the first element of the Set
	///
	/// \return Iterator to first element
	Iterator begin() const
	{
		typename List<T>::Iterator i = this->list_.begin();
		return i;
	}

	/// \brief get Iterator to the last element of the Set
	///
	/// \return Iterator to last element
	Iterator end() const
	{
		typename List<T>::Iterator i = this->list_.end();
		return i;
	}


private:
	List<T> list_; ///< Set is implemented using a doubly-linked List
}; // class Set

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
void Set<T>::remove(T const & val)
{
	this->list_.remove(val);
}

template <typename T>
void Set<T>::clear()
{
	this->list_.clear();
}

} // namespace nostl

#endif // BANCH_NOSTL_SET_HXX
