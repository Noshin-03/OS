#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
int age;
void *myThreadFunction(void *arg)
{
    printf("Hello from a new thread!\n");
    printf("Enter your age: ");
    scanf("%d", &age);
    if (age < 0)
    {
        printf("Invalid age entered.\n");
        pthread_exit(NULL);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t first;

    // create new thread
    if (pthread_create(&first, NULL, myThreadFunction, NULL) != 0)
    {
        perror("Failed to create 1st thread");
        return 1;
    }


    // Wait for the new thread to finish
    pthread_join(first, NULL);
    printf("1st thread exiting.\n");
    printf("Your age is: %d\n", age);

    return 0;
}