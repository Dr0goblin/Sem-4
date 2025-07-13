#include <stdio.h>

int main() {
    printf("Hello from the external program!\n");
    printf("My PID: %d\n", getpid());
    return 0;
}
