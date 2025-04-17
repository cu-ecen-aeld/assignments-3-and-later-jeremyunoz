#include "threading.h"
#include <pthread.h>
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
    sleep(1);

    if (pthread_mutex_lock(&thread_func_args->mutex) != 0) {
        ERROR_LOG("Fail to obtain mutex");
        thread_func_args->thread_complete_success = false;
        return thread_param;
    }

    printf("Waiting for 1 second after obtaining mutex!");
    sleep(1);

    if (pthread_mutex_unlock(&thread_func_args->mutex) != 0) {
        ERROR_LOG("Fail to release mutex");
        thread_func_args->thread_complete_success = false;
        return thread_param;
    }

    printf("Released mutex successfully!");

    thread_func_args->thread_complete_success = true;

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    

    return false;
}

