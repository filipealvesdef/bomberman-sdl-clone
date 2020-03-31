#include "list.h"
#include <stdlib.h>

List* createList() {
    List* list = (List*) malloc(sizeof(List));

    list->size = 0;
    list->head = NULL;
    list->tail = list->head;

    return list;
}

void deleteList(List* list) {

    while (!isEmpty(list))
        pop(list);

    free(list);
}

void push(List* list, void* data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = list->head;

    list->head = node;
    list->size++;

    if (list->size == 1)
        list->tail = list->head;

    // list->tail = atPos(list, list->size - 1);
}

void pushBack(List* list, void* data) {
    if (list->size == 0)
        push(list, data);

    else {
        Node* node = (Node*) malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;

        list->tail->next = node;
        list->tail = node;
        list->size++;
    }
}

int isEmpty(List* list) {
    return (list->size == 0);
}

void* getData(List* list, int index) {
    return atPos(list, index)->data;
}

void pop(List* list) {

    if (!isEmpty(list)) {
        Node* pointer = list->head;

        list->head = pointer->next;

        free(pointer->data);
        free(pointer);

        list->size--;
    }
}
void closeList(List* list) {
    list->tail->next = list->head;
}

Node* atPos(List* list, int index) {

    if (index >= 0 && index < list->size) {
        if (index == list->size - 1)
            return list->tail;

        Node* node = list->head;

        int i;
        for (i = 0; i < index; i++)
            node = node->next;

        return node;
    }

    return NULL;
}

int indexOf(List* list, Node* node) {

    if (node != NULL) {
        Node* pointer = list->head;

        int index = 0;
        while (pointer != node && pointer != NULL) {
            pointer = pointer->next;
            index++;
        }

        if (pointer != NULL)
            return index;
    }

    return -1;
}

int indexOfData(List* list, void* data) {

    if (data != NULL) {
        Node* pointer = list->head;

        int index = 0;
        while (pointer->data != data && pointer != NULL) {
            pointer = pointer->next;
            index++;
        }

        if (pointer != NULL)
            return index;
    }

    return -1;
}

void erase(List* list, int index) {

    if (index == 0)
        pop(list);

    else {
        Node* current = atPos(list, index);

        if (current != NULL) {
            Node* previous = atPos(list, index - 1);
            previous->next = current->next;

            free(current->data);
            free(current);
            list->size--;
            list->tail = atPos(list, list->size - 1);
        }
    }
}

void insert(List* list, void* data, int index) {
    if (index == 0)
        push(list, data);

    else if (index == list->size) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;

        list->tail->next = newNode;
        list->tail = newNode;
        list->size++;
    }


    else {
        Node* current = atPos(list, index);

        if (current != NULL) {
            Node* previous = atPos(list, index - 1);

            Node* newNode = (Node*) malloc(sizeof(Node));
            newNode->data = data;

            previous->next = newNode;
            newNode->next = current;
            list->size++;
        }
    }
}

void xchgNodes(List* list, Node* nodeA, Node* nodeB) {

    if (nodeA == nodeB)
        return;

    int indexA = indexOf(list, nodeA);
    int indexB = indexOf(list, nodeB);

    if (indexA == -1 || indexB == -1)
        return;

    if (indexA > indexB) {
        nodeA = nodeB;
        nodeB = atPos(list, indexA);

        indexA = indexB;
        indexB = indexOf(list, nodeB);
    }

    Node* pb = atPos(list, indexB - 1);

    if (nodeA == list->head) {
        list->head = nodeB;
    }

    else {
        Node* pa = atPos(list, indexA - 1);
        pa->next = nodeB;
    }

    pb->next = nodeA;

    Node* pointer = nodeA->next;
    nodeA->next = nodeB->next;
    nodeB->next = pointer;
}

Node* min(List* list, int index) {
    Node* pointer = atPos(list, index);

    if (pointer != NULL) {
        Node* minNode = pointer;

        while (pointer != NULL) {
            if (pointer->id < minNode->id)
                minNode = pointer;

            pointer = pointer->next;
        }

        return minNode;
    }

    return NULL;
}

Node* max(List* list, int index) {
    Node* pointer = atPos(list, index);

    if (pointer != NULL) {
        Node* maxNode = pointer;

        while (pointer != NULL) {
            if (pointer->id > maxNode->id)
                maxNode = pointer;

            pointer = pointer->next;
        }

        return maxNode;
    }

    return NULL;
}

void incSort(List* list) {
    int i;

    for (i = 0; i < list->size - 1; i++)
        xchgNodes(list, atPos(list, i), min(list, i));
}

void decSort(List* list) {
    int i;

    for (i = 0; i < list->size - 1; i++)
        xchgNodes(list, atPos(list, i), max(list, i));
}
