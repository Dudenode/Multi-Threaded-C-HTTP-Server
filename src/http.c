#include "http.h"
#include "error.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

void *handle_client(int client_fd){

    char buffer[4096];
    bzero(buffer, sizeof(buffer));
    read(client_fd, buffer, sizeof(buffer) - 1);
    printf("--- INCOMING REQUEST ---\n%s\n------------------------\n", buffer);

    char route[1024];
    sscanf(buffer,"GET %s",route);
    printf("Requested route: %s\n", route);
    if (strcmp(route, "/") == 0) {
        strcpy(route, "/index.html");
    }
    
    char *mime_type = "text/plain";
    char *target_file = route + 1;
    int file_fd = open(target_file, O_RDONLY);

    if (strstr(target_file, ".html")) {
        mime_type = "text/html";
    } else if (strstr(target_file, ".jpg")) {
        mime_type = "image/jpeg";
    } else if (strstr(target_file, ".pdf")) {
        mime_type = "application/pdf";
    }

    if (file_fd < 0) {
        
        char *not_found = "HTTP/1.1 404 Not Found\r\n\r\n404: File Missing";
        write(client_fd, not_found, strlen(not_found));
    } 
    else {

        char header_buffer[512];
        sprintf(header_buffer, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", mime_type);
        write(client_fd,header_buffer,strlen(header_buffer));

        char file_buffer[8192];
        bzero(file_buffer, sizeof(file_buffer));
        ssize_t bytes_read;

        while((bytes_read = read(file_fd, file_buffer, sizeof(file_buffer) - 1))>0){
            write(client_fd, file_buffer, bytes_read);
            
        }

        close(file_fd);
    }
    
    
    close(client_fd);
    return NULL;
}