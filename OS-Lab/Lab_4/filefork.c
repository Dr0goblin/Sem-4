
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

void* thread_function(void* arg) {
    printf("Thread %d in process %d\n", *(int*)arg, getpid());
    sleep(2);
    return NULL;
}

int main() {
    pthread_t thread;
    int thread_num = 1;

    pthread_create(&thread, NULL, thread_function, &thread_num);

    printf("Main thread in parent %d\n", getpid());

    pid_t pid = fork();

    if(pid == 0) {
        printf("Child process %d (parent %d)\n", getpid(), getppid());
        sleep(1);
    } else if(pid > 0) {
        printf("Parent %d created child %d\n", getpid(), pid);
        pthread_join(thread, NULL);
        wait(NULL);
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}
