#ifndef FUNCTIONAL_VECTOR_H_
#define FUNCTIONAL_VECTOR_H_

namespace nostd {
	template <typename type>
	class functional_vector {
	public:
		using value_type = type;
		using reference = type&;
		using const_reference = const reference;
		using pointer = value_type*;
		using const_pointer = const pointer;
		using iterator = value_type*;
		using const_iterator = const iterator;
		using size_type = size_t;
	};
}

#endif