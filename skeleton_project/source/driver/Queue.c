#include "Queue.h"
#include "variables.h"

node createNode(){
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    temp->next = NULL;
    return temp;
}

node addNode(node head, int value, ButtonType btnType){
    node temp, p;
    temp = createNode();
    temp->data = value;
    temp->btnType = btnType;
    if (head == NULL)
    {
        head = temp;
    }
    else{
        p = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = temp;
    }
    printf("%d", head->data);
    return head;
}

node clearVal(node head, int value){
    node temp, p;
    p = head;
    if (p == NULL){ // avbryter om køen er tom
        printf("komme viss head e NULL");
        return head;
    }else
    printf("Eg komme hit :) \n");
    if(p->next == NULL && p->data == value){ // om det ikke er flere elementer i køen sette head til NULL
        printf("Denne komme viss next e NULL");
        temp = p;
        p = NULL;
        free(temp);
        
        return p;
    }
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
    if(head->data == value){
        temp = head;
        head = head->next;
//        free(temp);
    }
    return head;
}

node printQueue(node head){
    if(head==NULL){return head;}
    node p;
    p = head;
    printf("Kø: ");
    while (1)
    {
        if (p == NULL)
        {
            return head;        // avbryter viss tom kø
        }
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return head;
}

node clearQueue(node head){
    node temp, p;
    p = head;
    if(head == NULL){       // avbryter om kø allerede er tom
        return head;
    }
    while(p->next != NULL){     // fjerner neste element, og setter neste neste som neste
        temp = p->next;
        p->next = p->next->next;
        free(temp);
    };
    temp = p->next;     // fjerner nest siste
    free(temp);
    temp = p;
    p = NULL;           // fjerner siste
    free(temp);
    // Legg inn til å håndtere bakerst
    // og kanskje tilbake til NULL
    return p;
}

node addFloor(node head, int floor, ButtonType btnType)
{
    head = addNode(head, floor, btnType);
    return head;
}