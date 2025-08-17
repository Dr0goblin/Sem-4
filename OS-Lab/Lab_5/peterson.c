#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_THREADS 2

// Shared variables for Peterson's algorithm
bool flag[NUM_THREADS] = {false, false};
int turn = 0;
int shared_counter = 0; // Shared resource to protect

void *thread_function(void *thread_id) {
    int id = *(int *)thread_id;
    int other = 1 - id; // ID of the other thread
    
    for (int i = 0; i < 5; i++) { // Each thread increments counter 5 times
        // Entry section - Peterson's algorithm
        flag[id] = true;
        turn = other;
        
        // Wait while the other thread is in its critical section
        while (flag[other] && turn == other) {
            // Busy wait (spinlock)
        }
        
        // Critical section
        printf("Thread %d entering critical section (iteration %d)\n", id, i+1);
        int temp = shared_counter;
        temp++;
        shared_counter = temp;
        printf("Thread %d updated counter to: %d\n", id, shared_counter);
        
        // Exit section
        flag[id] = false;
        
        // Remainder section
        usleep(100000); // Sleep for 100ms to allow other thread to run
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1};
    
    printf("Peterson's Solution for Mutual Exclusion\n");
    printf("Initial counter value: %d\n", shared_counter);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i])) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    
    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Final counter value: %d (should be 10)\n", shared_counter);
    return 0;
}
