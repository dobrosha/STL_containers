#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <iostream>
#include <limits>
//#include "s21_vector_iterators.h"
#include <initializer_list>
//using namespace std;

// Конструктор по умолчанию - позволяет создать объект класса с параметрами, которые нужны
// т.е. чтобы не создавался мусор и чтобы инициализация объекта была правильной

namespace s21 {
// Делаем класс шаблонным
    template<typename T>
    class vector {
    public:
        // объявляем вложенные классы для класса vector (вложенные, тк данные итераторы будут использоваться только для вектора)
        class VectorIterator;
        class VectorConstIterator;

        // T defines the type of element (T is template parameter)
        using value_type = T;
        // T & defines the type of the reference to an element
        using reference = T&;
        // const T & defines the type of the constant reference
        using const_reference = const T&;

        using iterator_pointer = T*;
        using const_iterator_pointer = const T*;
        // T * or internal class VectorIterator<T> defines the type for iterating through the container
        using iterator = vector<T>::VectorIterator;
        // const T * or internal class VectorConstIterator<T> defines the constant type for iterating through the container
        using const_iterator = vector<T>::VectorConstIterator;
        // Специальный беззнаковый целочисленный тип size_t для корректной работы программы.
        // Данный тип перекладывает заботу о возможном разном поведении целочисленных переменных при смене платформы с плеч
        // программиста на реализацию стандартной библиотеки. Поэтому использование типа size_t безопаснее и эффективнее,
        // чем использование обычных беззнаковых целочисленных типов.
        using size_type = size_t;

        vector(); // Конструктор по умолчанию без параметров
        explicit vector(size_type n); // Конструктор с 1 параметром: должен создаться массив из n элементов + все эл-ты = 0; explicit - чтобы не было неявного преобразования типов
        vector(std::initializer_list<value_type> const &items); // initializer list constructor, creates vector initizialized using std::initializer_list
        vector(const vector &v); // copy constructor
        vector(vector &&v) noexcept; // move constructor
        ~vector(); // destructor
        vector &operator=(vector &&v) noexcept; // assignment operator overload for moving object

        reference at(size_type pos); // access specified element with bounds checking
        reference operator[](size_type pos); // access specified element
        const_reference operator[](size_type pos) const; // access specified element
        const_reference front() const; // access the first element
        const_reference back() const; // access the last element
        iterator_pointer data() noexcept; // direct access to the underlying array

        iterator begin(); // returns an iterator to the beginning
        iterator end(); // returns an iterator to the end
        const_iterator cbegin() const; // returns a const iterator to the beginning
        const_iterator cend() const; // returns a const iterator to the end

        bool empty() const; // checks whether the container is empty
        size_type size() const; // returns the number of elements
        size_type max_size() const; // returns the maximum possible number of elements
        void reserve(size_type size); // allocate storage of size elements and copies current array elements to a newely allocated array
        size_type capacity() const; // returns the number of elements that can be held in currently allocated storage
        void shrink_to_fit(); // reduces memory usage by freeing unused memory

        void clear() noexcept; // clears the contents
        iterator insert(iterator pos, const_reference value); // inserts elements into concrete pos and returns the iterator that points to the new element
        void erase(iterator pos); // erases element at pos
        void push_back(const_reference value); // adds an element to the end
        void pop_back(); // removes the last element
        void swap(vector &other); // swaps the contents

        template <typename... Args>
        iterator insert_many(const_iterator pos, Args &&...args);
        template <typename... Args>
        void insert_many_back(Args &&...args);

    private:
        iterator_pointer data_;
        size_type size_;
        size_type capacity_;
    };

//template <typename T>
//vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}
//
//template <typename T>
//vector<T>::vector(size_type n) : data_(new value_type[n]), size_(n), capacity_(n) {
//    for (int i = 0; i < n; i++) {
//        data_[i] = 0;
//    }
////    std::fill_n(data_, n_, 0);
//}
//
//template <typename T>
//vector<T>::vector(std::initializer_list<value_type> const &items): data_(new value_type[items.size()]), size_(items.size()), capacity_(items.size()) {
//    std::copy(items.begin(), items.end(), data_);
//}
//
//template <typename T>
//vector<T>::vector(const vector &v): data_(new value_type[v.capacity_]), size_(v.size_), capacity_(v.capacity_) {
//    std::copy(v.data_, v.data_ + v.size_, data_);
//}
//
//template <typename T>
//vector<T>::vector(vector &&v) noexcept {
//    size_ = std::exchange(v.size_, 0);
//    capacity_ = std::exchange(v.capacity_, 0);
//    data_ = std::exchange(v.data_, nullptr);
//}
//
//template <typename T>
//vector<T>::~vector() {
//    delete[] data_;
//    size_ = 0;
//    capacity_ = 0;
//    data_ = nullptr;
//}
//
//template <typename T>
//vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
//    if (this != &v) {
//        this->swap(v);
//        delete[] v.data_;
//        v.size_ = 0;
//        v.capacity_ = 0;
//        v.data_ = nullptr;
//    }
//    return *this;
//}
//
//template <typename T>
//typename vector<T>::reference vector<T>::at(size_type pos) {
//    if (pos >= size_) {
//        throw std::out_of_range("AtError: Index out of range");
//    }
//    return data_[pos];
//}
//
//template <typename T>
//typename vector<T>::reference vector<T>::operator[](size_type pos) {
//    if (pos >= size_) {
//        throw std::out_of_range("IndexError: Index out of range");
//    }
//    return data_[pos];
//}
//
//template <typename T>
//typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
//    if (pos >= size_) {
//        throw std::out_of_range("IndexError: Index out of range");
//    }
//    return data_[pos];
//}
//
//template <typename T>
//typename vector<T>::const_reference vector<T>::front() const {
//    if (!size_) {
//        throw std::out_of_range("FrontError: vector is empty");
//    }
//    return data_[0];
//}
//
//template <typename T>
//typename vector<T>::const_reference vector<T>::back() const {
//    if (!size_) {
//        throw std::out_of_range("BackError: vector is empty");
//    }
//    return data_[size_ - 1];
//}
//
//template <typename T>
//typename vector<T>::iterator_pointer vector<T>::data() noexcept {
//    return data_;
//}
//
//template <typename T>
//typename vector<T>::iterator vector<T>::begin() {
//    return iterator(data_);
//}
//
//template <typename T>
//typename vector<T>::iterator vector<T>::end() {
//    return iterator(data_ + size_);
//}
//
//template <typename T>
//typename vector<T>::iterator vector<T>::cbegin() const{
//    return const_iterator(data_);
//}
//
//template <typename T>
//typename vector<T>::const_iterator vector<T>::cend() const {
//    return const_iterator(data_ + size_);
//}
//
//template <typename T>
//typename vector<T>::bool vector<T>::empty() const {
//    return size_ == 0;
//}
//
//template <typename T>
//typename vector<T>::size_type vector<T>::size() const {
//    return size_;
//}
//
//template <typename T>
//typename vector<T>::size_type vector<T>::max_size() const {
//    return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
//}
//
//template <typename T>
//void vector<T>::reserve(size_type new_capacity) {
//    if (new_capacity <= capacity_) {
//        return;
//    }
//
//    if (new_capacity > max_size()) {
//        throw std::out_of_range("ReserveError: Too large size for a new capacity");
//    }
//
//    iterator_pointer new_data = new value_type[new_capacity];
//    std::copy(data_, data_ + size_, new_data);
//    delete[] data_;
//    data_ = new_data;
//    capacity_ = new_capacity;
//}
//
//template <typename T>
//typename vector<T>::size_type vector<T>::capacity() const {
//    return capacity_;
//}
//
//template <typename T>
//void vector<T>::shrink_to_fit() {
//    if (size_ < capacity_) {
//        iterator_pointer new_data = new value_type[size_];
//        std::copy(data_, data_ + size_, new_data);
//        delete[] data_;
//        data_ = new_data;
//        capacity_ = size_;
//    }
//}
//
//template <typename T>
//void vector<T>::clear() noexcept {
//size_ = 0;
//}
//
//template <typename T>
//typename vector<T>::iterator vector<T>::insert(iterator pos,
//                                               const_reference value) {
//    size_type idx = pos - begin();
//
//    if (idx > size_) {
//        throw std::out_of_range(
//                "InsertError: The insertion position is out of range of the vector "
//                "memory");
//    }
//
//    if (size_ == capacity_) {
//        reserve(capacity_ ? capacity_ * 2 : 1);
//    }
//
//    iterator new_pos = begin() + idx;
//
//    for (iterator it = end(); it != new_pos; --it) {
//        *it = *(it - 1);
//    }
//    *new_pos = value;
//    ++size_;
//
//    return new_pos;
//}
//
//template <typename T>
//void vector<T>::erase(iterator pos) {
//    size_type position = pos - data_;
//
//    if (position > size_) {
//        throw std::out_of_range("EraseError: Index out of range");
//    }
//
//    for (iterator it = pos; it != end() - 1; ++it) {
//        *it = *(it + 1);
//    }
//    --size_;
//}
//
//template <typename T>
//void vector<T>::push_back(const_reference value) {
//    if (size_ == capacity_) {
//        reserve(capacity_ ? capacity_ * 2 : 1);
//    }
//    data_[size_++] = value;
//}
//
//template <typename T>
//void vector<T>::pop_back() {
//    if (size_ > 0) {
//        --size_;
//    }
//}
//
//template <typename T>
//void vector<T>::swap(vector<T> &other) {
//    std::swap(data_, other.data_);
//    std::swap(size_, other.size_);
//    std::swap(capacity_, other.capacity_);
//}


}  // namespace s21

#include "s21_vector.tpp"
#include "s21_vector_iterators.h"

#endif //SRC_S21_VECTOR_H
