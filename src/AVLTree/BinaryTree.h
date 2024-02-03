#ifndef SRC_BINARYTREE_H
#define SRC_BINARYTREE_H

#include <iostream>
#include <sys/sysctl.h>
#include <sys/types.h>

namespace s21 {
    template<typename Key, typename Value>
    class BinaryTree {
    protected:
        struct Node;
    public:
        class Iterator;
        class ConstIterator;

        using key_type = Key;
        using value_type = Value;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        using size_type = size_t;

        class Iterator {
        public:
            friend class BinaryTree<Key, Value>;

            Iterator();
            Iterator(Node* node, Node* prev_node);

            reference operator*() const; // returns node key (key value)
            Iterator &operator++();
            Iterator operator++(int);
            Iterator &operator--();
            Iterator operator--(int);
            bool operator==(const Iterator &other);
            bool operator!=(const Iterator &other);

        protected:
            Node* it_node_;
            Node* it_prev_node_;
            Node *MoveForward(Node *node);
            Node *MoveBack(Node *node);
        };

        class ConstIterator : public Iterator {
        public:
            ConstIterator() : Iterator() {};
//            ConstIterator(Node* node, Node* prev_node) : Iterator(Node* node, Node* prev_node) {};
            const_reference operator*() const { return Iterator::operator*(); };
        };

        BinaryTree(); // default constructor
        BinaryTree(const BinaryTree &other); // copy constructor
        BinaryTree(BinaryTree &&other) noexcept; // move constructor
        ~BinaryTree(); // destructor
        BinaryTree &operator=(const BinaryTree &other);
        BinaryTree &operator=(BinaryTree &&other) noexcept;

        iterator begin();
        iterator end();

        void clear(); // clears the tree contents
        bool empty(); // checks whether the container is empty
        size_type size(); // returns the number of elements
        size_type max_size(); // returns the maximum possible number of elements
        std::pair<iterator, bool> insert(const key_type &key); // inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place
        void erase(iterator pos); // erases element at pos
        void swap(BinaryTree &other); // swaps the contents
        void merge(BinaryTree &other); // splices nodes from another container
        bool contains(const Key &key);

    protected:
        iterator Find(const Key &key);
        struct Node {
            Node(key_type key, value_type value);
            Node(key_type key, value_type value, Node* parent);
            key_type key_;
            value_type value_;
            Node* left_ = nullptr;
            Node* right_ = nullptr;
            Node* parent_ = nullptr;
            int height_ = 0;
            int size_ = 0;
            friend class BinaryTree<Key, Value>;
    };
        Node * root_;

        // copy and delete tree
//        Node* CopyTree(const Node &node, const Node &parent);
        Node *CopyTree(Node *node, Node *parent);
        void FreeTree(Node *node);

        static Node *GetMin(Node *node);
        static Node *GetMax(Node *node);

        Node *RecursiveFind(Node *node, const Key &key);
        bool RecursiveInsert(Node *node, const Key &key, Value value);
        Node *RecursiveDelete(Node *node, Key key);
        size_t RecursiveSize(Node *node);

    };

    // Node constructors
    template<typename Key, typename Value>
    BinaryTree<Key, Value>::Node::Node(key_type key, value_type value) : key_(key), value_(value) {}

    template<typename Key, typename Value>
    BinaryTree<Key, Value>::Node::Node(key_type key, value_type value, BinaryTree::Node *parent) :
    key_(key), value_(value), parent_(parent) {}

    // Map Iterator Constructors and functions
    template<typename Key, typename Value>
    BinaryTree<Key, Value>::Iterator::Iterator() : it_node_(nullptr), it_prev_node_(nullptr) {}

    template<typename Key, typename Value>
    BinaryTree<Key, Value>::Iterator::Iterator(BinaryTree::Node *node, BinaryTree::Node *prev_node) : it_node_(node), it_prev_node_(prev_node) {}

    template<typename Key, typename Value>
    Value &BinaryTree<Key, Value>::Iterator::operator*() const {
        if (it_node_ == nullptr) {
            static Value not_true_value{};
            return not_true_value;
        }
        return it_node_->key_; // TODO: перепроверить, точно ли нужно возвращать key, а не значение value
    }

    // TODO: как итерироваться по бинарному дереву?
    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Iterator &BinaryTree<Key, Value>::Iterator::operator++() {
        // ++it
        Node *tmp;
        if (it_node_ != nullptr) {
            tmp = GetMax(it_node_);
        }
        it_node_ = MoveForward(it_node_);
        if (it_node_ == nullptr) {
            it_prev_node_ = tmp;
        }
        return *this;
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Iterator BinaryTree<Key, Value>::Iterator::operator++(int) {
        // it++
        Iterator tmp = *this;
        operator++();
        return tmp;
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Iterator &BinaryTree<Key, Value>::Iterator::operator--() {
        // --it
        if (it_node_ == nullptr && it_prev_node_ != nullptr) {
            *this = it_prev_node_;
            return *this;
        }
        it_node_ = MoveBack(it_node_);
        return *this;
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Iterator BinaryTree<Key, Value>::Iterator::operator--(int) {
        // it--
        Iterator tmp = *this;
        operator--();
        return tmp;
    }

    template<typename Key, typename Value>
    bool BinaryTree<Key, Value>::Iterator::operator==(const BinaryTree::Iterator &other) {
        return it_node_ == other.it_node_;
    }

    template<typename Key, typename Value>
    bool BinaryTree<Key, Value>::Iterator::operator!=(const BinaryTree::Iterator &other) {
        return it_node_ != other.it_node_;
    }

    // Binary Tree constructors
    template<typename Key, typename Value>
    BinaryTree<Key, Value>::BinaryTree() : root_(nullptr) {}

    template<typename Key, typename Value>
    BinaryTree<Key, Value>::BinaryTree(const BinaryTree &other) {
        root_ = CopyTree(other.root_, nullptr);
    }

    template<typename Key, typename Value>
    BinaryTree<Key, Value>::BinaryTree(BinaryTree &&other) noexcept {
        this->root_ = other.root_;
        other.root_ = nullptr;
    } // TODO: нужна ли здесь рекурсия? Где вообще будем использовать конструктор перемещения?

    template<typename Key, typename Value>
    BinaryTree<Key, Value>::~BinaryTree() {
        clear();
    }

    template<typename Key, typename Value>
    BinaryTree<Key, Value> &BinaryTree<Key, Value>::operator=(const BinaryTree &other) {
        if (this != &other) {
            BinaryTree tmp(other);
            FreeTree(root_);
            *this = std::move(tmp);
        }
        return *this;
    }

    template<typename Key, typename Value>
    BinaryTree<Key, Value> &BinaryTree<Key, Value>::operator=(BinaryTree &&other) noexcept {
        if (this != &other) {
            this->root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }


    // Copy tree (recursive)
    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::CopyTree(BinaryTree::Node *node,
                                                                   BinaryTree::Node *parent) {
        if (node == nullptr) {
            return nullptr;
        }
        Node *new_node = new Node(node->key_, node->value_, parent);
        new_node->left_ = CopyTree(node->left_, new_node);
        new_node->right_ = CopyTree(node->right_, new_node);
        return new_node;
    }

    // Delete tree (recursive)
    template<typename Key, typename Value>
    void BinaryTree<Key, Value>::FreeTree(BinaryTree::Node *node) {
        if (node == nullptr) {
            return;
        }
        FreeTree(node->right_);
        FreeTree(node->left_);
        delete node;
    }

    template<typename Key, typename Value>
    void BinaryTree<Key, Value>::clear() {
        if (root_ != nullptr) {
            FreeTree(root_);
            root_ = nullptr;
        }
    }

    template<typename Key, typename Value>
    bool BinaryTree<Key, Value>::empty() {
        return root_ == nullptr;
    }

    template<typename Key, typename Value>
    size_t BinaryTree<Key, Value>::size() {
        return RecursiveSize(root_);
//        return root_->size_; // TODO: так ли нужно определять кол-во элементов?
    }

    template<typename Key, typename Value>
    size_t BinaryTree<Key, Value>::max_size() {
        return std::numeric_limits<size_type>::max() /
               sizeof(typename BinaryTree<Key, Value>::Node);
    }

    template<typename Key, typename Value>
    std::pair<typename BinaryTree<Key, Value>::Iterator, bool> BinaryTree<Key, Value>::insert(const key_type &key) {
        std::pair<Iterator, bool> return_value;
        if (root_ == nullptr) {
            root_ = new Node(key, key);
            return_value.first = Iterator(root_);
            return_value.second = true;
        } else {
            bool was_insert = RecursiveInsert(root_, key, key);
            return_value.first = Find(key);
            return_value.second = was_insert;
        }
        if (return_value.second) {
            root_->size_ = root_->size_ + 1; // TODO: переписать с префиксом ++
        }
        return return_value;
    }

    template<typename Key, typename Value>
    void BinaryTree<Key, Value>::erase(BinaryTree::Iterator pos) {
        if (root_ == nullptr || pos.it_node_ == nullptr) {
            return;
        }
        root_ = RecursiveDelete(root_, *pos);
        if (root_ != nullptr) {
            root_->size_--;
        }
    }

    template<typename Key, typename Value>
    void BinaryTree<Key, Value>::swap(BinaryTree &other) {
        std::swap(root_, other.root_);
    }

    template<typename Key, typename Value>
    void BinaryTree<Key, Value>::merge(BinaryTree &other) {
        BinaryTree other_tree(other);
        Iterator other_it = other_tree.begin();
        for (; other_it != other_tree.end(); ++other_it) {
            std::pair<Iterator, bool> pr = insert(*other_it);
            if (pr.second) other.erase(pr.first);
        }
    }

    template<typename Key, typename Value>
    bool BinaryTree<Key, Value>::contains(const Key &key) {
        Node *contain_node = RecursiveFind(root_, key);
        return contain_node != nullptr;
        // return !(contain_node == nullptr);
    }
    
template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Iterator BinaryTree<Key, Value>::begin() {
        return BinaryTree::Iterator(GetMin(root_));
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Iterator BinaryTree<Key, Value>::end() {
        if (root_ == nullptr) {
            return begin();
        }
        return BinaryTree::Iterator(GetMax(root_));
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::GetMin(BinaryTree::Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->left_ == nullptr) {
            return node;
        }
        return GetMin(node->left_);
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::GetMax(BinaryTree::Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->right_ == nullptr) {
            return node;
        }
        return GetMax(node->right_);
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::RecursiveFind(BinaryTree::Node *node,
                                                                        const Key &key) {
        if (node == nullptr || node->key_ == key) {
            return node;
        }
        if (key > node->key_) {
            return RecursiveFind(node->right_, key);
        } else {
            return RecursiveFind(node->left_, key);
        }
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Iterator BinaryTree<Key, Value>::Find(const Key &key) {
        Node *search_node = RecursiveFind(root_, key);
        return Iterator(search_node);
    }

    template<typename Key, typename Value>
    bool BinaryTree<Key, Value>::RecursiveInsert(BinaryTree::Node *node, const Key &key, Value value) {
        // Функция вернет bool значение (произошел ли insert)
        bool was_insert = false;
        if (key < node->key_) {
            if (node->left_ == nullptr) {
                node->left_ = new Node(key, value, node);
                was_insert = true;
            } else {
                was_insert = RecursiveInsert(node->left_, key, value);
            }
        } else if (key > node->key_) {
            if (node->right_ == nullptr) {
                node->right_ = new Node(key, value, node);
                was_insert = true;
            } else {
                was_insert = RecursiveInsert(node->right_, key, value);
            }
        } else if (key == node->key_) {
            return was_insert; // Вернем false, т.к. в дереве не может быть два одинаковых ключа
        }
//        SetHeight(node);
//        Balance(node);
        return was_insert;
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::RecursiveDelete(BinaryTree::Node *node, Key key) {
        if (node == nullptr) return nullptr;
        if (key < node->key_) {
            node->left_ = RecursiveDelete(node->left_, key);
        } else if (key > node->key_) {
            node->right_ = RecursiveDelete(node->right_, key);
        } else {
            if (node->left_ == nullptr || node->right_ == nullptr) {
                Node *node_right = node->right_;
                Node *node_left = node->left_;
                Node *node_parent = node->parent_;
                delete node;
                if (node_left == nullptr) {
                    node = node_right;
                } else {
                    node = node_left;
                }
                if (node != nullptr) node->parent_ = node_parent;
            } else {
                Node *min_in_right = GetMin(node->right_);
                node->key_ = min_in_right->key_;
                node->value_ = min_in_right->value_;
                node->right_ = RecursiveDelete(node->right_, min_in_right->key_);
            }
        }
        if (node != nullptr) {
//            SetHeight(node);
//            Balance(node);
        }
        return node;
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::Iterator::MoveForward(BinaryTree::Node *node) {
        if (node->right_ != nullptr) {
            return GetMin(node->right_);
        }
        Node *parent = node->parent_;
        while (parent != nullptr && node == parent->right_) {
            node = parent;
            parent = parent->parent_;
        }
        return parent;
    }

    template<typename Key, typename Value>
    typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::Iterator::MoveBack(BinaryTree::Node *node) {
        if (node->left_ != nullptr) {
            return GetMax(node->left_);
        }
        Node *parent = node->parent_;
        while (parent != nullptr && node == parent->left_) {
            node = parent;
            parent = node->parent_;
        }
        return parent;
    }

    template<typename Key, typename Value>
    size_t BinaryTree<Key, Value>::RecursiveSize(BinaryTree::Node *node) {
        if (node == nullptr) return 0;
        size_t left_size = RecursiveSize(node->left_);
        size_t right_size = RecursiveSize(node->right_);
        return 1 + left_size + right_size;
    }


} // namespace s21
#endif //SRC_BINARYTREE_H
