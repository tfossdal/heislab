#pragma once
#include <stdio.h>
#include <stdlib.h>

struct LinkedList; //LinkedList implementation from hackerearth.com

typedef struct LinkedList *node;

node createNode();

node addNode(node head, int value);

void clearVal(node head, int value);

void printQueue(node head);

void clearQueue(node head);

int getFloor(node head);

void addFLoor(node head);

void removeFloor(node head, int value);