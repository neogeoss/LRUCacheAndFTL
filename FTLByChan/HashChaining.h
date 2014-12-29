//
//  HashChaining.h
//  FTLByChan
//
//  Created by In Chan Hwang on 12/17/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//
//
//  HashChaining.h
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#ifndef HashChaining_h
#define HashChaining_h

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "DataTypes.h"


void AppendNodeIntoAHashTable(HashTable* HashTB, Node* newNode);
HashTable* CreateHashTable(int TableSize);
ElementType GetValueFromHashTable(HashTable* HashTB, ElementType Key);
List GetAHorizontalSetofListData(HashTable* HashTB, ElementType Key);
void DestroyHashTable(HashTable* HashTB);
int CHT_HashForInteger(ElementType Key, int TableSize);
//void DummyDataFiller(int dataArray [], HashTable* HT, int actualLoopPeriod );
ElementType RetriveAHashValue(HashTable* HT, ElementType Key);

void DeleteANodeFromtheHash(HashTable* HashTB, ElementType Key);
ElementType hashNodeCounter(HashTable* HashTB, int TableSize);

#endif
