#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

void err_n_die(const char *fmt, ...) {

    int error_code = errno; 


    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);


    if (error_code != 0) {
        fprintf(stderr, ": %s", strerror(error_code));
    }
    

    fprintf(stderr, "\n");
    exit(1);
}

void thread_err_n_die(int thread_err_code, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (thread_err_code != 0) {
        fprintf(stderr, ": %s", strerror(thread_err_code));
    }
    
    fprintf(stderr, "\n");
    exit(1);
}