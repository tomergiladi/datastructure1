#include <iostream>
#include <memory>
#ifndef LIST_H_
#define LIST_H_
namespace List {
    using std::cout;
    using std::endl;
    using std::shared_ptr;
    using std::weak_ptr;
    template <class T,class U>
    struct Node :public std::enable_shared_from_this<Node<T,U>> {

        T key;
        U value;
        shared_ptr<Node> next;
        weak_ptr<Node> prev;

        explicit Node(const T& key,const U& value,shared_ptr<Node> next) :key(key), value(value),next(next) {
        }

        shared_ptr<Node> getNext(){
            return this->next;
        }

        ~Node() {
            //cout << "deleting node with value:" << this->value << endl;
        }
    };

    template <class T,class U>
    class ListDict {
        int size;
    public:
        shared_ptr<Node<T,U>> head;


        ListDict() : size(0) {
        }
        U find(const T& key){
            shared_ptr<Node<T,U>> ptr =this->head;
            while (ptr && ptr->key != key){
                ptr=ptr->next;
            }
            if(ptr)
                return ptr->value;
            else {
                throw std::exception();
            }
        }
        shared_ptr<Node<T,U>> insert(const T& key,const U& value){
            auto node= shared_ptr<Node<T,U>>(new Node<T,U>(key,value, this->head));
            if(this->head){
                this->head->prev = node;
            }
            this->head=node;
            size++;
            return this->head;
        }
        void deleteByNode(shared_ptr<Node<T,U>> node){
            if(node == this->head){
                this->head=node->next;
            }
            else{
                node->prev.lock()->next=node->next;
                if(node->next) {
                    node->next->prev = node->prev.lock();
                }
            }
            size--;
        }
        void deleteByKey(const T& key){
            shared_ptr<Node<T,U>> ptr =this->head;
            while (ptr && ptr->key != key){
                ptr=ptr->next;
            }
            if(ptr)
                this->deleteByNode(ptr);
            else {
                throw std::exception();
            }
        }
        shared_ptr<Node<T,U>> getFirst(){
            return this->head;
        }
        int getSize(){
            return this->size;
        }
    };
}
#endif