#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

int shared_counter = 0;
sem_t mutex; // Semaphore for mutual exclusion

void *thread_function(void *thread_id) {
    int id = *(int *)thread_id;
    
    for (int i = 0; i < 3; i++) { // Each thread increments counter 3 times
        // Wait (decrement semaphore)
        sem_wait(&mutex);
        
        // Critical section
        printf("Thread %d entering critical section (iteration %d)\n", id, i+1);
        int temp = shared_counter;
        usleep(100000); // Simulate work to increase chance of race condition
        temp++;
        shared_counter = temp;
        printf("Thread %d updated counter to: %d\n", id, shared_counter);
        
        // Signal (increment semaphore)
        sem_post(&mutex);
        
        // Remainder section
        usleep(50000); // Sleep to allow other threads to run
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Initialize semaphore (1 means binary semaphore)
    sem_init(&mutex, 0, 1);
    
    printf("Semaphore Solution for Race Conditions\n");
    printf("Initial counter value: %d\n", shared_counter);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i])) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    
    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Final counter value: %d (should be %d)\n", 
           shared_counter, NUM_THREADS * 3);
    
    // Clean up semaphore
    sem_destroy(&mutex);
    
    return 0;
}
