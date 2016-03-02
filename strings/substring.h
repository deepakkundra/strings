//
//  substring.h
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#ifndef substring_h
#define substring_h

#include <stdio.h>

/*!
 * @brief Finds the # of substring occurences in inputString
 * @param inputString The string to search in
 * @param substring The string to search for
 * @return # of occurences found
 */
unsigned int parallelSubstringCount(const char* inputString, const char* substring);

#endif /* substring_h */
