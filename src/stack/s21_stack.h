#ifndef SRC_S21_STACK_H
#define SRC_S21_STACK_H

#include "../deque/deque.h"

// LIFO (Last-In, First-Out)

namespace s21 {
    template<typename T>
    class stack : public deque<T> {
    public:
        using value_type = T; // the template parameter T
        using reference = T&; // defines the type of the reference to an element
        using const_reference = const T&; // defines the type of the constant reference
        using size_type = size_t; // defines the type of the container size (standard type is size_t)

        stack() : deque<T>() {}; // default constructor, creates empty stack
        stack(std::initializer_list<value_type> const &items); // initializer list constructor, creates stack initizialized using std::initializer_list
        stack(const stack &other) : deque_(other.deque_) {}; // copy constructor
        stack(stack &&other) : deque_(std::move(other.deque_)) {}; // move constructor
        ~stack() = default; // destructor

        stack &operator=(const stack &other);
        stack &operator=(stack &&other) noexcept; // assignment operator overload for moving object

        bool empty() const; // checks whether the container is empty
        size_type size() const; // returns the number of elements
        const_reference top() const; // accesses the top element

        void push(const_reference value); // inserts element at the top
        void pop(); // removes the top element
        void swap(stack& other); // swaps the contents

        template <class... Args>
        void insert_many_front(Args &&...args);

    private:
        deque<T> deque_;
    };

    template<typename T>
    stack<T>::stack(const std::initializer_list<value_type> &items) : stack() {
        for (auto i = items.begin(); i != items.end(); i++) push(*i);
    }

    template<typename T>
    stack<T> &stack<T>::operator=(const stack &other) {
        if (this != &other) {
            deque_ = other.deque_;
        }
        return *this;
    }

    template<typename T>
    stack<T> &stack<T>::operator=(stack &&other) noexcept {
        if (this != &other) {
            deque_ = std::move(other.deque_);
        }
        return *this;
    }

    template<typename T>
    void stack<T>::push(const_reference value) {
        // Добавление элемента в начало стека
        deque_.push_front(value);
    }

    template<typename T>
    void stack<T>::pop() {
        // Выталкивание элемента из начала
        deque_.pop_front();
    }

    template<typename T>
    void stack<T>::swap(stack &other) {
         std::swap(deque_, other.deque_);
    }

    template<typename T>
    bool stack<T>::empty() const {
        return deque_.empty();
    }

    template<typename T>
    size_t stack<T>::size() const {
        return deque_.size();
    }

    template<typename T>
    const T& stack<T>::top() const {
        return deque_.front();
    }

    template<typename T>
    template <class... Args>
    void stack<T>::insert_many_front(Args&&... args) {
        for (const auto& arg : {args...}) {
            deque_.push_front(arg);
        }
    }
} // namespace s21

#endif //SRC_S21_STACK_H
