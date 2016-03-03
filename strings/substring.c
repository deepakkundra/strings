//
//  substring.c
//  strings
//
//  Created by Deepak Kundra on 2/29/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#include <stdlib.h>
#include <pthread.h>

#include "common_defs.h"

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
 * @brief Global vars to keep track of the pointers to the input strings
 */
const char* gInputString = NULL;
const char* gSubstring = NULL;
unsigned int gInputStringLen = 0;
unsigned int gSubstringLen = 0;
unsigned int gThreadCount = 0;

/*!
 * @brief Sub string utility
 * @param index String to be displayed on the console
 * @return If there is an invalid char in the string return 1 else 0
 * Valid char is an ASCII value
 */
int fnSubString(index_struct* index){
    
    char* inputString = (char*)(gInputString + (index->start_index));
    
    //TODO//
    //Add check to make sure the char is valid
    
    for(int i = 0; \
        (i <= (index->end_index) - (index->start_index)) && \
        (((index->end_index) - ((index->start_index) + i)) >= (gSubstringLen - 1)); \
        i++){
        
        if (*inputString != *gSubstring) {
            inputString += 1;
        } else {
            if(is_mem_equal(inputString, gSubstring, gSubstringLen) == 0) {
                index->count += 1;
            }
            inputString += 1;
        }
    }

    return 0;
}


/*!
 * @brief Sub string utility
 * @param inPtrArgs index_struct passed as args
 * @return The result of the function
 */
void* ptrFnSubString(void* inPtrArgs) {
    index_struct* args = inPtrArgs;

#ifdef EXTENSIVE_DBG
    printf("ptrFnSubString() Thread ID = %d, Start = %d, End = %d\n", args->thread_id, args->start_index, args->end_index);
#endif //EXTENSIVE_DBG
    
    //FORK if :-
    //1. # of threads is < MAX_THREADS, we are doing one tree depth for now
    //2. size of seach set is > 2 x substr_size-1, to eliminate forking middle thread
    if (gThreadCount < MAX_THREADS && (args->end_index - args->start_index) >= (2 * gSubstringLen)) {
        void *status = 0;
        
        //malloc is defined as MT, so we should be ok//
        //If the platform we are on makes malloc not MT, then we got to
        //lock this call!
        pthread_t* thread_arr = malloc(MIN_THREADS * sizeof(pthread_t));
        if(thread_arr == NULL) return 0;
        
        index_struct* thread_index_arr = malloc(MIN_THREADS * sizeof(index_struct));
        if(thread_index_arr == NULL){
            free(thread_arr);
            return 0;
        }
        
        int thread_return = 0;
        int i = 0;
        unsigned int count = 0;
        
        //Partition the string and set the index for the threads
        //Thread Left
        thread_index_arr->count = 0;
        thread_index_arr->start_index = args->start_index;
        thread_index_arr->end_index = (args->end_index - args->start_index)/2;
        
        //Thread Right
        (thread_index_arr+1)->count = 0;
        (thread_index_arr+1)->start_index = ((args->end_index - args->start_index)/2)+1;
        (thread_index_arr+1)->end_index = args->end_index;
        
        //Thread Middle
        (thread_index_arr+2)->count = 0;
        (thread_index_arr+2)->start_index = (thread_index_arr->end_index + 1) - (gSubstringLen - 1);
        (thread_index_arr+2)->end_index = ((thread_index_arr+1)->start_index - 1) + (gSubstringLen - 1);
        
        // Create independent threads each of which will execute function
        for (i = 0; i < MIN_THREADS; i++) {
            (thread_index_arr+i)->thread_id = gThreadCount;
            gThreadCount += 1;
            thread_return = pthread_create( thread_arr+i, NULL, ptrFnSubString, (void*)(thread_index_arr+i));
            if(thread_return)
            {
                printf("Error pthread_create() return code: %d\n", thread_return);
                return 0;
            }
        }
    
        // Wait till threads are complete before continuing...
        for (i = 0; i < MIN_THREADS; i++) {
            pthread_join(*(thread_arr+i), &status);
            if (status == 0) {
                count += (thread_index_arr + i)->count;
                //Thread id goes from 0-X, Actual thread is +1 to the ID
                printf("Thread %d returned, Total # found yet %d\n", ((thread_index_arr+i)->thread_id+ 1), count);
            } else {
                printf("Thread %d failed\n", i);
            }
        }
        
        args->count = count;
        
        if(thread_index_arr != NULL) free(thread_index_arr);
        if(thread_arr != NULL) free(thread_arr);
    } else {
        //Find Substring...
        if(fnSubString(args) != 0) printf("ERROR: Invalid char found, returning partial result!");
    }
    
    return 0;
}

/*!
 * @brief Finds the # of gSubstring occurences in gInputString
 * @param index details for the search
 * @return # of occurences found
 */
unsigned int parallelSubstringMultiThread(index_struct* index) {
    //Just in case, future proof!
    if(gInputStringLen == 0 ||  gSubstringLen == 0 \
       || gInputString == NULL || gSubstring == NULL || index == NULL) return 0;
    
    void *status = 0;
    pthread_t thread;
    int thread_return = 0;
    unsigned int count = 0;
    
    gThreadCount += 1;
    thread_return = pthread_create(&thread, NULL, ptrFnSubString, (void*)index);
    if(thread_return)
    {
        printf("Error pthread_create() return code: %d\n", thread_return);
        return 0;
    }
    
    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
    pthread_join(thread, &status);
    if (status == 0) {
        count = index->count;
        printf("Thread 1 returned, Total # found %d\n", count);
    } else {
        printf("Thread 1 failed\n");
    }
    
    return count;
}

/*!
 * @brief Finds the # of substring occurences in inputString
 * @param inputString The string to search in
 * @param substring The string to search for
 * @return # of occurences found
 */
unsigned int parallelSubstringCount(const char* inputString, const char* substring) {
#ifdef EXTENSIVE_DBG
    logConsole3("parallelSubstringCount() for strings", inputString, substring);
#endif //EXTENSIVE_DBG
    
    unsigned int count = 0;
    gThreadCount = 0;
    gInputStringLen = get_string_len(inputString);
    gSubstringLen = get_string_len(substring);
    index_struct* index = NULL;
    
    if (gInputStringLen < MIN_STRING_SIZE || gSubstringLen < MIN_STRING_SIZE \
        || gInputStringLen > MAX_STRING_SIZE || gSubstringLen > MAX_STRING_SIZE \
        || gSubstringLen > gInputStringLen) {
        return 0;
    }
    
    gInputString = (char*)inputString;
    gSubstring = (char*)substring;

    index = malloc(sizeof(index_struct));
    if(index == NULL) return 0;
    
    index->thread_id = 0;
    index->start_index = 0;
    index->end_index = gInputStringLen - 1;
    index->count = 0;

    //Input should be atleast big enough to create threads, look at the alogrithm doc
    if(gInputStringLen < (gSubstringLen * MIN_MULTIPLIER)){
        if(fnSubString(index) != 0) printf("ERROR: Invalid char found, returning partial result!");
 
        count = index->count;
    } else {
        count = parallelSubstringMultiThread(index);
    }
        
    if(index != NULL) free(index);
    
    return count;
}