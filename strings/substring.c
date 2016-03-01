//
//  substring.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#include <stdlib.h>
#include <pthread.h>

#include "substring.h"
#include "utils.h"

const char* gInputString;
const char* gSubstring;

/*!
 * @brief Struct to hold the start and end index for search
 */
typedef struct {
    int thread_id;
    int start_index;
    int end_index;
    unsigned int count;
} index_struct;

/*!
 * @brief Sub string utility
 * @param inPtrStr String to be displayed on the console
 * @return The result of the function
 */
void* ptrFnSubString(void* inPtrArgs) {
    index_struct* args = inPtrArgs;
    
    args->count = parallelSubstringCount(gInputString, gSubstring);
    
    return 0;
}

/*!
 * @brief Finds the # of substring occurences in inputString
 * @param inputString The string to search in
 * @param substring The string to search for
 * @return # of occurences found
 */
unsigned int parallelSubstringCount(const char* inputString, const char* substring) {

    logConsole3("parallelSubstringCount() for strings", inputString, substring);
    
    return 1;
}

/*!
 * @brief Finds the # of substring occurences in inputString
 * @param inputString The string to search in
 * @param substring The string to search for
 * @param threads The # of threads to use
 * @return # of occurences found
 */
unsigned int parallelSubstring(const char* inputString, const char* substring, int threads) {
    gInputString = (char*)inputString;
    gSubstring = (char*)substring;
    
    void *status = 0;
    pthread_t thread_arr[threads];
    index_struct thread_data_arr[threads];
    int thread_return = 0;
    int i = 0;
    unsigned int count = 0;
    
    printf("parallelSubstring() for str %s sub %s threads %d \n", inputString, substring, threads);
    
    /* Create independent threads each of which will execute function */
    for (i = 0; i < threads; i++) {
        thread_return = pthread_create( &thread_arr[i], NULL, ptrFnSubString, (void*) &thread_data_arr[i]);
        if(thread_return)
        {
            printf("Error pthread_create() return code: %d\n", thread_return);
            return thread_return;
        }
    }
    
    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
    for (i = 0; i < threads; i++) {
        pthread_join(thread_arr[i], &status);
        if (status == 0) {
            count += thread_data_arr[i].count;
            printf("thread returned with val %d\n",count);
        } else {
            printf("thread failed\n");
        }
    }
    
    return count;
}