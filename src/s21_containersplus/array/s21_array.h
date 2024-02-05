#ifndef SRC_S21_ARRAY_H
#define SRC_S21_ARRAY_H

#include <iostream>
#include <limits>

// Array (массив) - это последовательный контейнер, инкапсулирующий в себе статический массив.
// В контейнер array нельзя добавить новый элементы, можно только модифицировать значение заданных изначально.

namespace s21 {
    template<typename T, std::size_t N>
    class array {
    public:
        using value_type = T; // defines the type of element (T is template parameter)
        using reference = T&; // defines the type of the reference to an element
        using const_reference = const T&; // defines the type of the constant reference
        using iterator = T*; // defines the type for iterating through the container
        using const_iterator = const T*; // defines the constant type for iterating through the container
        using size_type = size_t; // defines the type of the container size (standard type is size_t)

        array(); // default constructor, creates empty array
        array(std::initializer_list<value_type> const &items); // initializer list constructor, creates array initizialized using std::initializer_list
        array(const array &other); // copy constructor
        array(array &&other) noexcept; // move constructor
        ~array() = default; // destructor

        array &operator=(const array &other);
        array &operator=(array &&other) noexcept; // assignment operator overload for moving object

        iterator begin(); // returns an iterator to the beginning
        iterator end(); // returns an iterator to the end
        const_iterator cbegin() const;
        const_iterator cend() const;

        reference at(size_type pos); // access specified element with bounds checking
        const_reference at(size_type pos) const;
        reference operator[](size_type pos); // access specified element
        const_reference operator[](size_type pos) const;
        reference front();
        reference back();
        const_reference front() const; // access the first element
        const_reference back() const; // access the last element
        iterator data(); // direct access to the underlying array

        bool empty(); // checks whether the container is empty
        size_type size(); // returns the number of elements
        size_type max_size(); // returns the maximum possible number of elements

        void swap(array& other); // swaps the contents
        void fill(const_reference value);; // assigns the given value to all elements in the container.

    private:
        value_type elems_[N] = {};
        size_type size_ = N;
    };

    template<typename T, std::size_t N>
    array<T, N>::array() : size_(N) {}

    template<typename T, std::size_t N>
    array<T, N>::array(const std::initializer_list<value_type> &items) {
        std::copy(items.begin(), items.end(), elems_);
    }

    template<typename T, std::size_t N>
    array<T, N>::array(const array &other) {
//        elems_ = other.elems_;
        std::copy(other.elems_, other.elems_ + N, elems_);
    }

    template<typename T, std::size_t N>
    array<T, N>::array(array &&other) noexcept {
        std::move(other.elems_, other.elems_ + N, elems_);
    }

    template<typename T, std::size_t N>
    typename array<T, N>::iterator array<T, N>::begin() {
        return elems_;
    }

    template<typename T, std::size_t N>
    typename array<T, N>::iterator array<T, N>::end() {
        return elems_ + size_;
    }

    template<typename T, std::size_t N>
    typename array<T, N>::const_iterator array<T, N>::cbegin() const {
        return elems_;
    }

    template<typename T, std::size_t N>
    typename array<T, N>::const_iterator array<T, N>::cend() const {
        return elems_ + size_;
    }

    template<typename T, std::size_t N>
    typename array<T, N>::reference array<T, N>::front() {
        return elems_[0];
    }

    template<typename T, std::size_t N>
    typename array<T, N>::reference array<T, N>::back() {
        return elems_[N - 1];
    }

    template<typename T, std::size_t N>
    typename array<T, N>::const_reference array<T, N>::front() const {
        return elems_[0];
    }

    template<typename T, std::size_t N>
    typename array<T, N>::const_reference array<T, N>::back() const {
        return elems_[N - 1];
    }

    template<typename T, std::size_t N>
    typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
        // у "[]" нет проверки о выходе за пределы массива (а у метода "at" есть)
        return elems_[pos];
    }

    template<typename T, std::size_t N>
    typename array<T, N>::const_reference array<T, N>::operator[](size_type pos) const {
        return elems_[pos];
    }

    template<typename T, std::size_t N>
    typename array<T, N>::reference array<T, N>::at(size_type pos) {
        if (pos >= N) {
            throw std::out_of_range("OutOfRangeError: Index out of array range");
        }
        return elems_[pos];
    }

    template<typename T, std::size_t N>
    typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
        if (pos >= N) {
            throw std::out_of_range("OutOfRangeError: Index out of array range");
        }
        return elems_[pos];
    }

    // TODO: так ли?
    template<typename T, std::size_t N>
    typename array<T, N>::iterator array<T, N>::data() {
        return elems_;
    }

    template<typename T, std::size_t N>
    bool array<T, N>::empty() {
        return size_ == 0; // !size_
    }

    template<typename T, std::size_t N>
    typename array<T, N>::size_type array<T, N>::size() {
        return size_;
    }

    template<typename T, std::size_t N>
    typename array<T, N>::size_type array<T, N>::max_size() {
        return size();
//        return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
    }

    template<typename T, std::size_t N>
    void array<T, N>::swap(array &other) {
        std::swap_ranges(elems_, elems_ + N, other.elems_);
    }

    template<typename T, std::size_t N>
    void array<T, N>::fill(const_reference value) {
        std::fill(elems_, elems_ + N, value);
    }

    template <typename T, std::size_t N>
    array<T, N> &array<T, N>::operator=(const array &other) {
        std::copy(other.elems_, other.elems_ + N, elems_);
        return *this;
    }

    template <typename T, std::size_t N>
    array<T, N> &array<T, N>::operator=(array &&other) noexcept {
    for (size_t i = 0; i < N; ++i) {
        elems_[i] = std::move(other.elems_[i]);
    }
    return *this;
    }

} // namespace s21
#endif //SRC_S21_ARRAY_H
