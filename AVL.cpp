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
        void removeFromParent(shared_ptr<node> replace, shared_ptr<node> parent) {
            if (replace) {
                replace->parent = parent;
            }
            if (parent) {
                if (this->shared_from_this() == parent->right) {
                    parent->right = replace;
                } else if (this->shared_from_this() == parent->left) {
                    parent->left = replace;
                }
            } else {
                this->tree->head = replace;
            }
        }
        void removeFromParent(shared_ptr<node> replace) {
            this->removeFromParent(replace, this->parent.lock());
        }
        void leftRotate() {
            auto right = this->right;
            auto parent = this->parent.lock();
            this->right = right->left;
            if (right->left)
                right->left->parent = this->shared_from_this();
            right->left = this->shared_from_this();
            this->parent = right;
            this->removeFromParent(right, parent);
            this->setHeight();
            right->setHeight();
        }
        void rightRotate() {
            auto left = this->left;
            auto parent = this->parent.lock();
            this->left = left->right;
            if (left->right)
                left->right->parent = this->weak_from_this();
            left->right = this->shared_from_this();
            this->parent = left;
            left->parent = parent;
            this->removeFromParent(left, parent);
            this->setHeight();
            left->setHeight();
        }
    };
    shared_ptr<node> head;
    static void printByOrder(shared_ptr<node> current) {
        if (current) {
            printByOrder(current->left);
            cout << current->key << ":" << current->value << endl;
            printByOrder(current->right);
        }
    }
    static void fixFrom(shared_ptr<node> current) {
        while (current) {
            if (current->getBalanceFactor() > 1 || current->getBalanceFactor() < -1) {
                current->balance();
            } else {
                current->setHeight();
            }
            current = current->parent.lock();
        }
    }

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
            if ((*newNode)->key > key) {
                newNode = &((*newNode)->left);
            } else if ((*newNode)->key < key) {
                newNode = &((*newNode)->right);
            } else {
                newNode = nullptr;
                break;
            }
        }
        if (newNode) {
            (*newNode).reset(new node(key, value, parent, this));
            size++;
            fixFrom(*newNode);
        }
    }
    void deleteByKey(T key) {
        auto nodeToDelete = this->head;
        while (nodeToDelete && nodeToDelete->key != key) {
            if (nodeToDelete->key > key) {
                nodeToDelete = nodeToDelete->left;
            } else {
                nodeToDelete = nodeToDelete->right;
            }
        }
        auto fix = nodeToDelete->parent.lock();
        if (!(nodeToDelete->left) && !(nodeToDelete->right)) {
            nodeToDelete->removeFromParent(nullptr);
        } else if (!(nodeToDelete->left)) {
            nodeToDelete->removeFromParent(nodeToDelete->right);
        } else if (!(nodeToDelete->right)) {
            nodeToDelete->removeFromParent(nodeToDelete->left);
        } else if (nodeToDelete->left && nodeToDelete->right) {
            auto swapWith = nodeToDelete->right;
            while (swapWith->left) {
                swapWith = swapWith->left;
            }
            if (swapWith != nodeToDelete->right) {
                auto sr = swapWith->right;
                auto sp = swapWith->parent.lock();
                sp->left = sr;
                if (sr) {
                    sr->parent = sp;
                }
                swapWith->right = nodeToDelete->right;
                nodeToDelete->right->parent = swapWith;
                fix = swapWith->parent.lock();
            }
            swapWith->left = nodeToDelete->left;
            nodeToDelete->left->parent = swapWith;
            nodeToDelete->removeFromParent(swapWith);
        }
        fixFrom(fix);
    }
    friend std::ostream& operator<<(std::ostream& os, const AVLDict& avl) {
        return os << avl.head << endl;
    }
    int getHeight() {
        return this->head->getHeight();
    }
    void printByOrder() {
        printByOrder(this->head);
    }
};
int main() {
    AVLDict<int, int> t;
    t.insert(77, 77);
    srand(0);
    for (int i = 0; i < 100; i++) {
        int x = rand() % 500;
        t.insert(x, x);
        // cout << t.getHeight() << "," << i << "," << t.size << endl;
    }
    t.deleteByKey(77);
    t.printByOrder();
}
