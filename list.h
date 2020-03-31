#ifndef _list_h_
#define _list_h_

#include <stdlib.h>

typedef struct node {
    void* data;
    int id;
    struct node* next;
} Node;

typedef struct list {
    unsigned short int size;
    Node* head;
    Node* tail;
} List;

List* createList();
void deleteList(List* list);
void push(List* list, void* data);
void pushBack(List* list, void* data);
int isEmpty(List* list);
void closeList(List* list);
void* getData(List* list, int index);
void pop(List* list);
Node* atPos(List* list, int index);
int indexOf(List* list, Node* node);
int indexOfData(List* list, void* data);
void erase(List* list, int index);
void insert(List* list, void* data, int index);
void xchgNodes(List* list, Node* nodeA, Node* nodeB);
Node* min(List* list, int index);
Node* max(List* list, int index);
void incSort(List* list);
void decSort(List* list);

#endif // _list_h_
