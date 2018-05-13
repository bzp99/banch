/// \file set.cxx
///
/// function definitions for set.hxx

#include "nostl/set.hxx"

namespace nostl {

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

} // namespace nostl
