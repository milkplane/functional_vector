#ifndef FUNCTIONAL_VECTOR_H_
#define FUNCTIONAL_VECTOR_H_

#include <cstring>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace nostd {
	template <typename type>
	class functional_vector {
	public:
		// Typedefs
		using value_type = type;
		using reference = type&;
		using const_reference = const type&;
		using pointer = value_type*;
		using const_pointer = const type*;
		using iterator = type*;
		using const_iterator = const type*;
		using size_type = size_t;

		enum { empty_vector_capacity = 15 };

		// Constractors
		functional_vector();
		functional_vector(const type* arr, const size_type size, const size_type capacity);
		functional_vector(const type* arr, const size_type size) : functional_vector(arr, size, size) {};
		functional_vector(const functional_vector& other) : functional_vector(other.arr, other.size, other.capacity) {};
		functional_vector(functional_vector&& other);
		functional_vector(size_type times, type filler);
		functional_vector(const std::initializer_list<type>& li);

		// Destractors
		virtual ~functional_vector() { delete[] arr; };

		// Operators
		functional_vector& operator=(const functional_vector& other);
		functional_vector& operator=(functional_vector&& other);
		reference operator[](size_type i) { return arr[i]; };
		const_reference operator[](size_type i) const { return arr[i]; };
		reference at(const size_type i);
		const_reference at(const size_type i) const;

		// Iterators
		iterator begin() const { return arr; } ;
		iterator end() const { return arr + size; };
		const_iterator cbegin() const { return arr; };
		const_iterator cend() const { return arr + size; };

		// Capacity
		size_type max_size() const { return std::numeric_limits<size_type>::max(); };
		size_type get_size() const { return size; };
		size_type get_capacity() const { return capacity; };
		bool empty() const { return size == 0; };
		void resize(const size_type new_size);
		void resize(const size_type new_size, const type filler);
		void reserve(const size_type new_bigger_capacity);
		void shrink_to_fit();

		// Modifiers
		void push_back(const reference item);
		void push_back(type&& item);
		void pop_back();
		void clear();
		void swap(functional_vector& other);

		// Non-memebers
		template <typename type>
		friend std::ostream& operator<<(std::ostream& stream, const functional_vector<type>& v);
	private:
		type* arr;
		size_type size;
		size_type capacity;

		void reallocate(size_type new_capcity);
		void increase_capacity();
		void increase_size();
		void copy(const type* arr, const size_type size, const size_type capacity);
	};


	template<typename type>
	functional_vector<type>::functional_vector() {
		arr = new type[empty_vector_capacity];
		size = 0;
		capacity = empty_vector_capacity;
	}

	template<typename type>
	functional_vector<type>::functional_vector(const type* arr, const size_type size, const size_type capacity) {
		copy(arr, size, capacity);
	}

	template<typename type>
	functional_vector<type>::functional_vector(functional_vector&& other) {
		clear();
		swap(other);
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

		copy(other.arr, other.size, other.capacity);

		return *this;
	}

	template<typename type>
	functional_vector<type>& functional_vector<type>::operator=(functional_vector&& other) {
		clear();
		swap(other);

		return *this;
	}

	template<typename type>
	typename functional_vector<type>::reference functional_vector<type>::at(const size_type i) {
		if (i < 0 || i >= size) throw std::out_of_range("index is out of range");

		return arr[i];
	}

	template<typename type>
	typename functional_vector<type>::const_reference functional_vector<type>::at(const size_type i) const {
		return *this[i];
	}

	template<typename type>
	void functional_vector<type>::resize(const size_type new_size) {
		reallocate(new_size);
		size = new_size;
	}

	template<typename type>
	void functional_vector<type>::resize(const size_type new_size, const type filler) {
		if (new_size <= size) return resize(new_size);

		reallocate(new_size);
		
		for (size_type i = size; i < new_size; i++) {
			arr[i] = filler;
		}

		size = new_size;
	}

	template<typename type>
	void functional_vector<type>::reserve(const size_type new_capacity) {
		if (new_capacity <= capacity) return;

		reallocate(new_capacity);
	}

	template<typename type>
	void functional_vector<type>::shrink_to_fit() {
		return resize(size);
	}

	template <typename type>
	void functional_vector<type>::push_back(const functional_vector<type>::reference item) {
		increase_size();
		arr[size - 1] = item;
	}

	template <typename type>
	void functional_vector<type>::push_back(type&& item) {
		increase_size();
		arr[size - 1] = std::move(item);
	}

	template <typename type>
	void functional_vector<type>::pop_back() {
		size--;
	}

	template <typename type>
	void functional_vector<type>::clear() {
		delete[] arr;

		arr = nullptr;
		size = 0;
		capacity = 0;
	}

	template <typename type>
	void functional_vector<type>::swap(functional_vector<type>& other) {
		std::swap(other.arr, arr);
		std::swap(other.size, size);
		std::swap(other.capacity, capacity);
	}

	template<typename type>
	std::ostream& operator<<(std::ostream& stream, const functional_vector<type>& v) {
		if (v.size == 0) return stream;

		stream << v.arr[0];

		typedef functional_vector<type>::size_type size_type;
		for (size_type i = 1; i < v.size; i++) {
			stream << ' ' << v.arr[i];
		}

		return stream;
	}

	template <typename type>
	void functional_vector<type>::reallocate(size_type new_capcity) {
		type* old_pointer = arr;
		arr = new type[new_capcity];
		
		copy(old_pointer, size, new_capcity);

		delete[] old_pointer;
	}

	template <typename type>
	void functional_vector<type>::increase_capacity() {
		reallocate(capacity * 1.6 + 1);
	}

	template <typename type>
	void functional_vector<type>::increase_size() {
		if (size == capacity) {
			increase_capacity();
		}

		size++;
	}

	template <typename type>
	void functional_vector<type>::copy(const type* arr, const size_type size, const size_type capacity) {
		delete[] this->arr;

		this->arr = new type[capacity];
		this->size = size;
		this->capacity = capacity;

		memcpy(this->arr, arr, sizeof(type) * size);
	}
	
}

#endif