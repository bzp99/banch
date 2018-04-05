#ifndef BANCH_NOSTL_LIST_H
#define BANCH_NOSTL_LIST_H

namespace nostl {

template <typename T>
class List {
private: class Iterator;
public:
	List() : number_of_elements_(0)
	{
		this->head_ = new Node;
		this->tail_ = new Node;

		this->head_->prev_ = nullptr;
		this->head_->next_ = this->tail_;

		this->tail_->prev_ = this->head_;
		this->tail_->next_ = nullptr;
	}

	List(const List&);

	void append(const T&);
	void prepend(const T&);
	void remove(const T&);
	void clear();

	unsigned int size() const { return this->number_of_elements_; }

	List& operator=(const List&);
	// TODO other operators?

	Iterator begin() { return (number_of_elements_ == 0) ? nullptr : Iterator(this->head_->next_->value_); }
	Iterator end() { return (number_of_elements_ == 0) ? nullptr : Iterator(this->head->prev_->value_); }

	~List();


private:
	struct Node {
		T value_;
		Node * previous_;
		Node * next_;
	};

private:
	class Iterator {
	public:
		Iterator() : pointer_(nullptr) {}
		Iterator(T * where_to_point) : pointer_(where_to_point) {}

		T& operator*() { return *pointer_; } // dereference
		void operator++() // preincrement
		{
			// FIXME nothing
		}

	private:
		T * pointer_;
	};

private:
	Node * find(const T&) const;

private:
	Node * head_;
	Node * tail_;
	unsigned int number_of_elements_;
}; // class List

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
	this->head_->prev_ = nullptr;
	this->head_->next_ = this->tail_;
	this->tail_->prev_ = this->head_;
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
	new_node->prev_ = this->tail_->prev_;
	new_node->next_ = this->tail_;

	// setting neighbouring nodes' pointers
	new_node->prev_->next_ = new_node;
	new_node->next_->prev_ = new_node;

	// incrementing counter
	++this->number_of_elements_;
}

template <typename T>
void List<T>::prepend(const T& val)
{
	Node * new_node = new Node;
	new_node->value_ = val;

	// setting new_node's pointers
	new_node->prev_ = this->head_;
	new_node->next_ = this->head_->next_;

	// setting neighbouring nodes' pointers
	new_node->prev_->next_ = new_node;
	new_node->next_->prev_ = new_node;

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
		delendum->prev_->next_ = delendum->next_;
		delendum->next_->prev_ = delendum->prev_;

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
		delete traveller->prev_;
	}

	// resetting pointers of sentinels
	this->head_->next_ = this->tail_;
	this->tail_->prev_ = this->head_;

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
