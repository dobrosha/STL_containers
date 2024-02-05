#ifndef SRC_S21_info_H
#define SRC_S21_info_H

#include <iostream>
#include <limits>

#include "../deque/deque.h"

namespace s21 {
    template<typename T>
    class list : public deque<T> {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;

        class ListIterator {
            friend class list<T>;

        public:
            ListIterator();
            ListIterator(typename deque<T>::Node *node);
            ListIterator(typename deque<T>::Node *node,
                         typename deque<T>::Node *last_node);

            reference operator*() const;
            value_type *operator->() const;
            ListIterator &operator++();
            ListIterator operator++(int);
            ListIterator &operator--();
            ListIterator operator--(int);
            bool operator==(const ListIterator &other) const;
            bool operator!=(const ListIterator &other) const;

        protected:
            typename deque<T>::Node *node_;
            typename deque<T>::Node *last_node_;
        };

        class ListConstIterator : public ListIterator {
        public:
            ListConstIterator();
            ListConstIterator(const ListIterator &node_);
            const_reference operator*() const;
        };

        using iterator = ListIterator;
        using const_iterator = ListConstIterator;

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

        list();
        list(size_type n);
        list(std::initializer_list<value_type> const &items);
        list(const list &other);
        list(list &&other);
        ~list() = default;

        size_type max_size(); // returns the maximum possible number of elements

        void push_front(const_reference data); // adds an element to the head
        void pop_front(); // removes the first element
        void push_back(const_reference data); // adds an element to the end
        void pop_back(); // removes the last element

        iterator insert(iterator pos, const_reference value); // inserts element into concrete pos and returns the iterator that points to the new element
        void erase(iterator pos); // erases element at pos
        void splice(const_iterator pos, list &other); // transfers elements from list other starting from pos
        void merge(list &other); // merges two sorted lists
        void reverse(); // reverses the order of the elements
        void unique(); // removes consecutive duplicate elements
        void sort(); // sorts the elements

        template <class... Args>
        iterator insert_many(const_iterator pos, Args &&...args);
        template <class... Args>
        void insert_many_back(Args &&...args);
        template <class... Args>
        void insert_many_front(Args &&...args);

        list &operator=(const list &other);
        list &operator=(list &&other) noexcept;

    private:
        typename deque<T>::Node *MergeSort(typename deque<T>::Node *head);
        typename deque<T>::Node *GetMiddle(typename deque<T>::Node *head);
        typename deque<T>::Node *Merge(typename deque<T>::Node *left,
                                       typename deque<T>::Node *right);


    };


    // ------------------------------------------------------
    // .................... ListIterator ....................
    // ------------------------------------------------------
    template<typename T>
    list<T>::ListIterator::ListIterator() {};

    template<typename T>
    list<T>::ListIterator::ListIterator(typename deque<T>::Node *node) : node_(node) {}

    template<typename T>
    list<T>::ListIterator::ListIterator(typename deque<T>::Node *node,
                                        typename deque<T>::Node *last_node) : node_(node), last_node_(last_node) {}

    template<typename T>
    typename list<T>::reference list<T>::ListIterator::operator*() const {
        return node_->data;
    }

    template<typename T>
    typename list<T>::value_type* list<T>::ListIterator::operator->() const {
        return &node_->data;
    }

    template<typename T>
    typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
        // ++it
        last_node_ = node_;
        node_ = node_->next_node;
        return *this;
    }

    template<typename T>
    typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
        // it++
        ListIterator it = *this;
        this->node_ = node_->next_node;
        return it;
    }

    template<typename T>
    typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
        // --it
        if (node_ == nullptr) {
            node_ = last_node_;
        } else {
            node_ = node_->prev_node;
        }
        return *this;
    }

    template<typename T>
    typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
        // it--
        ListIterator it = *this;
        this->node_ = node_->prev_node;
        return it;
    }

    template<typename T>
    bool list<T>::ListIterator::operator==(const ListIterator& other) const {
        return node_ == other.node_;
    }

    template<typename T>
    bool list<T>::ListIterator::operator!=(const list::ListIterator &other) const {
        return node_ != other.node_;
    }

//    template<typename T>
//    bool list<T>::ListIterator::operator<(const list::ListIterator &other) const {
//        return node_ < other.node_;
//    }
//
//    template<typename T>
//    bool list<T>::ListIterator::operator<=(const list::ListIterator &other) const {
//        return node_ <= other.node_;
//    }
//
//    template<typename T>
//    bool list<T>::ListIterator::operator>(const list::ListIterator &other) const {
//        return node_ > other.node_;
//    }
//
//    template<typename T>
//    bool list<T>::ListIterator::operator>=(const list::ListIterator &other) const {
//        return node_ >= other.node_;
//    }


    // -----------------------------------------------------------
    // .................... ListConstIterator ....................
    // -----------------------------------------------------------

    template<typename T>
    list<T>::ListConstIterator::ListConstIterator() : ListIterator() {}

    template<typename T>
    list<T>::ListConstIterator::ListConstIterator(const list::ListIterator &node_) : ListIterator(node_) {}

    template<typename T>
    typename list<T>::const_reference list<T>::ListConstIterator::operator*() const {
        return ListIterator::operator*();
    }

    template<typename T>
    typename list<T>::iterator list<T>::begin() {
        return iterator(this->info_.head);
    }

    template<typename T>
    typename list<T>::iterator list<T>::end() {
//        return iterator(this->info_.tail->next_node, this->info_.tail);
        return this->info_.head ? iterator(this->info_.tail->next_node, this->info_.tail)
                                : begin();
    }

    template<typename T>
    typename list<T>::const_iterator list<T>::cbegin() const {
        return const_iterator(this->info_.head);
    }

    template<typename T>
    typename list<T>::const_iterator list<T>::cend() const {
        return const_iterator(this->info_.tail->next_node, this->info_.tail);
    }


    // -----------------------------------------------------------
    // .................... List Constructors ....................
    // -----------------------------------------------------------

    template<typename T>
    list<T>::list() : deque<T>() {}

    template<typename T>
    list<T>::list(size_type n) : list() {
        if (n > 0) {
            for (size_type i = 0; i < n; ++i) {
                push_front(value_type());
            }
        }
    }

    template<typename T>
    list<T>::list(const std::initializer_list<value_type> &items) : deque<T>(items) {}


    template<typename T>
    list<T>::list(const list &other) : deque<T>(other) {}

    template<typename T>
    list<T>::list(list &&other) : deque<T>(std::move(other)) {}

    // --------------------

    template<typename T>
    void list<T>::push_front(const_reference data) {
        deque<T>::push_front(data);
    }

    template<typename T>
    void list<T>::pop_front() {
        deque<T>::pop_front();
    }

    template<typename T>
    void list<T>::push_back(const_reference data) {
        deque<T>::push_back(data);
    }

    template<typename T>
    void list<T>::pop_back() {
        deque<T>::pop_back();
    }

    // ---------------------

    template<typename T>
    list<T> &list<T>::operator=(const list &other) {
        if (this != &other) {
            deque<T>::operator=(other);
        }
        return *this;
    }

    template<typename T>
    list<T> &list<T>::operator=(list &&other) noexcept {
        if (this != &other) {
            deque<T>::operator=(std::move(other));
        }
        return *this;
    }

    template<typename T>
    typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
        if (pos == begin()) {
            push_front(value);
            pos = this->info_.head;
        } else if (pos == this->end()) {
            push_back(value);
            pos = this->info_.tail;
        } else {
            typename deque<T>::Node *cur_node = pos.node_;
            typename deque<T>::Node *empty_node = new typename deque<T>::Node(value);
            empty_node->next_node = cur_node;
            empty_node->prev_node = cur_node->prev_node;
            cur_node->prev_node->next_node = empty_node;
            cur_node->prev_node = empty_node;
            this->info_.size++;
            return iterator(empty_node);
        }
        return pos;
    }

    template<typename T>
    void list<T>::erase(iterator pos) {
        if (pos == begin()) {
            pop_front();
        } else if (pos == this->info_.tail) {
            pop_back();
        } else {
            typename list<T>::Node *node = pos.node_;
            node->prev_node->next_node = node->next_node;
            node->next_node->prev_node = node->prev_node;
            delete node;
            this->info_.size--;
        }
    }


    template<typename T>
    typename list<T>::size_type list<T>::max_size() {
        return std::numeric_limits<size_type>::max() /
        sizeof(typename deque<T>::Node) / 2;
    }

    template<typename T>
    void list<T>::unique() {
        if (!this->empty()) {
            for (iterator it_prev = this->begin(); it_prev != this->end();) {
                iterator it_next = it_prev;
                ++it_next;
                if (it_next.node_ == nullptr) {
                    return;
                } else if (*it_prev == *it_next) {
                    erase(it_next);
                } else {
                    ++it_prev;
                }
            }
        }
    }

    template<typename T>
    void list<T>::reverse() {
        if (this->info_.size > 1) {
            typename deque<T>::Node *node = this->info_.head;
            for (size_type i = 0; i < this->info_.size; ++i) {
                std::swap(node->prev_node, node->next_node);
                node = node->prev_node;
            }
            std::swap(this->info_.head, this->info_.tail);
        }
    }

    template<typename T>
    void list<T>::splice(const_iterator pos, list &other) {
        if (!other.empty()) {
            for (iterator it = other.begin(); it != other.end(); ++it) {
                insert(pos, *it);
            }
        }
    }

    template<typename T>
    void list<T>::merge(list &other) {
        if (this != &other) {
            iterator it_this = begin();
            iterator it_other = other.begin();
            if (it_this == nullptr && it_other != nullptr) {
                splice(it_this, other);
                other.clear();
            } else {
                while (!other.empty()) {
                    if (this->empty()) {
                        insert(it_this, *it_other);
                        other.erase(it_other);
                        ++it_other;
                    } else {
                        if (it_this == end() || *it_other <= *it_this) {
                            insert(it_this, *it_other);
                            other.erase(it_other);
                            if (!other.empty()) {
                                it_other = other.begin();
                            }
                        } else {
                            ++it_this;
                        }
                    }
                }
            }
        }
    }

    template<typename T>
    typename deque<T>::Node* list<T>::Merge(typename deque<T>::Node *left, typename deque<T>::Node *right) {
        typename deque<T>::Node* result = nullptr;
        if (left == nullptr) {
            return right;
        } else if (right == nullptr) {
            return left;
        }
        if (left->data <= right->data) {
            result = left;
            result->next_node = Merge(left->next_node, right);
        } else {
            result = right;
            result->next_node = Merge(left, right->next_node);
        }
        return result;
    }

    template<typename T>
    typename deque<T>::Node *list<T>::GetMiddle(typename deque<T>::Node *head) {
        typename deque<T>::Node* slow = head;
        typename deque<T>::Node* fast = head;
        while (fast->next_node != nullptr && fast->next_node->next_node != nullptr) {
            slow = slow->next_node;
            fast = fast->next_node->next_node;
        }
        return slow;
    }

    template<typename T>
    typename deque<T>::Node *list<T>::MergeSort(typename deque<T>::Node *head) {
        if (head == nullptr || head->next_node == nullptr) {
            return head;
        }
        typename deque<T>::Node* middle = GetMiddle(head);
        typename deque<T>::Node* nextOfMiddle = middle->next_node;
        middle->next_node = nullptr;
        typename deque<T>::Node* left = MergeSort(head);
        typename deque<T>::Node* right = MergeSort(nextOfMiddle);
        return Merge(left, right);
    }

    template<typename T>
    void list<T>::sort() {
        this->info_.head = MergeSort(this->info_.head);
        this->info_.tail = this->info_.head;
        while (this->info_.tail->next_node != nullptr) {
            this->info_.tail = this->info_.tail->next_node;
        }
    }

    template<typename T>
    template <class... Args>
    typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
        for (const auto& arg : {args...}) {
            insert(pos, arg);
        }
        return pos;
    }

    template<typename T>
    template <class... Args>
    void list<T>::insert_many_back(Args&&... args) {
        for (const auto& arg : {args...}) {
            push_back(arg);
        }
    }

    template<typename T>
    template <class... Args>
    void list<T>::insert_many_front(Args&&... args) {
        for (const auto& arg : {args...}) {
            push_front(arg);
        }
    }
} // namespace s21

//#include "s21_list.tpp"

#endif //SRC_S21_info_H
