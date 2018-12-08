#include <cstdio>
#include <iostream>
#include "library1Test.h"
#include "testUtils.h"
#include "library1.h"

static void *DS = NULL;
static void *nodeP = NULL;
static void *valueP = NULL;

static void reset();

static void deleteAll();

static void add_nullDs();

static void add_nullNode();

static void add_keyAlreadyExists();

static void add_success();

static void find_nullDs();

static void find_nullValue();

static void find_keyDoesNotExist();

static void find_success();

static void delete_nullDs();

static void delete_keyDoesNotExist();

static void delete_success();

static void deleteByPointer_nullDs();

static void deleteByPointer_nullNode();

static void deleteByPointer_success();

static void size_nullDs();

static void size_nNull();

static void size_empty();

static void size_success();

static void quit_DsNull();

static void quit_hasNullAfter();

static void reset() {
    deleteAll();
    DS = Init();
}

static void deleteAll() {
    Quit(&DS);
}

Library1Test::Library1Test() {
    reset();
}

Library1Test::~Library1Test() {
    deleteAll();
}

void Library1Test::test() {
    add_nullDs();
    reset();
    add_nullNode();
    reset();
    add_keyAlreadyExists();
    reset();
    add_success();
    reset();
    find_nullDs();
    reset();
    find_nullValue();
    reset();
    find_keyDoesNotExist();
    reset();
    find_success();
    reset();
    delete_nullDs();
    reset();
    delete_keyDoesNotExist();
    reset();
    delete_success();
    reset();
    deleteByPointer_nullDs();
    reset();
    deleteByPointer_nullNode();
    reset();
    deleteByPointer_success();
    reset();
    size_nullDs();
    reset();
    size_nNull();
    reset();
    size_empty();
    reset();
    size_success();
    reset();
    quit_DsNull();
    reset();
    quit_hasNullAfter();
    reset();
    std::cout << "End Library1Test" << std::endl;
}

static void add_nullDs() {
    assertTest(Add(NULL, 0, NULL, &nodeP) == INVALID_INPUT);
}

static void add_nullNode() {
    assertTest(Add(DS, 0, NULL, NULL) == INVALID_INPUT);
}

static void add_keyAlreadyExists() {
    assertTest(Add(DS, 3, NULL, &nodeP) == SUCCESS);
    assertTest(Add(DS, 3, NULL, &nodeP) == FAILURE);
}

static void add_success() {
    assertTest(Add(DS, 0, NULL, &nodeP) == SUCCESS);
}

static void find_nullDs() {
    assertTest(Find(NULL, 0, &valueP) == INVALID_INPUT);
}

static void find_nullValue() {
    assertTest(Find(DS, 0, NULL) == INVALID_INPUT);
}

static void find_keyDoesNotExist() {
    assertTest(Find(DS, 0, &valueP) == FAILURE);
}

static void find_success() {
    int value = 8;
    Add(DS, 3, &value, &nodeP);
    assertTest(Find(DS, 3, &valueP) == SUCCESS);
    assertTest(*(int *) valueP == value);
}

static void delete_nullDs() {
    assertTest(Delete(NULL, 0) == INVALID_INPUT);
}

static void delete_keyDoesNotExist() {
    assertTest(Delete(DS, 0) == FAILURE);
}

static void delete_success() {
    assertTest(Add(DS, 0, NULL, &nodeP) == SUCCESS);
    assertTest(Find(DS, 0, &valueP) == SUCCESS);
    assertTest(Delete(DS, 0) == SUCCESS);
    assertTest(Find(DS, 0, &valueP) == FAILURE);
}

static void deleteByPointer_nullDs() {
    Add(DS, 0, NULL, &nodeP); // makes nodeP legit.
    assertTest(DeleteByPointer(NULL, nodeP) == INVALID_INPUT);
}

static void deleteByPointer_nullNode() {
    assertTest(DeleteByPointer(DS, NULL) == INVALID_INPUT);
}

static void deleteByPointer_success() {
    assertTest(Add(DS, 0, NULL, &nodeP) == SUCCESS);
    assertTest(Find(DS, 0, &valueP) == SUCCESS);
    assertTest(DeleteByPointer(DS, nodeP) == SUCCESS);
    assertTest(Find(DS, 0, &valueP) == FAILURE);
}

static void size_nullDs() {
    assertTest(Size(NULL, 0) == INVALID_INPUT);
}

static void size_nNull(){
    assertTest(Size(DS, NULL) == INVALID_INPUT);
}

static void size_empty() {
    int size;
    assertTest(Size(DS, &size) == SUCCESS);
    assertTest(size == 0);
}

static void size_success() {
    int key1 = 1;
    int key2 = 2;
    int key3 = 3;
    int key4 = 4;
    int key5 = 5;
    int key6 = 6;
    void *nodePToDelete;

    Add(DS, 1, &key1, &nodeP);
    Add(DS, 2, &key2, &nodeP);
    Add(DS, 3, &key3, &nodePToDelete);
    Add(DS, 4, &key4, &nodeP);
    Add(DS, 5, &key5, &nodeP);
    Add(DS, 6, &key6, &nodeP);

    DeleteByPointer(DS, nodePToDelete);
    Delete(DS, 5);

    int size;
    assertTest(Size(DS, &size) == SUCCESS);
    assertTest(size == 4);
}

static void quit_DsNull() {
    Quit(NULL);
}

static void quit_hasNullAfter() {
    void *newDs = Init();
    Quit(&newDs);
    assertTest(newDs == NULL);
}
/*
int main(){
    Library1Test la;
    la.test();
    auto DS = Init();
    int * a= new int[200];
    a[0]=77;
    void * node;
    Add(DS,77,a,&node);
    for (int i = 1; i < 100; i++) {
        int x = rand() % 500;
        a[i] = x;
        Add(DS,x,a+i,&node);
    }
    a[100]=2043;
    Add(DS,2043,a+100,&node);
    Delete(DS,218);
    Delete(DS,77);
    Delete(DS,495);
    DeleteByPointer(DS,node);
    return 0;
}
 */