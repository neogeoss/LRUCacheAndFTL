//
//  ftl.c
//  FTLByChan
//
//  Created by In Chan Hwang on 12/17/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//
#include "ftl.h"
#include <memory.h>
#include "LinkedList.h"
#include <stdlib.h>
#include <sys/queue.h>




typedef in_page_t	vcount;
typedef in_page_t   usedBCnt;

vcount usedBlockTable[NUM_BLOCKS]; // 0 for empty space, 1 for a non-empty space.

vcount	valid_count[NUM_BLOCKS];
page_t	map_table[LOGICAL_PAGES];

int  updateChecker[TOTAL_PAGES];
//it contains the information of update Status.


blk_t	empty_blk, write_blk, empty_Space_Blk;

in_page_t write_offset; // write offset in a write block

buf_t bufferGabageCollection[DATA_SIZE];

char emptyChar = 0xFF;

unsigned char* spareRead[SPARE_SIZE];
unsigned char* spareWrite[SPARE_SIZE];

int ftl_open(void) {
    
    memset(valid_count, 0x00, sizeof(valid_count));
    memset(map_table, 0xFF, sizeof(map_table));
    
    memset(usedBlockTable, 0, sizeof(usedBlockTable));
    memset(updateChecker, 0, sizeof(updateChecker));
    
    write_blk = 0;
    empty_blk = 1;
    
    write_offset = 0;
    
    if( erase_block(write_blk) )
        return FTL_ERROR;
    
    return FTL_SUCCESS;
}

int ftl_read_sector(sector_t sectorno, pbuf_t buf) {
    int physicalAddress = 0;//
    physicalAddress = map_table[sectorno];
    
    
    int offsetNo = physicalAddress % PPB;
    int blockNo = physicalAddress / PPB;
    if(read_page(blockNo, offsetNo, buf, spareRead) == FTL_SUCCESS){
        printf("FTL read was successful! \n");
    }
    
    
    return FTL_SUCCESS;
}

// this function has to be called by ftl_garbagte_collection()
// greedy policy is implemented
static int find_target_blk(void) {
    blk_t blk, min_blk;
    vcount min_vcount = PPB+1;
    
    for( blk = 0; blk < NUM_BLOCKS; blk++ ) {
        if( blk == write_blk )
            continue;
        
        /*if( blk == empty_blk )
            continue;*/
        
        if( valid_count[blk] < min_vcount ) {
            min_vcount = valid_count[blk];
            min_blk = blk;
        }
    }
    
    return min_blk;
}


/*in_page_t ftl_find_PageOffset(blk_t blockNo){
    blk_t pointerMapTableNo = blockNo * PPB;
    in_page_t  writeOffset = -1;
    for(int i = 0; i<PPB; i++){
        if (updateChecker[pointerMapTableNo+i] == 0){
        
            writeOffset = i;
            updateChecker[pointerMapTableNo+i] = 2;
            break;
            
        }
    }
    return writeOffset;
}*/



static int ftl_garbage_collection(void)  {
    blk_t targetBlockNo = find_target_blk();
    if(targetBlockNo == NUM_BLOCKS){
        printf("Out of range! the function escapes..\n");
        return 0;
    }
        
    //int loopPeriod = valid_count[targetBlockNo];
    int initialPhysicalAdd = targetBlockNo*PPB;
    
    
    empty_blk = ftl_find_Empty_Block();//Block number returned?
    erase_block(empty_blk);
    write_offset = 0;
    
    if(write_blk  != -1){
        
         for(int pageOffset = 0; pageOffset<PPB; pageOffset++){
             //in_page_t pageOffset = ftl_find_PageOffset(targetBlockNo);
             if(updateChecker[initialPhysicalAdd+pageOffset] == 0){
             
                 
             read_page(targetBlockNo, pageOffset, bufferGabageCollection, spareRead);
             
             write_page(empty_blk, write_offset, bufferGabageCollection, spareWrite);
             valid_count[empty_blk]++;
             write_offset++;
             }
         }
    }
   

    //int initialPhysicalAdd = targetBlockNo*PPB;
    for(int j=0; j<PPB; j++){
        updateChecker[initialPhysicalAdd+j] = 0;
    }
    
    
    usedBlockTable[targetBlockNo] = 0;
    usedBlockTable[empty_blk] = 1;
    
    
    valid_count[targetBlockNo] = 0;
   
    erase_block(targetBlockNo);
    
    
    
    return FTL_SUCCESS;
}


int ftl_find_Empty_Block(void){
    empty_Space_Blk = (NUM_BLOCKS)-2;
    for(int i = 0; i<NUM_BLOCKS; i++){
        if(usedBlockTable[i] == 0){
            empty_Space_Blk = i;
            break;
        }
    }
    return empty_Space_Blk;
}

/*int ftl_find_Writable_Block(void){
    int writableBlock = -1;
    for(int i = 0; i < NUM_BLOCKS; i++){
        if(valid_count[i] <= PPB){
            writableBlock = i;
            break;
        }
    }
    return writableBlock;
}

int ftl_writable_Offset(vcount blockNum){
    int writable_Offset = 0;
    int usedSOfar = valid_count[blockNum];
    writable_Offset = usedSOfar+1;
    return writable_Offset;
    
}*/

int ftl_write_sector(sector_t sectorno, pbuf_t buf) {
    
    if(map_table[sectorno] == emptyChar){
        int physicalAddress = write_blk * PPB + write_offset;
        
        
        if(write_page(write_blk, write_offset, buf, spareWrite) == FTL_SUCCESS){
            printf("FTL write was successful! \n");
            valid_count[write_blk]++;
            write_offset++;
            usedBlockTable[write_blk] = 1;
            map_table[sectorno] = physicalAddress;
        }
  
    } else if (map_table[sectorno] != emptyChar) {
        
        int physicalAddress = map_table[sectorno];
        blk_t validCountSubtract = physicalAddress/PPB;
        //map_table[sectorno] = emptyChar;//어떻게 이부분의 주소 데이터를 무효화 할 것인가?
        valid_count[validCountSubtract]--;
        
        
                
        
        if(write_page(write_blk, write_offset, buf, spareWrite) == FTL_SUCCESS){
            printf("FTL write was successful! \n");
            int physicalAddress = write_blk * PPB + write_offset;
            updateChecker[map_table[sectorno]]=1;
            map_table[sectorno] = physicalAddress;
            valid_count[write_blk]++;
            usedBlockTable[write_blk] = 1;
            write_offset++;

        }
    }

    
    if(write_offset == PPB){
        
        
        if(emptyBlockCounter() < 2){
            ftl_garbage_collection();
        }
        write_blk = ftl_find_Empty_Block();
        write_offset = 0;
        
    }
    
    return FTL_SUCCESS;
}




int emptyBlockCounter(void){
    int counter = 0;
    for(int i = 0; i<NUM_BLOCKS; i++){
        if(usedBlockTable[i] == 0)
            counter++;
        
    }
    return counter;
}

int ftl_close(void) {
    
    print_exe_time();
    
    return FTL_SUCCESS;
}