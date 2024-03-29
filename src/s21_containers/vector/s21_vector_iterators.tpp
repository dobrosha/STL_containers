#ifndef SRC_S21_VECTOR_ITERATORS_TPP
#define SRC_S21_VECTOR_ITERATORS_TPP

namespace s21 {
    template<typename T>
    vector<T>::VectorIterator::VectorIterator(iterator_pointer ptr) : ptr_(ptr) {}

    template<typename T>
    typename vector<T>::reference vector<T>::VectorIterator::operator*() {
        return *ptr_;
    }

    // Постфиксный vs префиксный оператор
    // Постфиксный - создается копия объекта, изменяется состояние this объекта (++ / --), НО возвращается копия объекта до изменения
    // Префиксный - изменяется состояние this объекта, он возвращается (++ / --)
    // => для увеличения быстродействия кода лучше всегда использовать префиксную форму (++it)

    // postfix it++
    template <typename T>
    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
        VectorIterator tmp(*this);
        ++ptr_;
        return tmp;
    }

    // postfix it--
    template <typename T>
    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
        VectorIterator tmp(*this);
        --ptr_;
        return tmp;
    }

    // prefix it++
    template <typename T>
    typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator++() {
        ++ptr_;
        return *this;
    }

    // prefix it--
    template <typename T>
    typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator--() {
        --ptr_;
        return *this;
    }

    template <typename T>
    bool vector<T>::VectorIterator::operator==(const VectorIterator &other) const {
        return ptr_ == other.ptr_;
    }

    template <typename T>
    bool vector<T>::VectorIterator::operator!=(const VectorIterator &other) const {
        return ptr_ != other.ptr_;
    }

    template <typename T>
    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(int n) const {
        VectorIterator tmp(*this);
        for (int i = 0; i < n; i++) {
            tmp++;
        };
        return tmp;
    }

    template <typename T>
    typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(int n) const {
        VectorIterator tmp(*this);
        for (int i = 0; i < n; i++) {
            tmp--;
        };
        return tmp;
    }

    template <typename T>
    ptrdiff_t vector<T>::VectorIterator::operator-(const VectorIterator &other) const {
        return ptr_ - other.ptr_;
    }


    // Константные итераторы
    template <typename T>
    vector<T>::VectorConstIterator::VectorConstIterator(const_iterator_pointer ptr)
            : ptr_(ptr) {}

    template <typename T>
    typename vector<T>::const_reference vector<T>::VectorConstIterator::operator*()
    const {
        return *ptr_;
    }

    template <typename T>
    typename vector<T>::VectorConstIterator
    vector<T>::VectorConstIterator::operator++(int) {
        VectorConstIterator tmp(*this);
        ++ptr_;
        return tmp;
    }

    template <typename T>
    typename vector<T>::VectorConstIterator vector<T>::VectorConstIterator::operator--(int) {
        VectorConstIterator tmp(*this);
        --ptr_;
        return tmp;
    }

    template <typename T>
    typename vector<T>::VectorConstIterator & vector<T>::VectorConstIterator::operator++() {
        ++ptr_;
        return *this;
    }

    template <typename T>
    typename vector<T>::VectorConstIterator & vector<T>::VectorConstIterator::operator--() {
        --ptr_;
        return *this;
    }

    template <typename T>
    bool vector<T>::VectorConstIterator::operator==(const VectorConstIterator &other) const {
        return ptr_ == other.ptr_;
    }

    template <typename T>
    bool vector<T>::VectorConstIterator::operator!=(const VectorConstIterator &other) const {
        return ptr_ != other.ptr_;
    }

    template <typename T>
    typename vector<T>::VectorConstIterator vector<T>::VectorConstIterator::operator+(int n) const {
        VectorConstIterator tmp(*this);
        for (int i = 0; i < n; i++) {
            tmp++;
        };

        return tmp;
    }

    template <typename T>
    typename vector<T>::VectorConstIterator vector<T>::VectorConstIterator::operator-(int n) const {
        VectorConstIterator tmp(*this);
        for (int i = 0; i < n; i++) {
            tmp--;
        };

        return tmp;
    }

    template <typename T>
    ptrdiff_t vector<T>::VectorConstIterator::operator-(const VectorConstIterator &other) const {
        return ptr_ - other.ptr_;
    }
}

#endif // SRC_S21_VECTOR_ITERATORS_TPP