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


#endif /* utils_h */
