//
//  stringcat.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "stringcat.h"
#include "strings_api_shim.h"
#include "utils.h"
#include "common_defs.h"

/*!
 * @brief
 * @param
 * @return
 */
char* stringcat(char* str1, const char* str2){
    char *ret = str1;
    
    while (*str1) str1++;
    
    while ((*str1++ = *str2++));
    
    return ret;
}

/*!
 * @brief
 * @param
 * @return
 * @notes For the output string, one version of the API will allocate space on the heap for the result.
 *        !!! Bad Idea, Have been burnt too many times here, the caller should allocated the memory,
 *            that way the caller can deallocate. It really helps as the code becomes complex. Static
 *            analysis tools can catch memory leaks if the caller is responsible for free...
 */
char* stringcat_heap(const char* str1, const char* str2, char* str3){
    int len1 = get_string_len(str1);
    char *ret = str3;
    
    mem_copy(str3, str1, len1);
    *(str3+len1) = '\0';
    
    while (*str3) str3++;
    
    while ((*str3++ = *str2++));
    
    return ret;
}

/*!
 * @brief
 * @param
 * @return
 * @notes OK, noheap, nostack. Whats the other option to do this? files? pipes?
 *        This could be a usecase where we dont want the stack variable sent to us
 *        malloc can not be used. So we would have the caller of this function
 *        manage memory on his end for the concatenated string, this function
 *        would essentially go through and send back a concatenated string.
 */
char* stringcat_nonheap(const char* str1, const char* str2){
    return NULL;
}

/*!
 * @brief
 * @param
 * @return
 */
void* stringcat_pipe(void* args){
    strings_strcat_pipe_struct* pipe_names = args;
    int fd = 0;
    int str_out_len = 0;
    char str_max[MAX_STRING_SIZE] = {0};
    
    //open pipe 1 read str1
    fd = open(pipe_names->input_str1_pipe, O_RDONLY);
    //str_out_len = read(fd, str_max, MAX_STRING_SIZE);
    close(fd);
    
    //open pipe 2 read str2
    fd = open(pipe_names->input_str2_pipe, O_RDONLY);
    //str_out_len = read(fd, str_max, MAX_STRING_SIZE);
    close(fd);
    
    //CONCAT
    //open ouput pipe and write str
    mkfifo(pipe_names->output_str_pipe, 0666);
    fd = open(pipe_names->output_str_pipe, O_WRONLY);
    write(fd, str_max, MAX_STRING_SIZE);
    close(fd);
    unlink(pipe_names->input_str2_pipe);

    return 0;
}
