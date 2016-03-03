//
//  stringcat.h
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#ifndef stringcat_h
#define stringcat_h

#include <stdio.h>
#include "strings_api.h"

/*!
 * @brief Default string cat similar to library implementation
 * @param str1 Destination string
 * @param str2 Source string to be appended to the Destination string
 * @return Pointer to concated string
 */
char* stringcat(char* str1, const char* str2);

/*!
 * @brief Heap allocated string cat, the caller provides the output memory
 * @param str1 Destination string
 * @param str2 Source string to be appended to the Destination string
 * @return Pointer to concated string
 */
char* stringcat_heap(const char* str1, const char* str2, char* str3);

/*!
 * @brief NOT SUPPORTED - //TODO
 */
char* stringcat_nonheap(const char* str1, const char* str2);

/*!
 * @brief This function uses pipes to communicate with the caller to get
 *        input strings and send back the concatenated output string
 * @param args Names of the pipes to use for communication
 */
void* stringcat_pipe(void* args);

#endif /* stringcat_h */
