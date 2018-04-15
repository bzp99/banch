#ifndef BANCH_NOSTL_SET_HXX
#define BANCH_NOSTL_SET_HXX

/// \file list.hxx
///
/// \brief re-implementation of std::Set<T>

#include "nostl/list.hxx"

namespace nostl {

/// \brief re-implementation of std::Set<T>
///
/// @tparam T type of elements that the Set contains
///
/// I had to re-implement the Set class because using STL containers was
/// prohibited. This set uses the previously made custom List class. The
/// only addition is that it checks for multiple addition (the Set can only
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
	/// \brief custom made iterator to navigate the Set more easily
	class Iterator {
	public:
		/// \brief constructor for the Set's Iterator (uses Lists class')
		///
		/// \param list_iterator List Iterator to use
		Iterator(typename List<T>::Iterator list_iterator)
		{
			this->list_iterator_ = list_iterator;
		}


		/// \brief dereference operator
		///
		/// \return the value of the List Node currently pointed to
		T & operator*() { return *(this->list_iterator_); }

		/// \brief const dereference operator
		///
		/// \return the value of the List Node currently pointed to
		T const & operator*() const { return *(this->list_iterator_); }

		/// \brief member access operator
		///
		/// \return pointer to itself
		Iterator * operator->() const { return this; }


		/// \brief preincrement operator
		///
		/// \return Iterator of next List Node
		Iterator operator++()
		{
			++this->list_iterator_;
			return *this;
		}

		/// \brief postincrement operator
		///
		/// \param int dummy parameter
		///
		/// \return Iterator of current List Node
		Iterator operator++(int)
		{
			Iterator rv = *this;
			++this->list_iterator_;
			return rv;
		}

		/// \brief predecrement operator
		///
		/// \return Iterator of previous List Node
		Iterator operator--()
		{
			--this->list_iterator_;
			return *this;
		}

		/// \brief postdecrement operator
		///
		/// \param int dummy parameter
		///
		/// \return Iterator of current List Node
		Iterator operator--(int)
		{
			Iterator rv = *this;
			--this->list_iterator_;
			return rv;
		}


		/// \brief equality operator
		///
		/// \param rhs Iterator to check equality with
		///
		/// \return true if the Iterators point to the same List Node
		bool operator==(Iterator const & rhs) const
		{
			return this->list_iterator_ == rhs.list_iterator_;
		}

		/// \brief inequality operator
		///
		/// \param rhs Iterator to check inequality with
		///
		/// \return true if the Iterators point to different List Nodes
		bool operator!=(Iterator const & rhs) const { return !(*this == rhs); }


	private:
		typename List<T>::Iterator list_iterator_; ///< using already
													///< implemented List
													/// Itearator
	}; // class Iterator

public:
	/// \brief get Iterator to the first element of the Set
	///
	/// \return Iterator to first element
	Iterator begin()
	{
		typename List<T>::Iterator i = this->list_.begin();
		return Iterator(i);
	}

	/// \brief get Iterator to the last element of the Set
	///
	/// \return Iterator to last element
	Iterator end()
	{
		typename List<T>::Iterator i = this->list_.end();
		return Iterator(i);
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

}

#endif // BANCH_NOSTL_SET_HXX
