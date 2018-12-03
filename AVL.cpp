#include <stdlib.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
template <class T, class U>
class AVLDict {
    struct node : public std::enable_shared_from_this<node> {
        shared_ptr<node> right;
        shared_ptr<node> left;
        weak_ptr<node> parent;
        T key;
        U value;
        int height;
        AVLDict* tree;
        explicit node(T key, U value, weak_ptr<node> parent, AVLDict* tree)
            : parent(parent), key(key), value(value), height(0), tree(tree) {
        }
        ~node() {
            cout << "deleting node with value:" << this->value << endl;
        }
        friend std::ostream& operator<<(std::ostream& os, shared_ptr<node> curr) {
            if (curr)
                os << "{" << curr->key << ":" << curr->value << ", " << curr->height << "} (" << curr->left << ") ("
                   << curr->right << ")";
            return os;
        }
        int setHeight() {
            int left_height = this->left->getHeight();
            int right_height = this->right->getHeight();
            this->height = 1 + (left_height > right_height ? left_height : right_height);
        }
        int getHeight() {
            if (!this)
                return -1;
            return this->height;
        }
        int getBalanceFactor() {
            return this->left->getHeight() - this->right->getHeight();
        }
        void balance() {
            if (this->getBalanceFactor() > 1) {
                if (this->left->getBalanceFactor() < 0) {
                    this->left->leftRotate();
                }
                this->rightRotate();
            } else if (this->getBalanceFactor() < -1) {
                if (this->right->getBalanceFactor() > 0) {
                    this->right->rightRotate();
                }
                this->leftRotate();
            }
        }
        void leftRotate() {
            auto right = this->right;
            weak_ptr<node> parent = this->parent;
            this->right = right->left;
            if (right->left)
                right->left->parent = this->shared_from_this();
            right->left = this->shared_from_this();
            this->parent = right;
            right->parent = parent;
            if (!(parent.expired())) {
                auto sparent = parent.lock();
                if (this->shared_from_this() == sparent->right) {
                    sparent->right = right;
                } else if (this->shared_from_this() == sparent->left) {
                    sparent->left = right;
                }
            } else {
                this->tree->head = right;
            }
            this->setHeight();
            right->setHeight();
        }
        void rightRotate() {
            auto left = this->left;
            weak_ptr<node> parent = this->parent;
            this->left = left->right;
            if (left->right)
                left->right->parent = this->weak_from_this();
            left->right = this->shared_from_this();
            this->parent = left;
            left->parent = parent;
            if (!(parent.expired())) {
                auto sparent = parent.lock();
                if (this->shared_from_this() == sparent->right) {
                    sparent->right = left;
                } else if (this->shared_from_this() == sparent->left) {
                    sparent->left = left;
                }
            } else {
                this->tree->head = left;
            }
            this->setHeight();
            left->setHeight();
        }
    };
    shared_ptr<node> head;

   public:
    int size;
    AVLDict() : size(8) {
    }
    void insert(T key, U value) {
        // insert(key, value, this->head);
        shared_ptr<node> parent = nullptr;
        auto* newNode = &(this->head);
        while (*newNode) {
            parent = *newNode;
            if ((*newNode)->key > key)
                newNode = &((*newNode)->left);
            else if ((*newNode)->key < key)
                newNode = &((*newNode)->right);
            else {
                newNode = nullptr;
                break;
            }
        }
        if (newNode) {
            (*newNode).reset(new node(key, value, parent, this));
            size++;
            auto current = *newNode;
            while (current) {
                if (current->getBalanceFactor() > 1 || current->getBalanceFactor() < -1) {
                    current->balance();
                } else {
                    current->setHeight();
                }
                current = current->parent.lock();
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const AVLDict& avl) {
        return os << avl.head << endl;
    }
    int getHeight() {
        return this->head->getHeight();
    }
};
int main() {
    AVLDict<int, int> t;
    srand(0);
    for (int i = 0; i < 1000000; i++) {
        int x = rand();
        t.insert(i, i);
        cout << t.getHeight() << "," << i << "," << t.size << endl;
    }
}
