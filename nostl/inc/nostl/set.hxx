#ifndef BANCH_NOSTL_SET_HXX
#define BANCH_NOSTL_SET_HXX

#include "nostl/list.hxx"

namespace nostl {

template <typename T>
class Set { // implementing Set class for STL containers are prohibited
public:
	Set() : number_of_elements_(0), list_(new List<T>) {}

	Set(Set const & obj) : number_of_elements_(obj.number_of_elements_), list_(obj.list_) {}

	Set & operator=(Set const &);

	void insert(T const &);
	void remove(T const &);
	void clear();

	unsigned int size() const { return this->number_of_elements_; }

	~Set() { delete this->list_; }

public: // nested class
	class Iterator {
	public:
		Iterator(typename List<T>::Iterator list_iterator) : list_iterator_(list_iterator) {}

		T & operator*() { return *(this->list_iterator_); } // derefence with * / var
		T const & operator*() const { return *(this->list_iterator_); } // derefence with * / const
		Iterator * operator->() const { return this; } // dereference with ->
		Iterator operator++() // preincrement
		{
			++this->list_iterator_;
			return *this;
		}
		Iterator operator++(int) // postincrement
		{
			Iterator rv = *this;
			++this->list_iterator_;
			return rv;
		}
		Iterator operator--() // predecrement
		{
			--this->list_iterator_;
			return *this;
		}
		Iterator operator--(int) // postdecrement
		{
			Iterator rv = *this;
			--this->list_iterator_;
			return rv;
		}
		bool operator==(Iterator const & rhs) const { return this->list_iterator_ == rhs.list_iterator_; }
		bool operator!=(Iterator const & rhs) const { return !(*this == rhs); }


	private:
		typename List<T>::Iterator list_iterator_;
	}; // class Iterator

public: // functions of nested class
	Iterator begin()
	{
		typename List<T>::Iterator i = this->list_->begin();
		return Iterator(i);
	}
	Iterator end()
	{
		typename List<T>::Iterator i = this->list_->end();
		return Iterator(i);
	}


private: // data members
	List<T> * list_;
	unsigned int number_of_elements_;

}; // class Set

template <typename T>
typename Set<T>::Set & Set<T>::operator=(Set const & rhs)
{
	// check for self assignment
	if (this == &rhs)
	{
		return *this;
	}

	this->clear();
	this->number_of_elements_ = rhs.number_of_elements_;
	this->list_ = rhs.list_;

	return *this;
}

template <typename T>
void Set<T>::insert(T const & val)
{
	// make sure list/set doesn't contain item yet
	if (this->number_of_elements_ != 0)
	{
		for (typename List<T>::Iterator i = this->list_->begin(); i != this->list_->end(); ++i)
		{
			if (*i == val)
			{
				return;
			}
		}
	}

	this->list_->append(val);
	++this->number_of_elements_;
}

template <typename T>
void Set<T>::remove(T const & val)
{
	this->list_->remove(val);
	--this->number_of_elements_;
}

template <typename T>
void Set<T>::clear()
{
	this->list_->clear();
	this->number_of_elements_ = 0;
}

}

#endif // BANCH_NOSTL_SET_HXX
