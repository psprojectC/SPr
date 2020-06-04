//
// Created by Platon on 5/3/2020.
//

#include "list.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <unistd.h>
#include "change.h"

void *queue(Node **head, Node **last, void *data)
{
    Node* temp = malloc(sizeof(Node));
    if (temp == NULL) return NULL;
    memcpy(&temp->data, &data, sizeof temp->data);
    if (*last) (*last)->next = temp, (*last) = temp;
    else *head = *last = temp;
    temp->next = NULL;
    return temp;
}

void *stack(Node **head, void *data)
{
    Node* temp = malloc(sizeof(Node));
    if (!temp) return NULL;
    memcpy(&temp->data, &data, sizeof temp->data);
    temp->next = *head;
    *head = temp;
    return temp;
}

void print(const Node *head)
{
    while(head)
    {
        const Change * item = (const Change *) head->data;
        wprintf((const wchar_t *) L"{%ls, %p}\n", item->pToString(head->data), head->next);
        head = head->next;
    }
}

size_t len(const Node *head)
{
    size_t len = 0;
    while(head) ++len, head = head -> next;
    return len;
}

void *del1st(Node ** head)
{
    assert(head), assert(*head);
    void* data = (*head)->data;
    Node* toBeDeleted = *head;
    *head = (*head)->next;
    free(toBeDeleted);
    return data;
}

void printToSocket(const Node *head, int connfd)
{
    while(head)
    {
        const Change * item = (const Change *) head->data;
        write(connfd, item->pToString(head->data), wcslen(item->pToString(head->data)));
    }
    write(connfd, "end", 3);
}

const wchar_t *additivePrint(const Node *head)
{
    wchar_t * tbr = malloc(sizeof(wchar_t[500]));
    while(head)
    {
        const Change * item = (const Change *) head->data;
        wchar_t str[50];
        swprintf(str, 50, L"%ls\n", item->pToString(head->data));
        wcscat(tbr, str);
        head = head->next;
    }
    return tbr;
}

