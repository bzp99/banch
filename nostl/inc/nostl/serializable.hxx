#ifndef BANCH_NOSTL_SERIALIZABLE_HXX
#define BANCH_NOSTL_SERIALIZABLE_HXX

/// \file serialize.hxx
///
/// \brief class to derive classes from that use serialization

#include <iostream>

// TODO this doesn't really belong into this namespace
namespace nostl {

/// \brief abstract class for a serializable object
class Serializable {
public:
	/// \brief virtual serializing function
	///
	/// \param stream to serialize into
	virtual void serialize(std::ostream &) const = 0;


	/// \brief virtual deserializing function
	///
	/// \param stream to deserialize from
	virtual void deserialize(std::istream &) = 0;

	/// \brief virtual destructor
	virtual ~Serializable() {}
}; // class Serializable

} // namespace nostl

#endif // BANCH_NOSTL_SERIALIZABLE_HXX
