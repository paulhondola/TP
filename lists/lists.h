#ifndef __LISTS_H
#define __LISTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;


typedef struct list {
    Node *front;
    Node *back;
} List;

List *add_front_node(List *list, int data);

List *add_back_node(List *list, int data);

void print_list(List *list);

void free_list(List *list);

#endif
