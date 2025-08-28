
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d is running\n", thread_num);
    sleep(thread_num);
    printf("Thread %d is exiting\n", thread_num);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int num1 = 1, num2 = 2;

    pthread_create(&thread1, NULL, thread_function, &num1);
    pthread_create(&thread2, NULL, thread_function, &num2);

    printf("Main thread waiting...\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("All threads completed\n");

    return 0;
}
