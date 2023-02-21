#include "Queue.h"

struct LinkedList
{
    int data;
    struct LinkedList *next;
};

node createNode(){
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    temp->next = NULL;
    return temp;
}

node addNode(node head, int value){
    node temp, p;
    temp = createNode();
    temp->data = value;
    if(head == NULL){
        head = temp;
    }
    else{
        p = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}

void clearVal(node head, int value){
    node temp, p;
    p = head;
    while (p->next != NULL){
        if (p->next->data == value){
            temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        else{
            p = p->next;
        }
    }
    // Legg inn til å fjerne bakerst også
    return;
}

void printQueue(node head){
    node p;
    while(1){
        if (p == NULL)
        {
            return;
        }
        printf(p->data);
        p = p->next;
    }
}

void clearQueue(node head){
    node temp, p;
    p = head;
    while(p->next != NULL){
        temp = p->next;
        p->next = p->next->next;
        free(temp);
    }
    free(p);
    // Legg inn til å håndtere bakerst
    // og kanskje tilbake til NULL
    return;
}