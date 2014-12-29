//
//  LinkedList.h
//  FTLByChan
//
//  Created by In Chan Hwang on 12/17/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

//
//  LinkedList.h
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h


#include <stdio.h>
#include "HashChaining.h"
#include "DataTypes.h"

Node* CreateNode(ElementType newData, ElementType key);
void DestroyNode(Node* node);
ElementType LookUpFunctionForValue(Node* head, ElementType numInput);
ElementType LookUpFunctionForIndexNum(Node* head, ElementType numInput);
void RemoveNode(Node** head, Node* remove);
Node* GetNodeAt(Node* head, ElementType location);
long GetNodeCount(Node* head);
void AppendNode(Node** head, Node* newNode);
List LRUOperationForAsingleBuffer(List theList, ElementType Key, ElementType result, ElementType indexForTheResult, ElementType MAX_HORIZANTAL_CACHE_SIZE);
void AppendNodeLRU(Node** Head, Node* NewNode);
void RemoveNodeLRU(Node** Head, Node* Remove);
Node* GetNodeAtLRU(Node* Head, ElementType Location);
long GetNodeCountLRU(Node* Head);
void AppendNodeFileCircularLinkedList(Node** Head, Node* NewNode);

Node* inputToLRULine(Node* list, ElementType submittingNum);
Node* CreateNodeLRU(ElementType newData, ElementType keyInput);

#endif /* defined(__HashChainFileSplit__LinkedList__) */
