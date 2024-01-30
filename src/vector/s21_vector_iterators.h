#ifndef SRC_S21_VECTOR_ITERATORS_H
#define SRC_S21_VECTOR_ITERATORS_H

#include "s21_vector.h"

namespace s21 {
// Делаем класс шаблонным
    template<typename T>
    class vector<T>::VectorIterator {
    public:
        VectorIterator() = default;
        VectorIterator(iterator_pointer ptr);

        reference operator*();
        VectorIterator operator++(int);
        VectorIterator operator--(int);
        VectorIterator& operator++();
        VectorIterator& operator--();
        bool operator==(const VectorIterator& other) const;
        bool operator!=(const VectorIterator& other) const;
        VectorIterator operator+(int n) const;
        VectorIterator operator-(int n) const;
        // ptrdiff_t - встроенный знаковый тип, который определяет разность между указателями (та же аналогия, что и для size_t)
        ptrdiff_t operator-(const VectorIterator& other) const;
    private:
        iterator_pointer ptr_; // T* ptr_
    };

    // Константные итераторы
    // Разница - константные итераторы нужны тогда, когда данные не должны меняться
    // (чтобы мы даже случайно не смогли что-то изменить в данных)
    template <typename T>
    class vector<T>::VectorConstIterator : public VectorIterator {
    public:
        VectorConstIterator() = default;
        VectorConstIterator(const_iterator_pointer ptr);

        const_reference operator*() const;
        VectorConstIterator operator++(int);
        VectorConstIterator operator--(int);
        VectorConstIterator& operator++();
        VectorConstIterator& operator--();
        bool operator==(const VectorConstIterator& other) const;
        bool operator!=(const VectorConstIterator& other) const;
        VectorConstIterator operator+(int n) const;
        VectorConstIterator operator-(int n) const;
        ptrdiff_t operator-(const VectorConstIterator& other) const;

    private:
        const_iterator_pointer ptr_;
    };

//
//    template<typename T>
//    vector<T>::VectorIterator::VectorIterator(iterator_pointer ptr) : ptr_(ptr) {}
//
//    template<typename T>
//    typename vector<T>::reference vector<T>::VectorIterator::operator*() {
//        return *ptr_;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
//        VectorIterator tmp(*this);
//        ++ptr_;
//        return tmp;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
//        VectorIterator tmp(*this);
//        --ptr_;
//        return tmp;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator++() {
//        ++ptr_;
//        return *this;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator--() {
//        --ptr_;
//        return *this;
//    }
//
//    template <typename T>
//    bool vector<T>::VectorIterator::operator==(const VectorIterator &other) const {
//        return ptr_ == other.ptr_;
//    }
//
//    template <typename T>
//    bool vector<T>::VectorIterator::operator!=(const VectorIterator &other) const {
//        return ptr_ != other.ptr_;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(int n) const {
//        VectorIterator tmp(*this);
//        for (int i = 0; i < n; i++) {
//            tmp++;
//        };
//        return tmp;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(int n) const {
//        VectorIterator tmp(*this);
//        for (int i = 0; i < n; i++) {
//            tmp--;
//        };
//        return tmp;
//    }
//
//    template <typename T>
//    ptrdiff_t vector<T>::VectorIterator::operator-(const VectorIterator &other) const {
//        return ptr_ - other.ptr_;
//    }
//
//
//    // Константные итераторы
//    template <typename T>
//    vector<T>::VectorConstIterator::VectorConstIterator(const_iterator_pointer ptr)
//            : ptr_(ptr) {}
//
//    template <typename T>
//    typename vector<T>::const_reference vector<T>::VectorConstIterator::operator*()
//    const {
//        return *ptr_;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorConstIterator
//    vector<T>::VectorConstIterator::operator++(int) {
//        VectorConstIterator tmp(*this);
//        ++ptr_;
//        return tmp;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorConstIterator vector<T>::VectorConstIterator::operator--(int) {
//        VectorConstIterator tmp(*this);
//        --ptr_;
//        return tmp;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorConstIterator & vector<T>::VectorConstIterator::operator++() {
//        ++ptr_;
//        return *this;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorConstIterator & vector<T>::VectorConstIterator::operator--() {
//        --ptr_;
//        return *this;
//    }
//
//    template <typename T>
//    bool vector<T>::VectorConstIterator::operator==(const VectorConstIterator &other) const {
//        return ptr_ == other.ptr_;
//    }
//
//    template <typename T>
//    bool vector<T>::VectorConstIterator::operator!=(const VectorConstIterator &other) const {
//        return ptr_ != other.ptr_;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorConstIterator vector<T>::VectorConstIterator::operator+(int n) const {
//        VectorConstIterator tmp(*this);
//        for (int i = 0; i < n; i++) {
//            tmp++;
//        };
//
//        return tmp;
//    }
//
//    template <typename T>
//    typename vector<T>::VectorConstIterator vector<T>::VectorConstIterator::operator-(int n) const {
//        VectorConstIterator tmp(*this);
//        for (int i = 0; i < n; i++) {
//            tmp--;
//        };
//
//        return tmp;
//    }
//
//    template <typename T>
//    ptrdiff_t vector<T>::VectorConstIterator::operator-(const VectorConstIterator &other) const {
//        return ptr_ - other.ptr_;
//    }

} // namespace s21

#include "s21_vector_iterators.tpp"

#endif //SRC_S21_VECTOR_ITERATORS_H
