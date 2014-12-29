//
//  HashChaining.c
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#include "HashChaining.h"
#include "LinkedList.h"

#define MAX_HORIZANTAL_CACHE_SIZE 10

HashTable* CreateHashTable(int TableSize){
    HashTable* HashTableInstance = (HashTable*)malloc(sizeof(HashTable));
    HashTableInstance->linkedListsIntheTable = (List*)malloc(sizeof(Node)*TableSize);
    
    memset(HashTableInstance->linkedListsIntheTable,0 ,sizeof(List) * TableSize);
    
    HashTableInstance->TableSize = TableSize;
    
    return HashTableInstance;
}

/*void AppendNodeIntoAHashTable(HashTable* HashTB, Node* newNode){
 int GeneratedHashAddress = CHT_HashForInteger(newNode->key, HashTB->TableSize);
 
 if(HashTB->linkedListsIntheTable[GeneratedHashAddress] == NULL){
 HashTB->linkedListsIntheTable[GeneratedHashAddress] = newNode;
 } else {
 Node* tail = HashTB->linkedListsIntheTable[GeneratedHashAddress];
 while(tail->nextNode != NULL)
 tail = tail->nextNode;
 
 tail->nextNode = newNode;
 //The current tail node is pointed by the preNode of the new node.
 newNode->prevNode = tail;
 
 }
 }*/

void AppendNodeIntoAHashTable(HashTable* HashTB, Node* newNode){
    
    int GeneratedHashAddress = CHT_HashForInteger(newNode->key, HashTB->TableSize);
    
    if(HashTB->linkedListsIntheTable[GeneratedHashAddress] == NULL){
        HashTB->linkedListsIntheTable[GeneratedHashAddress] = newNode;
        (HashTB->linkedListsIntheTable[GeneratedHashAddress])->nextNode = (HashTB->linkedListsIntheTable[GeneratedHashAddress]);
        (HashTB->linkedListsIntheTable[GeneratedHashAddress])->prevNode = (HashTB->linkedListsIntheTable[GeneratedHashAddress]);
    } else {
        Node* tail = (HashTB->linkedListsIntheTable[GeneratedHashAddress])->prevNode;
        
        tail->nextNode->prevNode = newNode;
        tail->nextNode = newNode;
        
        newNode->nextNode=(HashTB->linkedListsIntheTable[GeneratedHashAddress]);
        newNode->prevNode=tail;
        
        
    }
}


ElementType RetriveAHashValue(HashTable* HT, ElementType Key){
    int Address = CHT_HashForInteger(Key, HT->TableSize);
    List myList = HT->linkedListsIntheTable[Address];
    
    List Target = NULL;
    List Head = myList;
    
    
    
    if(myList == NULL)
        return NULL;
    
    while(1) {
        if(myList->key == Key){
            Target = myList;
            break;
        }else{
            myList = myList->nextNode;}
        
        if(Head == myList){
            return 0;
            break;
        }
        
        
    }
    
    return Target->value;
}


ElementType GetValueFromHashTable(HashTable* HashTB, ElementType Key){
    int hashedKeySoAddress = CHT_HashForInteger(Key, HashTB->TableSize);
    List theList = HashTB->linkedListsIntheTable[hashedKeySoAddress];
    
    
    
    if(theList == NULL)
        return -1; //-1 is returned when there is no value
    ElementType result = LookUpFunctionForValue(theList, Key);
    int indexForTheResult = LookUpFunctionForIndexNum(theList, Key);
    
    /*if(result == 0){
     Node* newNode = CreateNode(Key, Key);
     AppendNode(&theList, newNode);
     
     if(GetNodeCount(theList)>MAX_HORIZANTAL_CACHE_SIZE){
     Node* theLastNodeToRemove = GetNodeAt(theList, 0);
     RemoveNode(&theList, theLastNodeToRemove);
     
     DestroyNode(theLastNodeToRemove);
     }
     
     
     } else {
     RemoveNode(&theList, GetNodeAt(theList, indexForTheResult));
     
     Node* newNode = CreateNode(Key, Key);
     AppendNode(&theList, newNode);
     }*/
    
    
    HashTB->linkedListsIntheTable[hashedKeySoAddress] = LRUOperationForAsingleBuffer(theList, Key, result, indexForTheResult, MAX_HORIZANTAL_CACHE_SIZE);
    
    return result;
    
}

List GetAHorizontalSetofListData(HashTable* HashTB, ElementType Key){
    int hashedKeySoAddress = CHT_HashForInteger(Key, HashTB->TableSize);
    List theList = HashTB->linkedListsIntheTable[hashedKeySoAddress];
    
    return theList;
}



void DestroyHashTable(HashTable* HashTB){
    for(int i = 0; i<HashTB->TableSize; i++){
        List L = HashTB->linkedListsIntheTable[i];
        
        DestroyNode(L);
    }
    free(HashTB->linkedListsIntheTable);
    free(HashTB);
    
}


int CHT_HashForInteger(ElementType Key, int TableSize){
    
    
    int HashValue = 0;
    
    HashValue = Key;
    
    HashValue = HashValue % TableSize;
    
    return HashValue;
}


void DeleteANodeFromtheHash(HashTable* HashTB, ElementType Key){
    int indicator = 0; //0 means nothing to delete.
    int hashedKeySoAddress = CHT_HashForInteger(Key, HashTB->TableSize);
    List theList = (HashTB)->linkedListsIntheTable[hashedKeySoAddress];
    
    if(theList == NULL)
        printf("There is no value having been found!");
    
    
    indicator = HashLRUNodeRemovalOperation(&theList, Key);
    if(Key == theList->value){
        theList = NULL;
    }
    (HashTB)->linkedListsIntheTable[hashedKeySoAddress] = theList;
    
    
    
}

ElementType hashNodeCounter(HashTable* HashTB, int TableSize){
    int counter = 0;
    
    for(int i = 0; i<TableSize; i++){
        List theList = HashTB->linkedListsIntheTable[i];
        counter += GetNodeCount(theList);
    }
    return counter;
}


