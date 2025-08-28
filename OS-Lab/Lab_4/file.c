
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d is running\n", thread_num);
    sleep(2);
    printf("Thread %d is exiting\n", thread_num);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int num1 = 1, num2 = 2;

   
    if(pthread_create(&thread1, NULL, thread_function, &num1)) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

   
    if(pthread_create(&thread2, NULL, thread_function, &num2)) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    printf("Main thread continues while other threads run...\n");
    sleep(3);

    return 0;
}
