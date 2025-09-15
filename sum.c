#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 20

typedef struct {
    int* arr;
    int start;
    int end;
    long long partial_sum;
} ThreadData;

void* partialSum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long sum = 0;
    for (int i = data->start; i <= data->end; i++) {
        sum += data->arr[i];
    }
    data->partial_sum = sum;
    return NULL;
}

int main() {
    int arr[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i + 1;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    threadData[0].arr = arr;
    threadData[0].start = 0;   
    threadData[0].end = 4;

    threadData[1].arr = arr;
    threadData[1].start = 5;    
    threadData[1].end = 9;

    threadData[2].arr = arr;
    threadData[2].start = 10; 
    threadData[2].end = 14;

    threadData[3].arr = arr;
    threadData[3].start = 15;   
    threadData[3].end = 19;

    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].partial_sum = 0;
        if (pthread_create(&threads[i], NULL, partialSum, &threadData[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    long long total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_sum += threadData[i].partial_sum;
    }

    printf("Total sum: %lld\n", total_sum);

    return 0;
}
