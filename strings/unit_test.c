//
//  unit_test.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#include <stdio.h>
#include "utils.h"

/*!
 * @brief Entry point for running unit tests
 * @param str1 Test case type
 * @param str2 Test data input file
 * @return PASS or FAIL CAUSE
 */
int unit_test_main(const char* str1, const char* str2){
    logConsole(str1);
    logConsole(str2);
    return 0;
}