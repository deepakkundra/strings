//
//  utils.h
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <errno.h>

/*!
 * @brief Custom error codes
 */
#define UTILS_ERROR_MIN    0
#define UTILS_ERROR_NOFAIL 0
#define UTILS_ERROR_MAX    255

/*!
 * @brief Logging utility
 * @param inPtrStr String to be displayed on the console
 * @return The result of the function
 */
void* ptrFnLogConsole(void* inPtrStr);

/*!
 * @brief Logging utility
 * @param str String to be displayed on the console
 * @return The result of the function
 */
void logConsole(const char* str);

/*!
 * @brief Logging utility
 * @param str, str2 String to be displayed on the console
 * @return The result of the function
 */
void logConsole2(const char* str, const char* str2);

/*!
 * @brief Logging utility
 * @param str, str2, str3 String to be displayed on the console
 * @return The result of the function
 */
void logConsole3(const char* str, const char* str2, const char* str3);

/*!
 * @brief Utility to find strlen
 * @param str String to find the string length
 * @return The result of the function
 */
unsigned int get_string_len(const char* str);

/*!
 * @brief Utility to compare mem
 * @param str1 array 1
 * @param str2 array 2
 * @param n size to compare
 * @return The result is 0 if equal
 */
unsigned int is_mem_equal(const char *str1, const char *str2, int n);

/*!
 * @brief Utility to copy mem
 * @param str1 array 1
 * @param str2 array 2
 * @param n size to copy
 * @return The result is 0 copy passed
 */
unsigned int mem_copy(char *str1, const char *str2, int n);

#endif /* utils_h */
