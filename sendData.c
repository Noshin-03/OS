#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* threadFunction(void* arg) {
    int* result = (int*)malloc(sizeof(int));  // correct cast
    if (!result) {
        perror("malloc failed");
        pthread_exit(NULL);
    }

    *result = 42;
    printf("Thread: computed result = %d\n", *result);

    pthread_exit(result);
}

int main() {
    pthread_t thread;
    int* thread_result;

    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
        perror("pthread_create failed");
        return 1;
    }

    if (pthread_join(thread, (void**)&thread_result) != 0) {
        perror("pthread_join failed");
        return 1;
    }

    if (thread_result) {
        printf("Main thread received: %d\n", *thread_result);
        free(thread_result);
    } else {
        printf("Thread returned NULL\n");
    }

    return 0;
}
