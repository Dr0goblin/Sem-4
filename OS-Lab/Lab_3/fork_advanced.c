#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Before fork() - PID: %d\n", getpid());
    pid_t pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child process - PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(2);
        printf("Child exiting\n");
    } else {
        printf("Parent process - PID: %d, Child PID: %d\n", getpid(), pid);
        int status;
        wait(&status);
        printf("Child exited with status: %d\n", WEXITSTATUS(status));
    }
    return 0;
}
