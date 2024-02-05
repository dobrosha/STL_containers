#ifndef SRC_S21_QUEUE_H
#define SRC_S21_QUEUE_H

#include "../deque/deque.h"

// FIFO (First-In, First-Out)

namespace s21 {
    template <typename T>
    class queue : public deque<T> {
    public:
        using value_type = T; // the template parameter T
        using reference = T&; // defines the type of the reference to an element
        using const_reference = const T&; // defines the type of the constant reference
        using size_type = size_t; // defines the type of the container size (standard type is size_t)

        queue() : deque<T>() {}; // default constructor, creates empty stack
        queue(std::initializer_list<value_type> const &items) : deque_(items) {}; // initializer list constructor, creates stack initizialized using std::initializer_list
        queue(const queue &other) : deque_(other.deque_) {}; // copy constructor
        queue(queue &&other) : deque_(std::move(other.deque_)) {}; // move constructor
        ~queue() = default; // destructor

        queue &operator=(const queue &other);
        queue &operator=(queue &&other) noexcept; // assignment operator overload for moving object

        size_type size() const; // returns the number of elements
        bool empty() const; // checks whether the container is empty

        const_reference front() const; // access the first element
        const_reference back() const; // access the last element

        void pop(); // removes the first element
        void push(const_reference value); // inserts element at the end
        void swap(queue& other); // swaps the contents

        template <class... Args>
        void insert_many_back(Args &&...args);

    private:
        deque<T> deque_;
    };


    template<typename T>
    queue<T> &queue<T>::operator=(const queue &other) {
        if (this != &other) {
            deque_ = other.deque_;
        }
        return *this;
    }

    template<typename T>
    queue<T> &queue<T>::operator=(queue &&other) noexcept {
        if (this != &other) {
            deque_ = std::move(other.deque_);
        }
        return *this;
    }

    template<typename T>
    typename queue<T>::const_reference queue<T>::front() const {
        return deque_.front();
    }

    template<typename T>
    typename queue<T>::const_reference queue<T>::back() const {
        return deque_.back();
    }

    template<typename T>
    void queue<T>::swap(queue &other) {
        std::swap(deque_, other.deque_);
    }

    template<typename T>
    void queue<T>::push(const_reference value) {
        deque_.push_back(value);
    }

    template<typename T>
    void queue<T>::pop() {
        deque_.pop_front();
    }

    template<typename T>
    bool queue<T>::empty() const {
        return deque_.empty();
    }

    template<typename T>
    typename queue<T>::size_type queue<T>::size() const {
        return deque_.size();
    }

    template <typename T>
    template <class... Args>
    void queue<T>::insert_many_back(Args&&... args) {
        for (const auto& arg : {args...}) {
            deque_.push_back(arg);
        }
    }

} // namespace s21


#endif //SRC_S21_QUEUE_H
