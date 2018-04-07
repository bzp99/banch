#ifndef BANCH_NOSTL_LIST_H
#define BANCH_NOSTL_LIST_H

namespace nostl {

template <typename T>
class List { // implementing List class for STL containers are prohibited
public: // main body
	List();

	List(const List&);

	List& operator=(const List&);

	void append(const T&);
	void prepend(const T&);
	void remove(const T&);
	void clear();

	unsigned int size() const { return this->number_of_elements_; }

	~List();


private: // nested class
	struct Node {
		T value_;
		Node * previous_;
		Node * next_;
	};

private: // private function
	Node * find(const T&) const;

private: // data members
	Node * head_;
	Node * tail_;
	unsigned int number_of_elements_;

public: // nested class
	class Iterator {
	public:
		Iterator() {}
		Iterator(Node * where_to_point, Node * first_sentinel, Node * last_sentinel) : current_(where_to_point), first_sentinel_(first_sentinel), last_sentinel_(last_sentinel) {}

		T& operator*() const { return this->current_->value_; } // dereference with *
		Iterator *  operator->() { return this; } // dereference with ->
		Iterator operator++() // preincrement
		{
			if (this->current_->next_ != this->last_sentinel_)
			{
				this->current_ = this->current_->next_;
			}
			return *this;
		}
		Iterator operator++(int) // postincrement
		{
			Iterator rv = *this;
			if (this->current_->next_ != this->last_sentinel_)
			{
				this->current_ = this->current_->next_;
			}
			return rv;
		}
		Iterator operator--() // predecrement
		{
			if (this->current_->previous_ != this->first_sentinel_)
			{
				this->current_ = this->current_->previous_;
			}
			return *this;
		}
		Iterator operator--(int) // postdecrement
		{
			Iterator rv = *this;
			if (this->current_->previous_ != this->first_sentinel)
			{
				this->current_ = this->current_->previous_;
			}
			return rv;
		}
		bool operator==(Iterator& rhs) const { return this->current_ == rhs.current_; }
		bool operator!=(Iterator& rhs) const { return !(*this == rhs); }


	private:
		Node * current_;
		Node * first_sentinel_;
		Node * last_sentinel_;
	}; // class Iterator

public: // functions of nested class
	Iterator begin() { return (number_of_elements_ == 0) ? Iterator(nullptr, nullptr, nullptr) : Iterator(this->head_->next_, this->head_, this->tail_); }
	Iterator end() { return (number_of_elements_ == 0) ? Iterator(nullptr, nullptr, nullptr) : Iterator(this->head_->previous_, this->head_, this->tail_); }

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
typename List<T>::Node * List<T>::find(const T& val) const
{
	Node * traveller = this->head_->next_; // temporary node

	// traverse list to find node
	while(traveller->next_ != this->tail_)
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
List<T>::List(const List& obj)
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
		this->append(traveller); // this also sets the counter
		traveller = traveller->next_;
	}
}

template <typename T>
void List<T>::append(const T& val)
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
void List<T>::prepend(const T& val)
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
void List<T>::remove(const T& val)
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
List<T>& List<T>::operator=(const List<T>& rhs)
{
	// checking for self-assignment
	if (this == &rhs)
	{
		return *this;
	}

	// clearing current list
	this->clear();

	// copying list
	Node * traveller = rhs.head_->next_;
	while (traveller->next_ != rhs.tail_)
	{
		this->append(traveller); // this also sets the counter
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
