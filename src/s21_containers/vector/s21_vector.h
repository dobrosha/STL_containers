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
}  // namespace s21

#include "s21_vector.tpp"
#include "s21_vector_iterators.h"

#endif //SRC_S21_VECTOR_H
