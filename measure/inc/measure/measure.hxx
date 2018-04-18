#ifndef MEASURE_MEASURE_HXX
#define MEASURE_MEASURE_HXX

#include <type_traits>

#include "nostl/string.hxx"

namespace measure {

template <typename T>
class Measure {

	static_assert(std::is_arithmetic<T>::value, "Type must be numeric!");

public:
	Measure(nostl::String const unit, T const & value)
	{
		this->unit_ = unit;
		this->value_ = value;
	}

	bool isSameDimension(Measure const & comparison) const
	{
		return (this->unit_ == comparison.unit_);
	}

	bool operator==(Measure const & rhs) const
	{
		return (isSameDimension(rhs) && (this->value_ == rhs.value_));
	}

	template <typename F>
	friend std::ostream & operator<<(std::ostream &, Measure<F> const);

	// TODO more operators may be needed


private:
	nostl::String unit_;
	T value_;
}; // class Measure

template <typename F>
std::ostream & operator<<(std::ostream & os, Measure<F> const obj)
{
	return os << obj.value_ << " " << obj.unit_;
}

} // namespace measure

#endif // MEASURE_MEASURE_HXX
