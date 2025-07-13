#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        printf("Child executing external program...\n");
        execl("./hello", "hello", NULL); // Runs external 'hello'
        
        // Only reaches here if exec fails
        perror("exec failed");
        return 1;
    } 
    else if (pid > 0) { // Parent
        wait(NULL); // Wait for child
        printf("Parent: Child finished.\n");
    } 
    else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}
