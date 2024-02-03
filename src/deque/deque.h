#ifndef SRC_DEQUE_H
#define SRC_DEQUE_H

#include <iostream>

namespace s21 {
    template<typename T>
    // Реализация двусвязного списка / двустронней очереди (double-ended queue)
    class deque {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;

        deque();
        ~deque();
        deque(std::initializer_list<value_type> const &items);
        deque(const deque &other); // copy constructor
        deque(deque &&other); // move constructor

        deque &operator=(const deque &other);
        deque &operator=(deque &&other) noexcept; // assignment operator overload for moving object

        void push_back(const_reference value); // adds an element to the end
        void pop_back(); // removes the last element
        void push_front(const_reference value); // adds an element to the head
        void pop_front(); // removes the first element

        const_reference front() const; // access the first element
        const_reference back() const; // access the last element

        bool empty() const; // checks whether the container is empty
        size_type size() const; // returns the number of elements

        void swap(deque &other); // swaps the contents

        void clear(); // clears the contents

    protected:
        struct Node {
            value_type data;
            Node *next_node;
            Node *prev_node;

            Node (value_type data = value_type(), Node *next_node = nullptr, Node *prev_node = nullptr) {
                this->data = data;
                this->next_node = next_node;
                this->prev_node = prev_node;
            }
        };
        struct Nodes_info {
            size_type size = 0;
            Node *head = nullptr;
            Node *tail = nullptr;
        };

        Nodes_info info_;
    };

    template<typename T>
    deque<T>::deque() {
        info_.size = 0;
        info_.head = nullptr;
        info_.tail = nullptr;
    }

    template<typename T>
    deque<T>::deque(const std::initializer_list<value_type> &items) : deque() {
        for (auto i = items.begin(); i != items.end(); i++) push_back(*i);
    }

    template<typename T>
    deque<T>::deque(const deque &other) : deque() {
        Node *node = other.info_.head;
        while (node) {
            push_back(node->data);
            node = node->next_node;
        }
    }

    template<typename T>
    deque<T>::deque(deque &&other) {
        this->info_.size = other.info_.size;
        this->info_.head = other.info_.head;
        this->info_.tail = other.info_.tail;
        other.info_.size = 0;
        other.info_.head = nullptr;
        other.info_.tail = nullptr;
    }

    template<typename T>
    deque<T>::~deque() {
        clear();
    }

    template<typename T>
    deque<T> &deque<T>::operator=(const deque &other) {
        // a = b
        if (this != &other) {
            while (!empty()) {
                pop_front();
            }
            Node *node = other.info_.head;
            while (node) {
                push_back(node->data);
                node = node->next_node;
            }
        }
        return *this;
    }

    template<typename T>
    deque<T> &deque<T>::operator=(deque &&other) noexcept {
        if (this != &other) {
            while (!empty()) {
                pop_front();
            }
            this->info_.size = other.info_.size;
            this->info_.head = other.info_.head;
            this->info_.tail = other.info_.tail;
            other.info_.size = 0;
            other.info_.head = nullptr;
            other.info_.tail = nullptr;
        }
        return *this;
    }

    template<typename T>
    const typename deque<T>::value_type &deque<T>::front() const {
        return info_.head->data;
    }

    template<typename T>
    const typename deque<T>::value_type &deque<T>::back() const {
        return info_.tail->data;
    }

    template<typename T>
    bool deque<T>::empty() const {
        return (!info_.size);
        // return list_.head == nullptr;
    }

    template<typename T>
    typename deque<T>::size_type deque<T>::size() const {
        return info_.size;
    }

    template<typename T>
    void deque<T>::swap(deque &other) {
        std::swap(info_.size, other.info_.size);
        std::swap(info_.head, other.info_.head);
        std::swap(info_.tail, other.info_.tail);
    }

    template<typename T>
    void deque<T>::clear() {
        while (!empty()) {
            pop_front();
        }
    }

    template<typename T>
    void deque<T>::push_back(const_reference value) {
        Node *node = new Node(value);
        node->prev_node = info_.tail;
        node->next_node = nullptr;

        if (info_.tail) {
            info_.tail->next_node = node;
        }
        info_.tail = node;
        if (info_.head == nullptr) {
            info_.head = node;
        }
        ++info_.size;
    }


    template<typename T>
    void deque<T>::pop_back() {
        if (info_.tail) {
            Node *tmp = info_.tail;
            info_.tail = info_.tail->prev_node;
            if (info_.tail) {
                info_.tail->next_node = nullptr;
            } else {
                info_.head = nullptr;
            }
            delete tmp;
            --info_.size;
        }
    }

    template<typename T>
    void deque<T>::push_front(const_reference value) {
        Node *node = new Node(value);
        node->prev_node = nullptr;
        node->next_node = info_.head;
        if (info_.head) {
            info_.head->prev_node = node;
        }
        info_.head = node;
        if (info_.tail == nullptr) {
            info_.tail = node;
        }
        ++info_.size;
    }

    template<typename T>
    void deque<T>::pop_front() {
        if (info_.head) {
            Node *tmp = info_.head;
            info_.head = info_.head->next_node;
            if (info_.head) {
                info_.head->prev_node = nullptr;
            } else {
                info_.tail = nullptr;
            }
            delete tmp;
            --info_.size;
        }
    }



} // namespace s21


#endif //SRC_DEQUE_H
