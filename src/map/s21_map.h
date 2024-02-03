#ifndef SRC_S21_MAP_H
#define SRC_S21_MAP_H

#include "../AVLTree/BinaryTree.h"

namespace s21 {
    template <typename Key, typename T>
    class map : public BinaryTree<Key, T> {
    public:
        class MapIterator;
        class ConstMapIterator;

        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = MapIterator;
        using const_iterator = ConstMapIterator;
        using size_type = size_t;

        map() : BinaryTree<Key, T>(){};
        map(std::initializer_list<value_type> const &items);
        map(const map &other) : BinaryTree<Key, T>(other){};
        map(map &&other) noexcept : BinaryTree<Key, T>(std::move(other)){};
        map &operator=(map &&other) noexcept;
        map &operator=(const map &other);
        ~map() = default;

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;
        void merge(map &other);
        // TODO: contains доделать (DONE)
        bool contains(const Key& key); // checks if there is an element with key equivalent to key in the container

        class MapIterator : public BinaryTree<Key, T>::Iterator {
        public:
            friend class map;
            MapIterator() : BinaryTree<Key, T>::Iterator(){};
            MapIterator(typename BinaryTree<Key, T>::Node *node,
                        typename BinaryTree<Key, T>::Node *past_node = nullptr)
                        : BinaryTree<Key, T>::Iterator(node, past_node = nullptr) {};
            value_type operator*();

        protected:
            T &return_value();
        };

        class ConstMapIterator : public MapIterator {
        public:
            friend class map;
            ConstMapIterator() : MapIterator() {};
            ConstMapIterator(typename BinaryTree<Key, T>::Node *node,
                             typename BinaryTree<Key, T>::Node *past_node = nullptr)
                    : MapIterator(node, past_node = nullptr) {};
            const_reference operator*() const { return MapIterator::operator*(); };
        };

        T &at(const Key &key);
        T &operator[](const Key &key);
        // inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place
        std::pair<iterator, bool> insert(const value_type &value);
        // inserts value by key and returns iterator to where the element is in the container and bool denoting whether the insertion took place
        std::pair<iterator, bool> insert(const Key &key, const T &obj);
        // inserts an element or assigns to the current element if the key already exists
        std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
        template <class... Args>
        std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
        void erase(iterator pos);

    private:
        iterator find(const Key &key);
    };

    template <typename Key, typename T>
    map<Key, T>::map(const std::initializer_list<value_type> &items) {
        for (auto i = items.begin(); i != items.end(); ++i) {
            insert(*i);
        }
    }

    template <typename Key, typename T>
    map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
        if (this != &other) {
            BinaryTree<Key, T>::operator=(std::move(other));
        }
        return *this;
    }

    template <typename Key, typename T>
    map<Key, T> &map<Key, T>::operator=(const map &other) {
        if (this != &other) {
            BinaryTree<Key, T>::operator=(other);
        }
        return *this;
    }

    template <typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(const value_type &value) {
        return insert(value.first, value.second);
    }

    template <typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(const Key &key, const T &obj) {
        std::pair<iterator, bool> return_value;
        if (BinaryTree<Key, T>::root_ == nullptr) {
            BinaryTree<Key, T>::root_ = new typename BinaryTree<Key, T>::Node(key, obj);
            return_value.first = iterator(BinaryTree<Key, T>::root_);
            return_value.second = true;
        } else {
            bool check_insert = BinaryTree<Key, T>::RecursiveInsert(BinaryTree<Key, T>::root_, key, obj);
            return_value.first = find(key);
            return_value.second = check_insert;
        }
        return return_value;
    }

    template <typename Key, typename T>
//    typename map<Key, T>::MapIterator::operator*() const {
    typename map<Key, T>::value_type map<Key, T>::MapIterator::operator*() {
        if (BinaryTree<Key, T>::Iterator::it_node_ == nullptr) {
            static value_type not_true_value{};
            return not_true_value;
        }
        std::pair<const key_type, mapped_type> pr =
                std::make_pair(BinaryTree<Key, T>::Iterator::it_node_->key_,
                               BinaryTree<Key, T>::Iterator::it_node_->value_);
        std::pair<const key_type, mapped_type> ref = pr;

        return ref;
    }

    template <typename Key, typename T>
    T &map<Key, T>::MapIterator::return_value() {
        if (BinaryTree<Key, T>::Iterator::it_node_ == nullptr) {
            static T not_true_value{};
            return not_true_value;
        }
        return BinaryTree<Key, T>::Iterator::it_node_->value_;
    }

    template <typename Key, typename T>
    typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
        typename BinaryTree<Key, T>::Node *node =
                BinaryTree<Key, T>::RecursiveFind(BinaryTree<Key, T>::root_, key);
        return iterator(node);
    }

    template <typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
            const Key &key, const T &obj) {
        auto it = find(key);
        if (it != this->end()) {
            erase(it);
            auto pr = insert(key, obj);
            pr.second = false;
            return pr;
        }
        return insert(key, obj);
    }

    template <typename Key, typename T>
    template <class... Args>
    std::vector<std::pair<typename map<Key, T>::iterator, bool>>
    map<Key, T>::insert_many(Args &&...args) {
        std::vector<std::pair<typename map<Key, T>::iterator, bool>> vec;
        for (const auto &arg : {args...}) {
            vec.push_back(insert(arg));
        }
        return vec;
    }

    template <typename Key, typename T>
    T &map<Key, T>::at(const Key &key) {
        auto it = find(key);
        if (it == this->end()) {
            throw std::out_of_range("Container does not have an element with the specified key");
        }
        return it.return_value();
    }

    template <typename Key, typename T>
    T &map<Key, T>::operator[](const Key &key) {
        auto it = find(key);
        if (it == this->end()) {
            auto pr = insert(std::make_pair(key, T()));
            it = pr.first;
        }
        return it.return_value();
    }

    template <typename Key, typename T>
    typename map<Key, T>::iterator map<Key, T>::begin() {
        return map<Key, T>::MapIterator(
                BinaryTree<Key, T>::GetMin(BinaryTree<Key, T>::root_));
    }

    template <typename Key, typename T>
    typename map<Key, T>::iterator map<Key, T>::end() {
        if (BinaryTree<Key, T>::root_ == nullptr) return begin();

        typename BinaryTree<Key, T>::Node *last_node =
                BinaryTree<Key, T>::GetMax(BinaryTree<Key, T>::root_);
        MapIterator test(nullptr, last_node);
        return test;
    }

    template <typename Key, typename T>
    typename map<Key, T>::const_iterator map<Key, T>::cbegin() const {
        return map<Key, T>::ConstMapIterator(
                BinaryTree<Key, T>::GetMin(BinaryTree<Key, T>::root_));
    }

    template <typename Key, typename T>
    typename map<Key, T>::const_iterator map<Key, T>::cend() const {
        if (BinaryTree<Key, T>::root_ == nullptr) return cbegin();

        typename BinaryTree<Key, T>::Node *last_node =
                BinaryTree<Key, T>::GetMax(BinaryTree<Key, T>::root_);
        ConstMapIterator test(nullptr, last_node);
        return test;
    }

    template <typename Key, typename T>
    void map<Key, T>::merge(map &other) {
        map const_tree(other);
        iterator const_it = const_tree.begin();
        for (; const_it != const_tree.end(); ++const_it) {
            auto key = (*const_it).first;
            auto obj = (*const_it).second;
            std::pair<iterator, bool> pr = insert(key, obj);
            if (pr.second) other.erase(pr.first);
        }
    }

    template <typename Key, typename T>
    bool map<Key, T>::contains(const Key &key) {
        bool contains_res = false;
        auto it = find(key);
        if (it != this->end()) {
            contains_res = true;
        }
        return contains_res;
    }

    template <typename Key, typename T>
    void map<Key, T>::erase(map::iterator pos) {
        if (BinaryTree<Key, T>::root_ == nullptr || pos.it_node_ == nullptr) return;
        BinaryTree<Key, T>::root_ =
                BinaryTree<Key, T>::RecursiveDelete(BinaryTree<Key, T>::root_, (*pos).first);
    }

} // namespace s21


#endif //SRC_S21_MAP_H