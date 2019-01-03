//
// Created by Tomer on 04/12/2018.
//
#include "library1.h"
#include "List.h"
#include "dsexceptions.h"
using List::ListDict;
using List::Node;
void *Init(){
    return new ListDict<int,void*>();
}
StatusType Add(void *DS, int key, void* value, void** node){
    if(DS==nullptr || node== nullptr){
        return INVALID_INPUT;
    }
    try {
        auto dict = static_cast<ListDict<int, void *> *>(DS);
        *node = dict->insert(key, value).get();
        return SUCCESS;
    }
    catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }

}
StatusType Find(void *DS, int key, void** value){
    if(DS==nullptr || value== nullptr){
        return INVALID_INPUT;
    }
    auto dict = static_cast<ListDict<int, void *> *>(DS);
    try {
        *value = dict->find(key);
        return SUCCESS;
    }
    catch (Failure& ex){
        return FAILURE;
    }
}
StatusType Delete(void *DS, int key){
    if(DS==nullptr){
        return INVALID_INPUT;
    }
    auto dict = static_cast<ListDict<int, void *> *>(DS);
    try {
        dict->deleteByKey(key);
        return SUCCESS;
    }
    catch (Failure& ex){
        return FAILURE;
    }
}
StatusType DeleteByPointer(void *DS, void* node){
    if(DS==nullptr || node== nullptr){
        return INVALID_INPUT;
    }
    auto dict = static_cast<ListDict<int, void *> *>(DS);
    dict->deleteByNode(((Node<int,void*>*)node)->shared_from_this());
    return SUCCESS;
}

StatusType Size(void *DS, int *n){
    if(DS==nullptr || n == nullptr){
        return INVALID_INPUT;
    }
    auto dict = static_cast<ListDict<int, void *> *>(DS);
    *n = dict->getSize();
    return SUCCESS;
}

void Quit(void** DS) {
    if (DS == nullptr) {
        return;
    }
    auto dict = static_cast<ListDict<int, void *> *>(*DS);
    delete dict;
    *DS= nullptr;
}