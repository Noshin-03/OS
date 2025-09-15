#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // for sleep

void* threadFunc1(void* arg) {
    printf("Thread 1 is running\n");
    sleep(1);  // sleep for 1 second to simulate work
    printf("Thread 1 finished\n");
    return NULL;
}

void* threadFunc2(void* arg) {
    printf("Thread 2 is running\n");
    sleep(2);  // sleep for 2 seconds to simulate work
    printf("Thread 2 finished\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create threads
    if (pthread_create(&t1, NULL, threadFunc1, NULL) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }
    if (pthread_create(&t2, NULL, threadFunc2, NULL) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads have finished\n");

    return 0;
}
