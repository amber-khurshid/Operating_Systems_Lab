#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
// void* print_message(void *ptr)
// {
//     char *message;
//     message = (char *)ptr;
//     printf("%s \n", message);
// }

// int main()
// {
//     pthread_t thread1,thread2;
//     char *message1 = " thread 1";
//     char *message2 = " thread 2";


//   pthread_create(&thread1, NULL, print_message, (void *)message1);
//     pthread_create(&thread2, NULL, print_message, (void *)message2);
    
//     pthread_join(thread1,NULL);
//     pthread_join(thread2,NULL);
// }


// struct thread_data {
//     int x;
//     int y;
//     int z;
// };


// void *print(void *threadArg) {
//     struct thread_data *my_data;
//     my_data = (struct thread_data *) threadArg;
//     printf("X: %d, Y: %d, Z: %d\n", my_data->x, my_data->y, my_data->z);
// }

// int main() {
//     pthread_t tid;
//     struct thread_data j;
//     j.x = 1;
//     j.y = 2;
//     j.z = j.x + j.y;
//     int return_value1;
//     return_value1 = pthread_create(&tid, NULL, print, (void *) &j);

//     pthread_join(tid, NULL);
//     exit(0);
// }


// struct thread_data
// {
//     int x;
//     int y;
//     int z;
// };


// void* print_message(void *s)
// {
//     struct thread_data *z;
//     z = (struct thread_data *) s;
//     printf("values are %d , %d ,%d \n", z->x,z->y,z->z);

// }

// int main(){
//     pthread_t t;
//    struct thread_data z;
//    z.x = 2;
//    z.y = 3;
//    z.z = z.x +z.y;

//    pthread_create(&t,NULL,print_message,(void *)&z);
//    pthread_join(t,NULL);
//    exit(0);

// }

// void *print(void *t)
// {
//     char *z ;
//     z = (char *)t;
//     printf(" %s \n",z);
// }

// int main(){
//     pthread_t t;
//     int r;
//     char *z = "Hello world";
//     r = pthread_create(&t,NULL,print,(void *)z);
//     if(r){
//         printf("Error , from pthread_create() is %d ",r);
//         exit(-1);
//             }

//     pthread_exit(NULL);

// }


int global = 0;
 pthread_mutex_t mu;
void *thread_function(){
 int i,j;
 for(i =0;i<5 ;i++){
    pthread_mutex_lock(&mu);
    j= global;
    j=j+1;
    printf(". ");
    fflush(stdout);
    sleep(1);
    global =j;
    pthread_mutex_unlock(&mu);

 }
}

int main(){
    pthread_t t;
   

    pthread_create(&t,NULL,thread_function,NULL);

    for(int i =0; i<5;i++)
    {
        pthread_mutex_lock(&mu);
        global+=1;
        pthread_mutex_unlock(&mu);
        printf("o ");
        fflush(stdout);
        sleep(1);
    }
    pthread_join(t,NULL);
    printf("My global is %d : ",global);
    exit(0);
}
