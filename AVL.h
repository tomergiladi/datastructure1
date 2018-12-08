#ifndef AVL_H_
#define AVL_H_
#include <cstdlib>
#include <iostream>
#include <memory>
#include "dsexceptions.h"

namespace AVL {
    using std::cout;
    using std::endl;
    using std::shared_ptr;
    using std::weak_ptr;


    template <class T, class U>
    class AVLDict;

    template <class T,class U>

    struct Node : public std::enable_shared_from_this<Node<T,U>> {
    friend class AVLDict<T,U>;
    public: U value;
    private:
        shared_ptr<Node> right;
        shared_ptr<Node> left;
        weak_ptr<Node> parent;
        T key;
        int height;
        AVLDict<T,U> *tree;

        explicit Node(const T& key, const U& value, weak_ptr<Node> parent, AVLDict<T,U> *tree)
                :value(value), parent(parent), key(key),  height(0), tree(tree) {
        }

        friend std::ostream &operator<<(std::ostream &os, shared_ptr<Node> curr) {
            if (curr)
                os << "{" << curr->key << ":" << curr->value << ", " << curr->height << "} (" << curr->left << ") ("
                   << curr->right << ")";
            return os;
        }

        void setHeight() {
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

        void removeFromParent(shared_ptr<Node> replace, shared_ptr<Node> parent) {
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

        void removeFromParent(shared_ptr<Node> replace) {
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
                left->right->parent = this->shared_from_this();
            left->right = this->shared_from_this();
            this->parent = left;
            this->removeFromParent(left, parent);
            this->setHeight();
            left->setHeight();
        }

    public:
        shared_ptr<Node> getNext(){

            if (this->right) {
                auto nextNode= this->right;
                while (nextNode->left) {
                    nextNode = nextNode->left;
                }
                return nextNode;
            }
            auto nextNode = this->shared_from_this();
            while(!(nextNode->parent.expired())){
                if(nextNode==nextNode->parent.lock()->left){
                    return nextNode->parent.lock();
                }
                nextNode=nextNode->parent.lock();
            }
            return nullptr;
        }

    public:
        ~Node() {
            //cout << "deleting node with value:" << this->value << endl;
        }
    };

    template <class T, class U>
    class AVLDict {

        friend class Node<T,U>;
        int size;
        shared_ptr<Node<T,U>> head;


        static void printByOrder(shared_ptr<Node<T,U>> current) {
            if (current) {
                printByOrder(current->left);
                cout << current->key << ":" << current->value << endl;
                printByOrder(current->right);
            }
        }

        static void fixFrom(shared_ptr<Node<T,U>> current) {
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


        AVLDict() : size(0) {
        }

        auto insert(const T& key, const U& value) -> shared_ptr<Node<T,U>> {
            // insert(key, value, this->head);
            shared_ptr<Node<T,U>> parent = nullptr;
            auto *newNode = &(this->head);
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
                (*newNode).reset(new Node<T,U>(key, value, parent, this));
                size++;
                fixFrom(*newNode);
            }
            return newNode ? *newNode : nullptr;
        }

        void deleteByNode(shared_ptr<Node<T,U>> nodeToDelete) {
            this->size--;

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

        void deleteByKey(const T& key) {
            auto nodeToDelete = this->head;
            while (nodeToDelete && nodeToDelete->key != key) {
                if (nodeToDelete->key > key) {
                    nodeToDelete = nodeToDelete->left;
                } else {
                    nodeToDelete = nodeToDelete->right;
                }
            }
            if(nodeToDelete) {
                this->deleteByNode(nodeToDelete);
            }
            else{
                throw Failure();
            }
        }
        U find(const T& key){
            auto node = this->head;
            while (node && node->key != key) {
                if (node->key > key) {
                    node = node->left;
                } else {
                    node = node->right;
                }
            }
            if(node) {
                return node->value;
            }
            else {
                throw Failure();
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const AVLDict &avl) {
            return os << avl.head << endl;
        }

        int getHeight() {
            return this->head->getHeight();
        }

        int getSize() {
            return this->size;
        }

        void printByOrder() {
            printByOrder(this->head);
        }
        shared_ptr<Node<T,U>> getFirst(){
            auto node = this->head;
            if(!node) {
                return node;
            }
            while(node->left){
                node=node->left;
            }
            return node;
        }
    };
}/*
 *
int main() {
    AVLDict<int, int> t;
    t.insert(77, 77);
    srand(0);
    for (int i = 0; i < 100; i++) {
        int x = rand() % 500;
        t.insert(x, x);
    }
    auto a =t.insert(2043,205);

    t.deleteByKey(77);
    t.deleteByNode(a);
    cout << a->key << endl;
    t.printByOrder();
}
*/
#endif