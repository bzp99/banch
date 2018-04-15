#ifndef BANCH_NOSTL_LIST_H
#define BANCH_NOSTL_LIST_H

namespace nostl {

/// \brief re-implementation of std::List<T>
///
/// \tparam T type of elements that the List contains
///
/// I had to re-implement the List class because using STL containers was
/// prohibited. My List is doubly-linked and has two sentinels (a head and a
/// tail).
template <typename T>
class List {
public:
	/// \brief constructor w/o parameters --- only initialises memory
	List();

	/// \brief copy constructor
	///
	/// \param List to copy
	///
	/// The default copy constructor needs to be overridden because it would
	/// only copy pointers to the head and tail of the list.
	List(List const &);

	/// \brief assignment operator
	///
	/// \param List to set *this* equal to
	///
	/// \return the List itself
	List & operator=(List const &);


	/// \brief add element to end of List
	///
	/// \param value of new element
	void append(T const &);

	/// \brief add element to beginning of List
	///
	/// \param value of new element
	void prepend(T const &);

	/// \brief remove an element from the List
	///
	/// \param value of element to remove
	///
	/// \note this function only deletes the first occurrence of the value
	/// that's passed as a parameter
	void remove(T const &);

	/// \brief clear the list (i.e. remove all of its elements)
	void clear();

	/// \brief get the size of the list (i.e. the number of its elements)
	///
	/// \return the List's size
	unsigned int size() const { return this->number_of_elements_; }


	/// \brief destructor
	///
	/// The default destructor function needs to be overridden because the class
	/// uses dynamic memory allocation
	~List();


private:
	/// \brief the doubly-linked list consists of these nodes
	///
	/// Each Node has a value and knows the preceding and succeeding Node's
	/// address
	struct Node {
		T value_; ///< the actual value that is stored by the Node
		Node * previous_; ///< address of preceding Node
		Node * next_; ///< address of succeeding Node
	};

private:
	/// \brief get address of first element in the List with a given value
	///
	/// \param value to search for
	///
	/// \return address of Node with value passed as parameter
	///
	/// \note the function obviously returns the *first* occurrence of the value
	/// passed as parameter
	Node * find(T const &) const;

private:
	Node * head_; ///< head sentinel (its value is irrelevant)
	Node * tail_; ///< tail sentinel (its value is irrelevant)
	unsigned int number_of_elements_; ///< size of the List


public:
	/// \brief custom made iterator to navigate the List more easily
	class Iterator {
	public:
		/// \brief construr for the List's Iterator w/o parameter
		///
		/// TODO why do I need this?
		Iterator() {}

		/// \brief constructor for the List's Iterator
		///
		/// \param where_to_point address Node to point to
		/// \param first_sentinel address of the List's head sentinel
		/// \param last_sentinel address f the List's tail sentinel
		Iterator(Node * where_to_point,
					Node * first_sentinel,
					Node * last_sentinel)
		{
			this->current_ = where_to_point;
			this->first_sentinel_ = first_sentinel;
			this->last_sentinel_ = last_sentinel;
		}


		/// \brief dereference operator
		///
		/// \return the value of the Node currently pointed to
		T & operator*() { return this->current_->value_; }

		/// \brief const dereference operator
		///
		/// \return the value of the Node currently pointed to
		T const & operator*() const { return this->current_->value_; }

		/// \brief member access operator
		///
		/// \return pointer to itself
		///
		/// \note this is just needed for convenience
		Iterator *  operator->() { return this; }


		/// \brief preincrement operator
		///
		/// \return Iterator of next Node
		Iterator operator++()
		{
			if (this->current_->next_ != this->last_sentinel_)
			{
				this->current_ = this->current_->next_;
			}
			return *this;
		}

		/// \brief postincrement operator
		///
		/// \param int dummy parameter
		///
		/// \return Iterator of current Node
		Iterator operator++(int)
		{
			Iterator rv = *this;
			if (this->current_->next_ != this->last_sentinel_)
			{
				this->current_ = this->current_->next_;
			}
			return rv;
		}

		/// \brief predecrement operator
		///
		/// \return Iterator of previous Node
		Iterator operator--()
		{
			if (this->current_->previous_ != this->first_sentinel_)
			{
				this->current_ = this->current_->previous_;
			}
			return *this;
		}

		/// \brief postdecrement operator
		///
		/// \param int dummy parameter
		///
		/// \return Iterator of current Node
		Iterator operator--(int)
		{
			Iterator rv = *this;
			if (this->current_->previous_ != this->first_sentinel_)
			{
				this->current_ = this->current_->previous_;
			}
			return rv;
		}


		/// \brief equality operator
		///
		/// \param rhs Iterator to check equality with
		///
		/// \return true if the Iterators point to the same Node
		bool operator==(Iterator const & rhs) const
		{
			return this->current_ == rhs.current_;
		}

		/// \brief inequality operator
		///
		/// \param rhs Iterator to check inequality with
		///
		/// \return true if the Iterators point to different Nodes
		bool operator!=(Iterator const & rhs) const { return !(*this == rhs); }


	private:
		Node * current_; ///< currently pointed Node
		Node * first_sentinel_; ///< lower bound (can't go 'below' this)
		Node * last_sentinel_; ///< upper bound (can't go 'above' this)
	}; // class Iterator

public:
	/// \brief get Iterator to the first element of the List
	///
	/// \return the first List element (right after the head sentinel)
	///
	/// TODO should we really return nullptrs in case the List is empty?
	Iterator begin()
	{
		if (this->size() == 0)
		{
			return Iterator(nullptr, nullptr, nullptr);
		}
		else
		{
			return Iterator(this->head_->next_, this->head_, this->tail_);
		}
	}

	/// \brief get Iterator to the last element of the List
	///
	/// \return the last List element (right before the tail sentinel)
	///
	/// TODO should we really return nullptrs in case the List is empty?
	Iterator end()
	{
		if (this->size() == 0)
		{
			return Iterator(nullptr, nullptr, nullptr);
		}
		else
		{
			return Iterator(this->tail_->previous_, this->head_, this->tail_);
		}
	}
}; // class List

template <typename T>
List<T>::List()
{
	this->number_of_elements_ = 0;

	this->head_ = new Node;
	this->tail_ = new Node;

	this->head_->previous_ = nullptr;
	this->head_->next_ = this->tail_;

	this->tail_->previous_ = this->head_;
	this->tail_->next_ = nullptr;
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
		this->append(traveller->value_); // this also sets the counter
		traveller = traveller->next_;
	}
}

template <typename T>
void List<T>::append(T const & val)
{
	Node * new_node = new Node;
	new_node->value_ = val;

	// setting new_node's pointers
	new_node->previous_ = this->tail_->previous_;
	new_node->next_ = this->tail_;

	// setting neighbouring nodes' pointers
	new_node->previous_->next_ = new_node;
	new_node->next_->previous_ = new_node;

	// incrementing counter
	++this->number_of_elements_;
}

template <typename T>
void List<T>::prepend(T const & val)
{
	Node * new_node = new Node;
	new_node->value_ = val;

	// setting new_node's pointers
	new_node->previous_ = this->head_;
	new_node->next_ = this->head_->next_;

	// setting neighbouring nodes' pointers
	new_node->previous_->next_ = new_node;
	new_node->next_->previous_ = new_node;

	// incrementing counter
	++this->number_of_elements_;
}

template <typename T>
void List<T>::remove(T const & val)
{
	// find node
	Node * delendum = find(val);

	if (delendum != nullptr)
	{
		// set neighbouring nodes' pointers
		delendum->previous_->next_ = delendum->next_;
		delendum->next_->previous_ = delendum->previous_;

		// delete delendum
		delete delendum;

		// decrementing counter
		--this->number_of_elements_;
	}
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

	// zero counter
	this->number_of_elements_ = 0;
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
		this->append(traveller->value_); // this also sets the counter
		traveller = traveller->next_;
	}

	return *this;
}

template <typename T>
List<T>::~List()
{
	// clear list
	this->clear();

	// delete sentinels
	delete this->head_;
	delete this->tail_;
}

} // namespace nostl

#endif // BANCH_NOSTL_LIST_H
