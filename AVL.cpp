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
        explicit node(T key, U value, weak_ptr<node> parent) : parent(parent), key(key), value(value), height(0) {
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
        int getHeight() {
            if (!this)
                return -1;
            return this->height;
        }
        void leftRotate() {
            auto right = this->right;
            weak_ptr<node> parent = this->parent;
            this->right = right->left;
            right->left->parent = this->weak_from_this();
            right->left = this->shared_from_this();
            this->parent = right;
            right->parent = parent;
            if (!(parent.expired())) {
                auto sparent = parent.lock();
                if (this->shared_from_this() == sparent->right) {
                    sparent->right = right;
                }
                if (this->shared_from_this() == sparent->left) {
                    sparent->left = right;
                }
            }
        }
    };
    shared_ptr<node> head;
    static void insert(T key, U value, shared_ptr<node>& current, shared_ptr<node> parent = nullptr) {
        if (!current) {
            current.reset(new node(key, value, parent));
        } else {
            if (current->key > key)
                insert(key, value, current->left, current);
            if (current->key < key)
                insert(key, value, current->right, current);
        }
        int left_height = current->left->getHeight();
        int right_height = current->right->getHeight();
        current->height = 1 + (left_height > right_height ? left_height : right_height);
    }

   public:
    AVLDict() = default;
    void insert(T key, U value) {
        insert(key, value, this->head);
    }
    friend std::ostream& operator<<(std::ostream& os, const AVLDict& avl) {
        return os << avl.head << endl;
    }
    void ttt() {
        this->head->right->leftRotate();
        cout << "Fdsfsa" << this->head->right->parent.lock()->key << endl;
        cout << "Fdsfsa" << this->head->right->left->parent.lock()->key << endl;
        cout << "Fdsfsa" << this->head->right->left->right->parent.lock()->key << endl;
    }
};
int main() {
    AVLDict<int, int> t;
    t.insert(1, 1);
    t.insert(5, 5);
    t.insert(3, 3);
    t.insert(2, 2);
    t.insert(10, 10);
    t.insert(7, 7);
    cout << t;
    t.ttt();
    cout << t;
}
