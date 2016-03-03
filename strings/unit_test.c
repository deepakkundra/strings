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
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "strings_api.h"
#include "common_defs.h"

/*!
 */
strings_strcat_pipe_struct pipe_names = {0};
char g_pipe_output[MAX_STRING_SIZE] = {0};


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
    char* str_dest = NULL;
    int str_input1_len = 0;
    int str_input2_len = 0;
    int fd = 0;
    int str_out_len = 0;
    
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
        
        //In case of strcat functions we should try to see eventhough
        //we are saying we are not responsible, in cases where the string
        //size is not enough to hold the concatenated string
        
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
        
        str_input1_len = (int)get_string_len(str_input1);
        str_input2_len = (int)get_string_len(str_input2);
        
        printf("Run Unit Test str1 %s size1 %d str2 %s size2 %d result %s\n", \
               str_input1, str_input1_len, \
               str_input2, str_input2_len, \
               str_input3);
        
        switch ( cmd_option ) {
            case SUBSTRING_CASE_DEFAULT_THREADS:
            case SUBSTRING_CASE_CONFIG_THREADS:
                substring_count = parallelSubstringCount(str_input1, str_input2);
                print_test_result((int)substring_count, atoi(str_input3));
                break;
            
            /* //TODO//
            case SUBSTRING_CASE_CONFIG_THREADS:
                if ( cmd_option_threads < MIN_THREADS || cmd_option_threads > MAX_THREADS ) return EINVAL;
            
                parallelSubstring(str_input1, str_input2, cmd_option_threads);
                break;
            */
                
            case STRINGCAT_CASE_DEFAULT:
                str_dest = calloc((str_input1_len + str_input2_len + 2), sizeof(char));
                memcpy(str_dest, str_input1, str_input1_len); //Since our original string cannot accomodate both
                printf("STRINGCAT %s\n\n", (strings_strcat(str_dest, str_input2, NULL, STRINGS_API_DEFAULT)));
                free(str_dest);
                break;
                
            case STRINGCAT_CASE_HEAP:
                str_dest = calloc((str_input1_len + str_input2_len + 2), sizeof(char));
                printf("STRINGCAT HEAP %s\n\n", (strings_strcat(str_input1, str_input2, str_dest, STRINGS_API_HEAP)));
                free(str_dest);
                break;
                
            case STRINGCAT_CASE_NON_HEAP:
                //TODO//
                printf("STRINGCAT NON-HEAP %s\n\n", (strings_strcat(str_input1, str_input2, NULL, STRINGS_API_NON_HEAP)));
                break;

            case STRINGCAT_CASE_PIPE:
                strcpy(pipe_names.input_str1_pipe, "input_str1_pipe");
                strcpy(pipe_names.input_str2_pipe, "input_str2_pipe");
                strcpy(pipe_names.output_str_pipe, "output_str_pipe");

                //open pipe 1 write str1
                mkfifo(pipe_names.input_str1_pipe, 0666);
                fd = open(pipe_names.input_str1_pipe, O_WRONLY);
                write(fd, str_input1, (str_input1_len+1));
                close(fd);
                unlink(pipe_names.input_str1_pipe);
                
                //open pipe 2 write str2
                mkfifo(pipe_names.input_str2_pipe, 0666);
                fd = open(pipe_names.input_str2_pipe, O_WRONLY);
                write(fd, str_input2, (str_input2_len+1));
                close(fd);
                unlink(pipe_names.input_str2_pipe);

                if( strings_strcat_pipe(&pipe_names) == 1) {
                    //read pipe 3 and print result
                    fd = open(pipe_names.output_str_pipe, O_RDONLY);
                    //str_out_len = read(fd, g_pipe_output, MAX_STRING_SIZE);
                    close(fd);
                    printf("STRINGCAT PIPE %s\n\n", g_pipe_output);
                } else {
                    printf("STRINGCAT PIPE FAILED \n\n");
                }
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