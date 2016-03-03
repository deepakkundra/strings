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
#include <string.h>

#include "common_defs.h"
#include "strings_api.h"

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
    int str_input1_len = 0;
    int str_input2_len = 0;
    char* str_dest = NULL;
    
    if ( argc < MIN_INPUT_ARGS || argc > MAX_INPUT_ARGS  ) {
        return EINVAL;
    } else {
        cmd_option = atoi(argv[INPUT_FUNC_CASE]);
        if ( cmd_option <= 0 || cmd_option > MAX_CMD_OPTIONS ) return EINVAL;
        
        str_input1_len = (int)get_string_len(argv[INPUT_STR1]);
        str_input2_len = (int)get_string_len(argv[INPUT_STR2]);
        
        switch ( cmd_option ) {
            case SUBSTRING_CASE_DEFAULT_THREADS:
            case SUBSTRING_CASE_CONFIG_THREADS:
                return parallelSubstringCount(argv[INPUT_STR1], argv[INPUT_STR2]);
                break;

            /* //TODO// Future let the user decide how many threads/levels to branch at
            case SUBSTRING_CASE_CONFIG_THREADS:
                cmd_option_threads = atoi(argv[INPUT_THREADS]);
                
                if ( argc != MAX_INPUT_ARGS && (cmd_option_threads < MIN_THREADS || cmd_option_threads > MAX_THREADS) ) return EINVAL;
                
                return parallelSubstring(argv[INPUT_STR1], argv[INPUT_STR2], cmd_option_threads);
                break;
            */
            
            case STRINGCAT_CASE_DEFAULT:
                str_dest = calloc((str_input1_len + str_input2_len + 2), sizeof(char));
                memcpy(str_dest, argv[INPUT_STR1], str_input1_len);
                printf("STRINGCAT %s\n\n", (strings_strcat(str_dest, argv[INPUT_STR2], NULL, STRINGS_API_DEFAULT)));
                free(str_dest);
                break;
                
            case STRINGCAT_CASE_HEAP:
                str_dest = calloc((str_input1_len + str_input2_len + 2), sizeof(char));
                printf("STRINGCAT HEAP %s\n\n", (strings_strcat((char*)argv[INPUT_STR1], argv[INPUT_STR2], str_dest, STRINGS_API_HEAP)));
                free(str_dest);
                break;
                
            case STRINGCAT_CASE_NON_HEAP:
                //TODO//
                printf("STRINGCAT NON-HEAP %s\n", (strings_strcat((char*)argv[INPUT_STR1], argv[INPUT_STR2], NULL, STRINGS_API_NON_HEAP)));
                break;
                
            case RUN_UNIT_TEST:
                // file_name, test_case, #_of_threads
                return unit_test_main(argv[INPUT_STR1], argv[INPUT_STR2], argv[INPUT_THREADS]);
                break;
                
            default:
                printf("Command %d not recogonized", cmd_option);
                return EINVAL;
                break;
        }
    }
    
    return 0;
}