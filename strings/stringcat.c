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
 * @brief Default string cat similar to library implementation
 * @param str1 Destination string
 * @param str2 Source string to be appended to the Destination string
 * @return Pointer to concated string
 */
char* stringcat(char* str1, const char* str2){
    char *ret = str1;
    
    while (*str1) str1++;
    
    while ((*str1++ = *str2++));
    
    return ret;
}

/*!
 * @brief Heap allocated string cat, the caller provides the output memory
 * @param str1 Destination string
 * @param str2 Source string to be appended to the Destination string
 * @return Pointer to concated string
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
 * @brief NOT SUPPORTED - //TODO
 */
char* stringcat_nonheap(const char* str1, const char* str2){
    return NULL;
}

/*!
 * @brief This function uses pipes to communicate with the caller to get
 *        input strings and send back the concatenated output string
 * @param args Names of the pipes to use for communication
 * @return 0
 * @notes OK, noheap, nostack. Whats the other option to do this? files? pipes?
 *        This could be a usecase where we dont want the stack variable sent to us
 *        sending pointers to stack variables in flat address space to a caller
 *        generally works but best to avoid it always. Constraint is malloc can not 
 *        be used. So we would have the caller of this function manage memory on his
 *        end for the concatenated string, this function would essentially go through
 *        and send back a concatenated string.
 */
void* stringcat_pipe(void* args){
    strings_strcat_pipe_struct* pipe_names = args;
    int fd = 0;
    int str_out_len = 0;
    char str_max[MAX_STRING_SIZE] = {0};
    char* ptr_strcat_loc = NULL;
    int strcat_loc_len = 0;
    
    //open pipe 1 read str1
    fd = open(pipe_names->input_str1_pipe, O_RDONLY);
    str_out_len = read(fd, str_max, MAX_STRING_SIZE);
    close(fd);
#ifdef EXTENSIVE_DBG
    printf("STR1 %s Len1 %d\n", str_max, str_out_len);
#endif //EXTENSIVE_DBG
    
    //open pipe 2 read str2
    strcat_loc_len = str_out_len - 1;
    ptr_strcat_loc = str_max + strcat_loc_len;
    fd = open(pipe_names->input_str2_pipe, O_RDONLY);
    str_out_len = read(fd, ptr_strcat_loc, MAX_STRING_SIZE);
    close(fd);
#ifdef EXTENSIVE_DBG
    printf("STR2 %s Len2 %d\n", ptr_strcat_loc, str_out_len);
#endif //EXTENSIVE_DBG
    
    //CONCAT
    //open ouput pipe and write str
    strcat_loc_len += str_out_len;
    fd = open(pipe_names->output_str_pipe, O_WRONLY);
    write(fd, str_max, strcat_loc_len);
    close(fd);

    return 0;
}
