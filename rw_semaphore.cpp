#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t mutex;     
sem_t wrt;       
sem_t queueLock; 
int read_count = 0;
int dataValue = 0;

void* reader(void* arg) {
    int reader_id = *(int*)arg;

    while (true) {
        sem_wait(&queueLock);
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt);
        }

        sem_post(&mutex);
        sem_post(&queueLock);
    
        cout << "Reader " << reader_id << " reads data = " << dataValue << endl;
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt);
        }
        
        sem_post(&mutex);

        sleep(1);
    }
    return nullptr;
}

void* writer(void* arg) {
    int writer_id = *(int*)arg;

    while (true) {
        sem_wait(&queueLock);
        sem_wait(&wrt);

    
        dataValue++;
        cout << "Writer " << writer_id << " writes data = " << dataValue << endl;
        sleep(1);

        sem_post(&wrt);
        sem_post(&queueLock);

        sleep(2);
    }
    return nullptr;
}

int main() {
    pthread_t rtid[3], wtid[2];
    int r_ids[3] = {1, 2, 3};
    int w_ids[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    sem_init(&queueLock, 0, 1);

    for (int i = 0; i < 3; i++) {
        pthread_create(&rtid[i], nullptr, reader, &r_ids[i]);
    }

    for (int i = 0; i < 2; i++){
        pthread_create(&wtid[i], nullptr, writer, &w_ids[i]);
    }

    for (int i = 0; i < 3; i++){
        pthread_join(rtid[i], nullptr);
    }

    for (int i = 0; i < 2; i++) { 
        pthread_join(wtid[i], nullptr);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    sem_destroy(&queueLock);

}
