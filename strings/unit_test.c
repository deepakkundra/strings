//
//  unit_test.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_defs.h"

/*!
 * @brief Entry point for running unit tests
 * @param str1 Test case type
 * @param str2 Test data input file
 * @return PASS or FAIL CAUSE
 * @usage file_name, test_case, #_of_threads
 */
int unit_test_main(const char* str1, const char* str2, const char* str3){
    //strings_unit_test_input
    logConsole(str1);
    logConsole(str2);
    logConsole(str3);
    
    FILE * fp = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char* token = NULL;
    char* str_input1 = NULL;
    char* str_input2 = NULL;
    
    int cmd_option_threads = atoi(str3);
    int cmd_option = atoi(str2);
    if ( cmd_option <= 0 || cmd_option >= MAX_CMD_OPTIONS ) return EINVAL;
    
    fp = fopen(str1, "r");
    if (fp == NULL) return EBADF;
    
    while ((read = getline(&line, &len, fp)) != -1) {
        line[read-1] = '\0'; //Remove newline at the end and replace with NULL
        printf("Retrieved line of length %d %s\n", read, line);
        token = strtok(line, " ");
        str_input1 = token;
        token = strtok(NULL, " ");
        str_input2 = token;
        printf("Retrieved str1 %s %d str2 %s %d\n", str_input1, strlen(str_input1), str_input2, strlen(str_input2));
        
        switch ( cmd_option ) {
            case SUBSTRING_CASE_DEFAULT_THREADS:
                parallelSubstringCount(str_input1, str_input2);
                break;
            
            case SUBSTRING_CASE_CONFIG_THREADS:
                if ( cmd_option_threads < MIN_THREADS || cmd_option_threads > MAX_THREADS ) return EINVAL;
            
                parallelSubstring(str_input1, str_input2, cmd_option_threads);
                break;
            
            case STRINGCAT_CASE_STACK:
                stringcat_stack(str_input1, str_input2);
                break;
            
            case STRINGCAT_CASE_HEAP:
                stringcat_heap(str_input1, str_input2);
                break;
            
            default:
                return EINVAL;
                break;
        }
    }
    
    fclose(fp);
    if (line) free(line);
    
    return 0;
}