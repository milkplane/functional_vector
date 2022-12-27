#ifndef FUNCTIONAL_VECTOR_H_
#define FUNCTIONAL_VECTOR_H_

#include <cstring>
#include <initializer_list>
#include <iterator>
#include <algorithm>

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

		enum { empty_vector_capacity = 15 };

		functional_vector();
		functional_vector(const type* arr, const size_type size, const size_type capacity);
		functional_vector(const type* arr, const size_type size) : functional_vector(arr, size, size) {};
		functional_vector(const functional_vector& other) : functional_vector(other.arr, other.size, other.capacity) {};
		functional_vector(functional_vector&& other);
		functional_vector(size_type times, type filler);
		functional_vector(const std::initializer_list<type>& li);
		virtual ~functional_vector() { delete[] arr; };

		functional_vector& operator=(const functional_vector& other);
		functional_vector& operator=(functional_vector&& other);

		iterator begin() { return arr; };
		iterator end() { return arr + size; }
		const_iterator cbegin() { return arr; }
		const_iterator cend() { return arr; }
	private:
		type* arr;
		size_type size;
		size_type capacity;
	};


	template<typename type>
	functional_vector<type>::functional_vector() {
		arr = new type[empty_vector_capacity];
		size = 0;
		capacity = empty_vector_capacity;
	}

	template<typename type>
	functional_vector<type>::functional_vector(const type* arr, const size_type size, const size_type capacity) {
		this->arr = new type[capacity];
		this->size = size;
		this->capacity = capacity;

		memcpy(this->arr, arr, sizeof(type) * capacity);
	}

	template<typename type>
	functional_vector<type>::functional_vector(functional_vector&& other) {
		arr = other.arr;
		size = other.size;
		capacity = other.capacity;

		other.arr = nullptr;
		other.size = 0;
		other.capacity = 0;
	}

	template<typename type>
	functional_vector<type>::functional_vector(size_type times, type filler) {
		size = times;
		capacity = times;
		arr = new type[times];

		for (size_type i = 0; i < size; i++) {
			arr[i] = filler;
		}
	}

	template<typename type>
	functional_vector<type>::functional_vector(const std::initializer_list<type>& li) {
		size = li.size();
		capacity = li.size();
		arr = new type[capacity];

		std::copy(li.begin(), li.end(), arr);
	}

	template<typename type>
	functional_vector<type>& functional_vector<type>::operator=(const functional_vector& other) {
		if (this == &other) return *this;

		delete[] arr;

		arr = new type[other.capacity];
		memcpy(arr, other.arr, sizeof(type) * other.capacity);
		size = other.size;
		capacity = other.capacity;
	}

	template<typename type>
	functional_vector<type>& functional_vector<type>::operator=(functional_vector&& other) {
		delete[] arr;

		arr = other.arr;
		size = other.size;
		capacity = other.capacity;

		other = nullptr;
		size = 0;
		capacity = 0;
	}
}

#endif