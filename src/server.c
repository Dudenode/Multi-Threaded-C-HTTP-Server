#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <signal.h>
#include "threadpool.h"
#include "error.h"

#define SERVER_PORT 8080
#define LISTENQ 10

#define MAXLINE 4096
#define SA struct sockaddr

volatile sig_atomic_t server_running = 1;

int server_fd;

void handle_sigint(int sig) {
    server_running = 0;
    close(server_fd);
}

int main(){
    
    signal(SIGINT, handle_sigint);
    
    printf("Server listening on port 8080 with 8 worker threads...\n");
    
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if (server_fd<0){
        err_n_die("server failed!");
    }
    else{
        printf("Socket allocated!\n");

    }

    struct sockaddr_in servadder;

    bzero(&servadder,sizeof(servadder));
    servadder.sin_family = AF_INET;
    servadder.sin_port = htons(SERVER_PORT);
    servadder.sin_addr.s_addr = htonl(INADDR_ANY);

    
    if (bind(server_fd,(SA *)&servadder,sizeof(SA))<0){
        err_n_die("bind failed!");
    }
    else{
        printf("bind succesful!\n");
    }
    
    if (listen(server_fd,LISTENQ)<0){
        err_n_die("listen failed!");
    }
    else{
        printf("listen succesful!\n");
    }

    pthread_t thread_pool[8];
        for (int i = 0; i < 8; i++) {
            pthread_create(&thread_pool[i], NULL, worker_thread, NULL);
        }
    
    while (server_running){

        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);
        char client_address[MAXLINE+1];

        
        int client_fd = accept(server_fd, (SA *)&addr, &addr_len);

        if (client_fd < 0) {
            if (!server_running) {
                break; // Socket closed by SIGINT, exit the loop cleanly
            }
        err_n_die("client allocation failed!");
        } 
        else {
            inet_ntop(AF_INET, &addr.sin_addr, client_address, MAXLINE);
            printf("client connection: %s\naccept success!\n", client_address);
        }

            pthread_mutex_lock(&mutex);
        
            client_queue[queue_count] = client_fd;
            queue_count++;
        
            pthread_mutex_unlock(&mutex);
        
            pthread_cond_signal(&cond_var);
        
    }
    pthread_cond_broadcast(&cond_var);


    for (int i = 0; i < 8; i++) {
        pthread_join(thread_pool[i], NULL);
    }


    close(server_fd);
    return 0;
}
