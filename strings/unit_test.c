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
 * @brief Prints test result
 * @param count count reported by the API
 * @param expected_count result expected
 */
void print_test_result(int count, int expected_count){
    if(count == expected_count){
        printf("Unit Test return %d = PASS \n\n", count);
    } else {
        printf("Unit Test return %d = FAIL \n\n", count);
    }
}


/*!
 * @brief Entry point for running unit tests
 * @param str1 Test case type
 * @param str2 Test data input file
 * @return PASS or FAIL CAUSE
 * @usage file_name, test_case, #_of_threads
 */
int unit_test_main(const char* str1, const char* str2, const char* str3){
#ifdef EXTENSIVE_DBG
    //strings_unit_test_input
    logConsole(str1);
    logConsole(str2);
    logConsole(str3);
#endif //EXTENSIVE_DBG
    
    FILE * fp = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char* token = NULL;
    char* str_input1 = NULL;
    char* str_input2 = NULL;
    char* str_input3 = NULL;
    
    unsigned int substring_count = 0;
    //int cmd_option_threads = atoi(str3);
    int cmd_option = atoi(str2);
    if ( cmd_option <= 0 || cmd_option >= MAX_CMD_OPTIONS ) return EINVAL;
    
    fp = fopen(str1, "r");
    if (fp == NULL) return EBADF;
    
    while ((read = getline(&line, &len, fp)) != -1) {
        //TODO//
        //In addition to the set of pre-curated test strings, we should
        //test null strings passed in and the max string cases to get
        //the stability of the API in edge cases
        
        //Remove newline at the end of each line and replace with NULL
        line[read-1] = '\0';
#ifdef EXTENSIVE_DBG
        printf("Retrieved line of length %d %s\n", (int)read, line);
#endif //EXTENSIVE_DBG
        token = strtok(line, " ");
        str_input1 = token;
        token = strtok(NULL, " ");
        str_input2 = token;
        token = strtok(NULL, " ");
        str_input3 = token;
        printf("Run Unit Test str1 %s size1 %d str2 %s size2 %d result %s\n", \
               str_input1, (int)get_string_len(str_input1), \
               str_input2, (int)get_string_len(str_input2), \
               str_input3);
        
        switch ( cmd_option ) {
            case SUBSTRING_CASE_DEFAULT_THREADS:
            case SUBSTRING_CASE_CONFIG_THREADS:
                substring_count = parallelSubstringCount(str_input1, str_input2);
                break;
            
            /* //TODO//
            case SUBSTRING_CASE_CONFIG_THREADS:
                if ( cmd_option_threads < MIN_THREADS || cmd_option_threads > MAX_THREADS ) return EINVAL;
            
                parallelSubstring(str_input1, str_input2, cmd_option_threads);
                break;
            */
                
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
        
        print_test_result((int)substring_count, atoi(str_input3));
    }
    
    fclose(fp);
    if (line) free(line);
    
    return 0;
}