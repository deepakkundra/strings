//
//  common_defs.h
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#include "utils.h"
#include "unit_test.h"
#include "substring.h"
#include "stringcat.h"

#ifndef common_defs_h
#define common_defs_h

// Should be defined if you want your console to be
// obliterated by logs!!!
//#define EXTENSIVE_DBG

#define MIN_INPUT_ARGS 4
#define MAX_INPUT_ARGS 5

#define INPUT_FUNC_CASE 1
#define INPUT_STR1      2
#define INPUT_STR2      3
#define INPUT_THREADS   4

#define MIN_THREADS 3
#define MAX_THREADS 4

#define MIN_MULTIPLIER 3

#define SUBSTRING_CASE_DEFAULT_THREADS 1
#define SUBSTRING_CASE_CONFIG_THREADS  2
#define STRINGCAT_CASE_STACK           3
#define STRINGCAT_CASE_HEAP            4
#define RUN_UNIT_TEST                  5
#define MAX_CMD_OPTIONS                5

#define MAX_STRING_SIZE 1024
#define MIN_STRING_SIZE 1

#endif /* common_defs_h */
