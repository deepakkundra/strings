//
//  utils.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//
//#include <string.h>

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

/*!
 * @brief Utility to find strlen
 * @param str String to find the string length
 * @return The result of the function
 */
unsigned int get_string_len(const char* str){
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

//Replace with own memcmp util
/*!
 * @brief Utility to compare mem
 * @param str1 array 1
 * @param str2 array 2
 * @param n size to compare
 * @return The result is 0 if equal
 */
unsigned int is_mem_equal(const char *str1, const char *str2, int n){
    while (n-- != 0) {
        if(*(str1+n) != *(str2+n)) return 1;
    }
    return 0;
}