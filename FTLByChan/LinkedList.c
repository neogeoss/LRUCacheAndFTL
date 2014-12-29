//
//  LinkedList.c
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#include "LinkedList.h"

Node* CreateNode(ElementType newData, ElementType newKey){
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->value = newData;
    newNode->key = newKey;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    newNode->lruNode = NULL;
    
    return newNode;
}

Node* CreateNodeLRU(ElementType newData, ElementType keyInput){
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->value = newData;
    newNode->key = keyInput;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    newNode->lruNode = NULL;
    
    return newNode;
}



void DestroyNode(Node* node){
    free(node);
}




ElementType LookUpFunctionForValue(Node* head, ElementType numInput){
    ElementType foundOrNot = 0;
    ElementType indexNum = -1;
    ElementType valueReturned = 0;
    for(ElementType i=0; i<GetNodeCount(head); i++){
        ElementType numData = GetNodeAt(head, i)->key;
        if(numInput == numData){
            indexNum = i;
            foundOrNot = 1;
            valueReturned = GetNodeAt(head,i)->value;
        }
    }
    
    return valueReturned;
    //returns a number when it is present, but returns 0 when it is not found
    
}




ElementType LookUpFunctionForIndexNum(Node* head, ElementType numInput){
    ElementType foundOrNot = 0;
    ElementType indexNum = -1;
    ElementType valueReturned = 0;
    for(ElementType i=0; i<GetNodeCount(head); i++){
        ElementType numData = GetNodeAt(head, i)->key;
        if(numInput == numData){
            indexNum = i;
            foundOrNot = 1;
            valueReturned = GetNodeAt(head,i)->value;
        }
    }
    
    return indexNum;
    //returns -1 when it is present, but returns 0 when it is not found
    
}





void RemoveNode(Node** head, Node* remove){
    //if the head is identical to the one to remove
    if(*head == remove){
        
        (*head)->prevNode->nextNode = remove->nextNode;
        (*head)->nextNode->prevNode = remove->prevNode;
        //head points to the address of the next node
        *head = remove->nextNode;
        
        //if the head still exists,
        
        
        
        remove->prevNode = NULL;
        remove->nextNode = NULL;
        
    } else {
        Node* temp = remove;
        //If the node to remove still has the previous node address
        //The previous node is connected with the next node
        remove->prevNode->nextNode = temp->nextNode;
        //if the node to remove still has the next node address
        //the next node address and the previous node address are connected together.
        remove->nextNode->prevNode = remove->prevNode;
        remove->prevNode = NULL;
        remove->nextNode = NULL;
    }
}


//Node searching
Node* GetNodeAt(Node* head, ElementType location){
    Node* current = head;
    
    while(current != NULL && (--location) >= 0){
        current = current->nextNode;
    }
    return current;
}

//Count nodes
ElementType GetNodeCount(Node* head){
    unsigned long count = 0;
    Node* current = head;
    
    while(current != NULL){
        current = current->nextNode;
        count++;
        if(current == head){
            break;
        }
    }
    return count;
}



void AppendNode(Node** Head, Node* NewNode){
    if((*Head) == NULL){
        *Head = NewNode;
        (*Head)->lruNode = *Head;
        (*Head)->prevNode = *Head;
    }
    else
    {
        Node* Tail = (*Head)->prevNode;
        
        Tail->lruNode->prevNode = NewNode;
        Tail->lruNode=NewNode;
        
        NewNode->lruNode = (*Head);
        NewNode->prevNode = Tail;
        
    }
    
}

List LRUOperationForAsingleBuffer(List thList, ElementType Key, ElementType result, ElementType indexForTheResult, ElementType MAX_HORIZANTAL_CACHE_SIZE){
    
    List newProcessedList = thList;
    if(result == 0){
        Node* newNode = CreateNode(Key, Key);
        AppendNode(&newProcessedList, newNode);
        
        if(GetNodeCount(newProcessedList)>MAX_HORIZANTAL_CACHE_SIZE){
            Node* theLastNodeToRemove = GetNodeAt(newProcessedList, 0);
            RemoveNode(&newProcessedList, theLastNodeToRemove);
            
            DestroyNode(theLastNodeToRemove);
        }
        
        
    } else {
        RemoveNode(&newProcessedList, GetNodeAt(newProcessedList, indexForTheResult));
        
        Node* newNode = CreateNode(Key, Key);
        AppendNode(&newProcessedList, newNode);
    }
    return newProcessedList;
}

/*void AppendNodeLRU(Node** Head, Node* NewNode){
 if((*Head) == NULL){
 *Head = NewNode;
 } else {
 Node* Tail = (*Head);
 while(Tail->lruNode != NULL){
 Tail = Tail->lruNode;
 }
 Tail->lruNode = NewNode;
 Tail->prevNode=NULL;
 Tail->nextNode=NULL;
 }
 
 
 
 }*/


void AppendNodeFileCircularLinkedList(Node** Head, Node* NewNode){
    if((*Head) == NULL){
        *Head = NewNode;
        (*Head)->lruNode = *Head;
        (*Head)->prevNode = *Head;
    }
    else
    {
        Node* Tail = (*Head)->prevNode;
        
        Tail->lruNode->prevNode = NewNode;
        Tail->lruNode=NewNode;
        
        NewNode->lruNode = (*Head);
        NewNode->prevNode = Tail;
        
    }
}




void AppendNodeLRU(Node** Head, Node* NewNode){
    
    if((*Head) == NULL){
        *Head = NewNode;
        (*Head)->lruNode = *Head;
        (*Head)->prevNode = *Head;
    }
    else
    {
        Node* Tail = (*Head)->prevNode;
        
        Tail->lruNode->prevNode = NewNode;
        Tail->lruNode=NewNode;
        
        NewNode->lruNode = (*Head);
        NewNode->prevNode = Tail;
        
    }
}


void RemoveNodeLRU(Node** head, Node* remove){
    if(*head == remove){
        
        (*head)->prevNode->lruNode = remove->lruNode;
        (*head)->lruNode->prevNode = remove->prevNode;
        //head points to the address of the next node
        
        
        *head = remove->lruNode;
        
        //if the head still exists,
        
        
        
        remove->prevNode = NULL;
        remove->lruNode = NULL;
        
    } else {
        Node* temp = remove;
        //If the node to remove still has the previous node address
        //The previous node is connected with the next node
        remove->prevNode->lruNode = temp->lruNode;
        //if the node to remove still has the next node address
        //the next node address and the previous node address are connected together.
        remove->lruNode->prevNode = remove->prevNode;
        remove->prevNode = NULL;
        remove->lruNode = NULL;
    }
}

Node* GetNodeAtLRU(Node* Head, ElementType Location){
    Node* Current = Head;
    while(Current != NULL && (--Location) >= 0) {
        Current = Current->lruNode;
    }
    return Current;
}


long GetNodeCountLRU(Node* Head){
    unsigned long Count = 0;
    Node* Current = Head;
    
    while(Current != NULL){
        Current = Current->lruNode;
        Count++;
        if(Current == Head)
            break;
    }
    return Count;
}

ElementType LookUpFunctionForIndexNumLRU(Node* head, ElementType numInput){
    ElementType foundOrNot = 0;
    ElementType indexNum = -1;
    ElementType valueReturned = 0;
    for(ElementType i=0; i<GetNodeCountLRU(head); i++){
        ElementType numData = GetNodeAtLRU(head, i)->key;
        if(numInput == numData){
            indexNum = i;
            foundOrNot = 1;
            valueReturned = GetNodeAtLRU(head,i)->value;
        }
    }
    
    return indexNum;
    //returns -1 when it is present, but returns 0 when it is not found
    
}


Node* inputToLRULine(Node* list, ElementType submittingNum){
    
    List newList = list;
    ElementType numToSubmit = submittingNum;
    
    //printf("a generated number moving into the cache is %d\n ", numToSubmit);
    Node* newNode = NULL;
    Node* firstNode = NULL;
    //int cacheElementCount = sizeof(numbersInCache)/sizeof(int);
    
    ElementType indexNumForOperation = LookUpFunctionForIndexNumLRU(list, numToSubmit);//returns an index number, -1 is returned when it cannot find any.
    if(indexNumForOperation == -1 ){
        
        List newNodeToLRU = CreateNodeLRU(numToSubmit, numToSubmit);
        
        firstNode = GetNodeAtLRU(list, 0);
        
        RemoveNodeLRU(&newList, firstNode);
        
        AppendNodeLRU(&newList, newNodeToLRU);
        DestroyNode(firstNode);
        DestroyNode(newNodeToLRU);
        
        
        //When the number of nodes exceeds the cache size, it deletes the very first node to maintain its maximum capacity.
        
    } else {
        
        RemoveNodeLRU(&newList, GetNodeAtLRU(list, indexNumForOperation));
        newNode = CreateNode(numToSubmit, numToSubmit);
        AppendNodeLRU(&newList, newNode);
    }
    return newList;
}

ElementType HashLRUNodeRemovalOperation(Node** thList, ElementType Key){
    //List newProcessedList = thList;
    ElementType indicator = 0; //Nothing in the Hash.
    List oneToRemove = NULL;
    ElementType nodeLength = GetNodeCount(*thList);
    for(ElementType i = 0; i<nodeLength; i++){
        if(Key == GetNodeAt(*thList, i)->key){
            oneToRemove = GetNodeAt(*thList,i);
            indicator = 1;
        }
    }
    
    RemoveNode(thList, oneToRemove);
    
    return indicator;
}
