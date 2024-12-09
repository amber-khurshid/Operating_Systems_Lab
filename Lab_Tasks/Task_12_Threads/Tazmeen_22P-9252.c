#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct fib_arg {
    int n;
    int result;
};

void *fib_thread(void *arg) {
    struct fib_arg *fib_data;
    fib_data = (struct fib_arg *) arg;
    int n = fib_data->n;

    printf("Thread for n=%d started\n", n);

    if (n <= 0) {
        fib_data->result = 0;
    } else if (n == 1) {
        fib_data->result = 1;

    } else {
      
        struct fib_arg arg1;
        arg1.n = n - 1;
        arg1.result = 0;
        
        struct fib_arg arg2;
        arg2.n  = n - 2;
        arg2.result = 0;
        pthread_t thread1, thread2;

        pthread_create(&thread1, NULL, fib_thread, &arg1);
        pthread_create(&thread2, NULL, fib_thread, &arg2);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        fib_data->result = arg1.result + arg2.result;
    }

    printf("Thread for n=%d finished with result=%d\n", n, fib_data->result); 

    pthread_exit(NULL);
}

int main() {
    int n = 5;
    struct fib_arg fib_data ;
    fib_data.n = n;
    fib_data.result = 0;
    pthread_t thread;

    pthread_create(&thread, NULL, fib_thread, &fib_data);
    pthread_join(thread, NULL);

    printf("Fibonacci number at position %d is %d\n", n, fib_data.result);
    return 0;
}
