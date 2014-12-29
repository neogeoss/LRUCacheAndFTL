//
//  main.c
//  FTLByChan
//
//  Created by In Chan Hwang on 12/17/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//
#include "ftl.h"
#include <memory.h>
#include <stdio.h>


int main(void) {
    FILE* ifp;
    char type_c;
    sector_t sectorno;
    buf_t	buffer[DATA_SIZE];
    
    
    if( !(ifp = fopen("/Users/inchanhwang/Desktop/FTLByChan/FTLByChan/w3_mixed.txt", "r")) ) {
        printf("trace file open error.\n");
        return 1;
    }
    
    ftl_open();
    
    
    // all sectors should be written sequentially before the experiment
    // you have to remove below comment
    
    
     for( sectorno = 0; sectorno < TOTAL_SECTORS; sectorno++ ) {
         *((sector_t*)buffer) = sectorno;
     
         if( ftl_write_sector(sectorno, buffer) != FTL_SUCCESS ) {
     
             return 3;
         }
     }
    
    
    while( !feof(ifp) ) {
        fscanf(ifp, "%c %u\n", &type_c, &sectorno);
        
        sectorno = sectorno % TOTAL_SECTORS;
        
        printf("%u\n", sectorno);
        
        if( type_c == 'R' ) {
            if( ftl_read_sector(sectorno, buffer) != FTL_SUCCESS ) {
                
                return 4;
            }
        }
        else if( type_c == 'W' ) {
            if( ftl_write_sector(sectorno, buffer) != FTL_SUCCESS )
                return 5;
        }
        else {
            printf("something wrong.\n");
            return 2;
        }
    }
    
    ftl_close();
    
    fclose(ifp);
    
    return 0;
}