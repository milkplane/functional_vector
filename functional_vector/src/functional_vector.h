#ifndef FUNCTIONAL_VECTOR_H_
#define FUNCTIONAL_VECTOR_H_

#include <cstring>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <cmath>

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

		iterator begin() const { return arr; } ;
		iterator end() const { return arr + size; };
		const_iterator cbegin() const { return arr; };
		const_iterator cend() const { return arr + size; };

		size_type max_size() const { return std::numeric_limits<size_type>::max(); };
		size_type get_capacity() const { return capacity; };
		bool empty() const { return size == 0; };
		void resize(const size_type new_size);
		void resize(const size_type new_size, const type filler);
		void reserve(const size_type new_bigger_capacity);
		void shrink_to_fit();

		
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

	template<typename type>
	void functional_vector<type>::resize(const size_type new_size) {
		type* resized_arr = new type[new_size];

		for (size_type i = 0; i < new_size; i++) {
			resized_arr[i] = arr[i];
		}

		delete[] arr;

		arr = resized_arr;
		size = new_size;
		capacity = new_size;
	}

	template<typename type>
	void functional_vector<type>::resize(const size_type new_size, const type filler) {
		if (new_size <= size) return resize(new_size);

		type* resized_arr = new type[new_size];

		size_type i;
		while (i < size) {
			resized_arr[i] = arr[i];
			i++;
		}

		while (i < new_size) {
			resized_arr[i] = filler;
			i++;
		}

		delete[] arr;

		arr = resized_arr;
		size = new_size;
		capacity = new_size;
	}

	template<typename type>
	void functional_vector<type>::reserve(const size_type new_capacity) {
		if (new_capacity <= capacity) return;

		type* arr_with_new_capacity = new type[new_capacity];

		for (size_type i = 0; i < size; i++) {
			arr_with_new_capacity[i] = arr[i];
		}

		delete[] arr;

		arr = arr_with_new_capacity;
		capacity = new_capacity;
	}

	template<typename type>
	void functional_vector<type>::shrink_to_fit() {
		return resize(size);
	}
	
}

#endif