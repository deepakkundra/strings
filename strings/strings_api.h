//
//  strings_api.h
//  strings
//
//  Created by Deepak Kundra on 3/2/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#ifndef strings_api_h
#define strings_api_h

/*!
 * @name STRINGS_API_T
 *
 * @include strings_api.h
 *
 * @brief Options on how to perform string cat operation
 *
 * @param STRINGS_API_DEFAULT - Default similar to strcat() in std C lib
 *        str1 and str2 should not overlap in the memory, and str1 should have
 *        enough space for the concatenated string. If memory has not been
 *        allocated for the concatenated string the buffer overflow will
 *        be caused. Utility does not protect against this, caller is responsible
 *        str3 in this case is unused and can be/should be set to NULL
 *
 * @param STRINGS_API_HEAP - Caller in this case provides a str3 which is big enough 
 *        for the concatenated string. str1 and str2 will be concatenated and added to
 *        str3 and str3 pointer will be returned. If memory has not been
 *        allocated for the concatenated string the buffer overflow will
 *        be caused. Utility does not protect against this, caller is responsible
 *
 * @param STRINGS_API_NON_HEAP - //TODO//Will use separate API for this exercise
 *
 */
typedef enum STRINGS_API {
    STRINGS_API_MIN = 0,
    STRINGS_API_DEFAULT = STRINGS_API_MIN,
    STRINGS_API_HEAP,
    STRINGS_API_NON_HEAP,
    STRINGS_API_MAX
} STRINGS_API_T;

/*!
 * @name Maximum length of the pipe name
 */
#define STRINGS_API_MAX_PIPE_NAME_LEN 30

/*!
 * @name strings_strcat_pipe_struct
 */
typedef struct {
    char input_str1_pipe[STRINGS_API_MAX_PIPE_NAME_LEN];
    char input_str2_pipe[STRINGS_API_MAX_PIPE_NAME_LEN];
    char output_str_pipe[STRINGS_API_MAX_PIPE_NAME_LEN];
} strings_strcat_pipe_struct;

/*!
 * @name strings_strcat
 *
 * @include strings_api.h
 *
 * @brief Utility to concatenate two strings
 *
 * @param str1 Null terminated String 1
 *
 * @param str2 NULL terminated String 2
 *
 * @param option Refer to STRINGS_API_T for further information
 *
 * @return char* Pointer to the concatenated string
 *
 * @notes If input strings are not NULL terminated the utility
 *        will have undefined behavior.
 */
char* strings_strcat(char* str1, const char* str2, char* str3, STRINGS_API_T option);

/*!
 * @name strings_strcat_pipe
 *
 * @param args Pointer to the pipe names for input output
 *
 * @notes Use input_str1_pipe to send string 1
 *        Use input_str2_pipe to send string 2
 *        Read from output_str_pipe the concatenated string
 */
int strings_strcat_pipe(strings_strcat_pipe_struct* args);

/*!
 * @samples //TODO//
 */

#endif /* strings_api_h */
