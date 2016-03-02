//
//  main.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//
//  @usage "strings FUNC_CASE STR1 STR2 OPTIONAL_MAX_THREADS"

#include <stdio.h>
#include <stdlib.h>

#include "common_defs.h"

/*!
 * @brief Main function for the strings project which provide entry
 *        point for the subString and strCat functions.
 * @param argc Number of arguments
 * @param argv Input arguments
 * @return The result of the project invocation
 * @usage "strings FUNC_CASE STR1 STR2 OPTIONAL_MAX_THREADS"
 */
int main(int argc, const char * argv[]) {
    int cmd_option = 0;
    //int cmd_option_threads = 0;
    
    if ( argc < MIN_INPUT_ARGS || argc > MAX_INPUT_ARGS  ) {
        return EINVAL;
    } else {
        cmd_option = atoi(argv[INPUT_FUNC_CASE]);
        if ( cmd_option <= 0 || cmd_option > MAX_CMD_OPTIONS ) return EINVAL;
        
        switch ( cmd_option ) {
            case SUBSTRING_CASE_DEFAULT_THREADS:
            case SUBSTRING_CASE_CONFIG_THREADS:
                return parallelSubstringCount(argv[INPUT_STR1], argv[INPUT_STR2]);
                break;

            /* //TODO// Future let the user decide how many threads
            case SUBSTRING_CASE_CONFIG_THREADS:
                cmd_option_threads = atoi(argv[INPUT_THREADS]);
                
                if ( argc != MAX_INPUT_ARGS && (cmd_option_threads < MIN_THREADS || cmd_option_threads > MAX_THREADS) ) return EINVAL;
                
                return parallelSubstring(argv[INPUT_STR1], argv[INPUT_STR2], cmd_option_threads);
                break;
            */
            
            case STRINGCAT_CASE_STACK:
                return stringcat_stack(argv[INPUT_STR1], argv[INPUT_STR2]);
                break;
                
            case STRINGCAT_CASE_HEAP:
                return stringcat_heap(argv[INPUT_STR1], argv[INPUT_STR2]);
                break;
                
            case RUN_UNIT_TEST:
                // file_name, test_case, #_of_threads
                return unit_test_main(argv[INPUT_STR1], argv[INPUT_STR2], argv[INPUT_THREADS]);
                break;
                
            default:
                return EINVAL;
                break;
        }
    }
    
    return 0;
}