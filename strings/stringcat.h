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
 * @brief
 * @param
 * @return
 */
char* stringcat(char* str1, const char* str2);

/*!
 * @brief
 * @param
 * @return
 */
char* stringcat_heap(const char* str1, const char* str2, char* str3);

/*!
 * @brief
 * @param
 * @return
 */
char* stringcat_nonheap(const char* str1, const char* str2);

/*!
 * @brief
 * @param
 * @return
 */
void* stringcat_pipe(void* args);

#endif /* stringcat_h */
