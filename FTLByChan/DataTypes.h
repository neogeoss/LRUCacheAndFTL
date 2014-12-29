//
//  DataTypes.h
//  FTLByChan
//
//  Created by In Chan Hwang on 12/17/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//
//
//  DataTypes.h
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#ifndef DataTypes_h
#define DataTypes_h

typedef long ElementType;

typedef struct tagNode{
    ElementType value, key;
    struct tagNode* prevNode;
    struct tagNode* nextNode;
    struct tagNode* lruNode;
} Node;

typedef Node* List;

typedef struct tagHashTable{
    int TableSize;
    List* linkedListsIntheTable;
} HashTable;

#endif
