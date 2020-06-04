//
// Created by Platon on 5/3/2020.
//

#ifndef SPR_LIST_H
#define SPR_LIST_H
#include <stdio.h>

typedef struct Node
{
    void * data;
    const struct Node * next;
}Node;

void* queue(Node** head, Node** last, void* data);
void* stack(Node** head, void* data);
void print(const Node* head);
const wchar_t * additivePrint(const Node * head);
void printToSocket(const Node * head, int connfd);
size_t len(const Node* head);
void* del(Node** head, void* data, size_t pos);
void* del1st(Node** head);

#endif //SPR_LIST_H
