#include "threadpool.h"
#include "http.h"
#include <signal.h>


extern volatile sig_atomic_t server_running;
int client_queue[256];     
int queue_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

void *worker_thread(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        while (queue_count == 0 && server_running){
            pthread_cond_wait(&cond_var,&mutex);
        }
        if (!server_running && queue_count == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        int client_fd = client_queue[0];
        for (int i = 0;i < queue_count-1; i++){
            client_queue[i]=client_queue[i+1];
        }
        queue_count--;
        pthread_mutex_unlock(&mutex);
        handle_client(client_fd);
    }
    return NULL;
}