#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

// sem_t sem;

// void* thread_function(void* arg){
//     sem_wait(&sem);
//     printf("Thread %ld\n", (long)arg);
//     sleep(1);
//     printf("bye\n");
//     sem_post(&sem);

// }



// int main()
// {
//     pthread_t thread[3];

//     sem_init(&sem,0,1);

//     for(long i=0;i<3;i++){
//         pthread_create(&thread[i],NULL,thread_function,(void*)i);

// }

// for(long i=0;i<3;i++){
//     pthread_join(thread[i],NULL);
// }

// sem_destroy(&sem);

// return 0;
// }


// sem_t sem;

// void* thread_function(void *arg){
//     sem_wait(&sem);
//     printf("thread %ld is entering the C.S \n",(long)arg);
//     sleep(2);
//     sem_post(&sem);
//     printf("thread %ld is leaving the C.S \n",(long)arg);

// }

// int main(){
//     pthread_t p[5];
//     sem_init(&sem,0,3);
//     for(long i = 0; i < 5;i++){
//         pthread_create(&p[i],NULL,thread_function,(void*)i);
//     }

//     for(long i = 0; i < 5;i++){
//         pthread_join(p[i],NULL);
//     }

//     sem_destroy(&sem);
//     return 0;
// }

sem_t sem;

void* thread_function1(void* arg){
    printf("thread is waiting for signal \n");
    sem_wait(&sem);
    printf("thread received signal\n");
    return NULL;

}

void* thread_function2(void* arg){
    sleep(1);
    printf("sending signal \n");
    sem_post(&sem);
    return NULL;

}


int main(){
    pthread_t thread1,thread2;

    sem_init(&sem,0,0);
    pthread_create(&thread1,NULL,thread_function1,NULL);
     pthread_create(&thread2,NULL,thread_function2,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    sem_destroy(&sem);
    return 0;

}