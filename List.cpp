#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
struct node {
    shared_ptr<node> next;
    weak_ptr<node> prev;
    int value;
    explicit node(int value) : value(value) {
    }
    ~node() {
        cout << "deleting node with value:" << this->value << endl;
    }
};
class List {
   public:
    shared_ptr<node> first;
    shared_ptr<node> last;

    explicit List(int value) : first(new node(value)), last() {
        cout << (last.get());
        this->last = first;
    }
    void push_front(int value) {
        shared_ptr<node> temp(new node(value));
        temp->next = this->first;
        this->first->prev = temp;
        this->first = temp;
    }
    void push_back(int value) {
        shared_ptr<node> temp(new node(value));
        temp->prev = this->last;
        this->last->next = temp;
        this->last = temp;
    }
};
