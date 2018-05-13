/// \file list.cxx
///
/// function declarations for the list.hxx

#include "nostl/list.hxx"

/// \brief namespace for STL reimplementations
namespace nostl {

template <typename T>
List<T>::List(List const & obj)
{
	// initiating empty list
	this->head_ = new Node;
	this->tail_ = new Node;
	this->head_->previous_ = nullptr;
	this->head_->next_ = this->tail_;
	this->tail_->previous_ = this->head_;
	this->tail_->next_ = nullptr;
	this->number_of_elements_ = 0;

	// copying list
	Node * traveller = obj.head_->next_;
	while (traveller->next_ != obj.tail_)
	{
		this->append(traveller->value_); // this also sets the node counter
		traveller = traveller->next_;
	}
}

template <typename T>
List<T> & List<T>::operator=(List<T> const & rhs)
{
	// checking for self-assignment
	if (this == &rhs)
	{
		return *this;
	}

	// clearing current list
	this->clear();

	// if rhs is empty, we're done
	if (rhs.size() == 0)
	{
		return *this;
	}

	// copying list
	Node * traveller = rhs.head_->next_;
	while (traveller != rhs.tail_)
	{
		this->append(traveller->value_); // this also sets the node counter
		traveller = traveller->next_;
	}

	return *this;
}

template <typename T>
typename List<T>::Node * List<T>::find(T const & val) const
{
	// if the List is empty, nothing will be found
	if (this->size() == 0)
	{
		return nullptr;
	}

	Node * traveller = this->head_->next_;

	// traverse list to find node
	while(traveller != this->tail_)
	{
		if (traveller->value_ == val)
		{
			return traveller;
		}

		traveller = traveller->next_;
	}

	// node was not found
	return nullptr;
}

template <typename T>
void List<T>::clear()
{
	// traverse list and delete nodes between sentinels
	Node * traveller = this->head_->next_;
	while (traveller != this->tail_)
	{
		traveller = traveller->next_;
		delete traveller->previous_;
	}

	// resetting pointers of sentinels
	this->head_->next_ = this->tail_;
	this->tail_->previous_ = this->head_;

	// zero node counter
	this->number_of_elements_ = 0;
}

template <typename T>
bool List<T>::operator==(List<T> const & rhs) const
{
	// the lists cannot be equal if their size differs
	if (this->size() != rhs.size())
	{
		return false;
	}

	// iterate through both lists, comparing each element
	List<T>::Iterator i = this->begin();
	List<T>::Iterator j = rhs.begin();
	while (i != this->end())
	{
		// if two elements don't match up, the Lists are different
		if (*(i++) != *(j++))
		{
			return false;
		}
	}

	// if we got here, the Lists must be identical
	return true;
}

} // namespace nostl
