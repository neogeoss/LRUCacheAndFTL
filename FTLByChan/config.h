//
//  config.h
//  FTLByChan
//
//  Created by In Chan Hwang on 12/17/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

typedef unsigned short blk_t;
typedef unsigned char in_page_t;
typedef unsigned int page_t;
typedef unsigned char* pbuf_t;
typedef unsigned char buf_t;
typedef unsigned int sector_t;

#define DATA_SIZE			512
#define SPARE_SIZE			16
#define PPB					64
#define DATA_CAPACITY		(1024*1024*32)
#define BLOCK_SIZE			(PPB*DATA_SIZE)
#define NUM_BLOCKS			(DATA_CAPACITY / BLOCK_SIZE)
#define SPARE_BLOCK_SIZE	(PPB*SPARE_SIZE)
#define TOTAL_PAGES			(DATA_CAPACITY / DATA_SIZE)