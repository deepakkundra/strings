//
//  utils.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#include "utils.h"

/*!
 * @brief Logging utility
 * @param inPtrStr String to be displayed on the console
 * @return The result of the function
 */
void* ptrFnLogConsole(void* inPtrStr) {
    char* log = (char*) inPtrStr;
    printf("%s \n", log);
    return 0;
}

/*!
 * @brief Logging utility
 * @param str String to be displayed on the console
 * @return The result of the function
 */
void logConsole(const char* str) {
    printf("%s \n", str);
}

/*!
 * @brief Logging utility
 * @param str, str2 String to be displayed on the console
 * @return The result of the function
 */
void logConsole2(const char* str, const char* str2){
    printf("%s %s \n", str, str2);
}

/*!
 * @brief Logging utility
 * @param str, str2, str3 String to be displayed on the console
 * @return The result of the function
 */
void logConsole3(const char* str, const char* str2, const char* str3){
    printf("%s %s %s\n", str, str2, str3);
}