#pragma once
#include <stdio.h>
#include <stdlib.h>

struct LinkedList{
    int data;
    struct LinkedList *next;
};
//LinkedList implementation from hackerearth.com

typedef struct LinkedList *node;

node createNode();

node addNode(node head, int value);

node clearVal(node head, int value);

node printQueue(node head);

node clearQueue(node head);

int getFloor(node head);

node addFloor(node head, int floor);

void removeFloor(node head, int value);