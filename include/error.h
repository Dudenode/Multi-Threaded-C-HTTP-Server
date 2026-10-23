#ifndef ERROR_H
#define ERROR_H

void err_n_die(const char *fmt, ...);
void thread_err_n_die(int thread_err_code, const char *fmt, ...);

#endif