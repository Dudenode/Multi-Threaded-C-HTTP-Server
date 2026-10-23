#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <pthread.h>

extern int client_queue[256];     
extern int queue_count;
extern pthread_mutex_t mutex;
extern pthread_cond_t cond_var;


void *worker_thread(void *arg);


#endif