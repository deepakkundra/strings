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

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "common_defs.h"
#include "strings_api.h"

/*!
 * Global variables for running concat via pipes
 */
strings_strcat_pipe_struct pipe_names = {0};
char g_pipe_output[MAX_STRING_SIZE] = {0};

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
    int fd = 0;
    int str_out_len = 0;
    pid_t pid;
    
    if ( argc < MIN_INPUT_ARGS || argc > MAX_INPUT_ARGS  ) {
        printf("./strings FUNC_CASE STR1 STR2 OPTIONAL_MAX_THREADS  \n");
        printf("                                                    \n");
        printf("1   = SUBSTRING_CASE_DEFAULT_THREADS                \n");
        printf("2   = SUBSTRING_CASE_CONFIG_THREADS *NOT SUPPORTED* \n");
        printf("3   = STRINGCAT_CASE_DEFAULT                        \n");
        printf("4   = STRINGCAT_CASE_HEAP                           \n");
        printf("5   = STRINGCAT_CASE_NON_HEAP       *NOT SUPPORTED* \n");
        printf("6   = STRINGCAT_CASE_PIPE                           \n");
        printf("255 = RUN_UNIT_TEST                                 \n");
        printf("\n");
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
 
            case STRINGCAT_CASE_PIPE:
                strcpy(pipe_names.input_str1_pipe, "input_str1_pipe");
                strcpy(pipe_names.input_str2_pipe, "input_str2_pipe");
                strcpy(pipe_names.output_str_pipe, "output_str_pipe");
                
                mkfifo(pipe_names.input_str1_pipe, 0666);
                mkfifo(pipe_names.input_str2_pipe, 0666);
                mkfifo(pipe_names.output_str_pipe, 0666);
                
                pid = fork();
                if (pid == 0) {
                    //Call the API
                    if( strings_strcat_pipe(&pipe_names) == 1) {
#ifdef EXTENSIVE_DBG
                        printf("STRINGCAT CHILD DONE - PASS\n");
#endif //EXTENSIVE_DBG
                    } else {
                        printf("STRINGCAT CHILD DONE - FAILED\n");
                    }
                    //We need to kill the child!!!
                    return 0;
                } else {
                    //open pipe 1 write str1
                    fd = open(pipe_names.input_str1_pipe, O_WRONLY);
                    write(fd, argv[INPUT_STR1], (str_input1_len+1));
                    close(fd);
                    
                    //open pipe 2 write str2
                    fd = open(pipe_names.input_str2_pipe, O_WRONLY);
                    write(fd, argv[INPUT_STR2], (str_input2_len+1));
                    close(fd);
                    
                    //read pipe 3 and print result
                    fd = open(pipe_names.output_str_pipe, O_RDONLY);
                    str_out_len = read(fd, g_pipe_output, MAX_STRING_SIZE);
                    close(fd);
                    printf("STRINGCAT PIPE %s LEN %d\n\n", g_pipe_output, str_out_len);
                    
                    //Only parent does the unlink
                    unlink(pipe_names.input_str1_pipe);
                    unlink(pipe_names.input_str2_pipe);
                    unlink(pipe_names.output_str_pipe);
                }
                break;
                
            case RUN_UNIT_TEST:
                // file_name, test_case, #_of_threads
                return unit_test_main(argv[INPUT_STR1], argv[INPUT_STR2], argv[INPUT_THREADS]);
                break;
                
            default:
                printf("Command %d not recogonized \n", cmd_option);
                return EINVAL;
                break;
        }
    }
    
    return 0;
}