#ifndef BANCH_NOSTL_LIST_H
#define BANCH_NOSTL_LIST_H

namespace nostl {

template <typename T>
class List {
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

	void append(T);
	void prepend(T);
	void remove(T);

	unsigned int size() const { return this->number_of_elements_; }


private:
	struct Node {
		T value_;
		Node * previous_;
		Node * next_;
	};

private:
	Node * find(T) const;

private:
	Node * head_;
	Node * tail_;
	unsigned int number_of_elements_;
}; // class List

template <typename T>
typename List<T>::Node * List<T>::find(T val) const
{
	Node * traveller = this->head_->next_; // temporary node

	// traverse list to find node
	while(traveller->next_ != this->tail_)
	{
		if (traveller->value_ == val)
		{
			return traveller;
		}
	}

	// node was not found
	return nullptr;
}

template <typename T>
void List<T>::append(T val)
{
	Node * new_node = new Node;
	new_node->value_ = val;

	// setting new_node's pointers
	new_node->prev_ = this->tail_->prev_;
	new_node->next_ = this->tail_;

	// setting neighbouring nodes' pointers
	new_node->prev_->next_ = new_node;
	new_node->next_->prev_ = new_node;
}

template <typename T>
void List<T>::prepend(T val)
{
	Node * new_node = new Node;
	new_node->value_ = val;

	// setting new_node's pointers
	new_node->prev_ = this->head_;
	new_node->next_ = this->head_->next_;

	// setting neighbouring nodes' pointers
	new_node->prev_->next_ = new_node;
	new_node->next_->prev_ = new_node;
}

template <typename T>
void List<T>::remove(T val)
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
	}
}

} // namespace nostl

#endif // BANCH_NOSTL_LIST_H
