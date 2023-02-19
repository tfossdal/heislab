#pragma once
#include <stdio.h>
#include <stdlib.h>

struct LinkedList; //LinkedList implementation from hackerearth.com

typedef struct LinkedList *node;

node createNode();

node addNode(node head, int value);

void clearVal(node head, int value);

