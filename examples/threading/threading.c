#include "threading.h"
#include <bits/pthreadtypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    struct thread_data *thread_func_args = (struct thread_data*)thread_param;

    printf("Waiting for 1 second as thread created!");
    usleep(thread_func_args->wait_to_obtain_ms * 1000);

    if (pthread_mutex_lock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Fail to obtain mutex");
        thread_func_args->thread_complete_success = false;
        return thread_param;
    }

    DEBUG_LOG("Waiting for 1 second after obtaining mutex successfully!");
    usleep(thread_func_args->wait_to_release_ms * 1000);

    if (pthread_mutex_unlock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Fail to release mutex");
        thread_func_args->thread_complete_success = false;
        return thread_param;
    }

    DEBUG_LOG("Released mutex successfully!");

    thread_func_args->thread_complete_success = true;

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    struct thread_data* param = (struct thread_data*)malloc(sizeof(struct thread_data));
    if (param == NULL) {
        ERROR_LOG("Memory allocation failure for thread_data\n");
        return false;
    }

    param->mutex = mutex;
    param->wait_to_obtain_ms = wait_to_obtain_ms;
    param->wait_to_release_ms = wait_to_release_ms;
    param->thread_complete_success = false;

    int rc = pthread_create(thread, NULL, threadfunc, param);

    if ( rc != 0 ) {
        ERROR_LOG("pthread_create failed with error %d\n", rc);
        free(param);
        return false;
    }

    DEBUG_LOG("Thread successfully started");
    
    return true;
}

