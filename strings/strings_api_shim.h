//
//  strings_api_shim.h
//  strings
//
//  Created by Deepak Kundra on 3/2/16.
//  Copyright © 2016 Deepak Kundra. All rights reserved.
//

#ifndef strings_api_shim_h
#define strings_api_shim_h

#include <pthread.h>

#include "strings_api.h"

#define SHIM_CONNECTED

#ifdef SHIM_CONNECTED
/*!
 * @brief This file provides a connector so that the API headers can be
 *        sent to the customer and they can include it, and start their work
 *        while the actual implementation is worked on
 *
 */

inline char* strings_strcat(char* str1, const char* str2, char* str3, STRINGS_API_T option){
    if(option == STRINGS_API_DEFAULT) {
        return stringcat(str1, str2);
    } else if(option == STRINGS_API_HEAP) {
        return stringcat_heap(str1, str2, str3);
    } else if(option == STRINGS_API_NON_HEAP) {
        return stringcat_nonheap(str1, str2);
    } else {
        printf("ERROR: INVALID INPUT");
        return NULL;
    }
    return NULL;
};

int strings_strcat_pipe(strings_strcat_pipe_struct* args){
    void *status = 0;
    pthread_t thread;
    int thread_return = 0;

    thread_return = pthread_create(&thread, NULL, stringcat_pipe, (void*)args);
    if(thread_return)
    {
        printf("Error pthread_create() return code: %d\n", thread_return);
        return 0;
    }
    
    pthread_join(thread, &status);
    if (status == 0) {
        printf("API success\n");
        return 1;
    } else {
        printf("API failed\n");
    }
    
    return 0;
};

#else //SHIM_CONNECTED

//TODO//DUMMY IMPLEMENTATIONS OF ALL FUNC'S

#endif //SHIM_CONNECTED

#endif /* strings_api_shim_h */
