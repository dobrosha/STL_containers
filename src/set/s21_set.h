#ifndef SRC_S21_SET_H
#define SRC_S21_SET_H

#include "../AVLTree/BinaryTree.h"
#include <vector>
#include <iostream>
#include <sys/sysctl.h>
#include <sys/types.h>

// set - хранит только уникальные значения (не может быть повторов)
// в отличие от map в set-е нет "ключей" - есть только значения. По ним происходит поиск и добавление в дерево
// => для set-а ключом будет являться значение (value)

// В set-е нельзя менять значения (иначе сломается упорядоченная логика хранения в дереве)
// Альтернативное решение: удалить элемент и добавить новый

namespace s21 {
    template <typename Key>
    class set : public BinaryTree<Key, Key> {
    public:
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = typename BinaryTree<Key, Key>::Iterator;
        using const_iterator = typename BinaryTree<Key, Key>::ConstIterator;
        using size_type = size_t;

        set() : BinaryTree<Key, Key>(){};
        set(std::initializer_list<value_type> const &items);
        set(const set &other) : BinaryTree<Key, Key>(other) {};
        set(set &&other) noexcept : BinaryTree<Key, Key>(std::move(other)){};
        set &operator=(set &&other) noexcept;
        set &operator=(const set &other);
        ~set() = default;

        iterator find(const key_type &key) { return BinaryTree<Key, Key>::Find(key); };
        template <class... Args>
        std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
    };

    template <typename Key>
    set<Key>::set(const std::initializer_list<value_type> &items) {
        for (auto i = items.begin(); i != items.end(); ++i) {
            BinaryTree<Key, Key>::insert(*i);
        }
    }

    template <typename Key>
    set<Key> &set<Key>::operator=(set &&other) noexcept {
        if (this != &other) {
            BinaryTree<Key, Key>::operator=(std::move(other));
        }
        return *this;
    }

    template <typename Key>
    set<Key> &set<Key>::operator=(const set &other) {
        if (this != &other) {
            BinaryTree<Key, Key>::operator=(other);
        }
        return *this;
    }

    template <typename Key>
    template <class... Args>
    std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
            Args &&...args) {
        std::vector<std::pair<typename set<Key>::iterator, bool>> vec;
        for (const auto &arg : {args...}) {
            vec.push_back(BinaryTree<Key, Key>::insert(arg));
        }
        return vec;
    }

} // namespace s21

#endif //SRC_S21_SET_H
