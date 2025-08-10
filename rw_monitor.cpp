#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

class ReadWriteLock {
private:
    mutex mtx;
    condition_variable canRead, canWrite;
    int readCount = 0;
    int writeCount = 0;
    bool isWriting = false;

public:
    void startRead(int id) {
        unique_lock<mutex> lock(mtx);
        while (isWriting || writeCount > 0) {
            canRead.wait(lock);
        }
        readCount++;
        cout << "Reader " << id << " starts reading\n";
    }

    void endRead(int id) {
        unique_lock<mutex> lock(mtx);
        readCount--;
        cout << "Reader " << id << " ends reading\n";
        if (readCount == 0) {
            canWrite.notify_one();
        }
    }

    void startWrite(int id) {
        unique_lock<mutex> lock(mtx);
        writeCount++;
        while (isWriting || readCount > 0) {
            canWrite.wait(lock);
        }
        writeCount--;
        isWriting = true;
        cout << "Writer " << id << " starts writing\n";
    }

    void endWrite(int id) {
        unique_lock<mutex> lock(mtx);
        isWriting = false;
        cout << "Writer " << id << " ends writing\n";
        if (writeCount > 0) {
            canWrite.notify_one();
        } else {
            canRead.notify_all();
        }
    }
};

class Reader {
    int id;
    ReadWriteLock& rwLock;

public:
    Reader(int id, ReadWriteLock& rwLock) : id(id), rwLock(rwLock) {}

    void operator()() {
        while (true) {
            rwLock.startRead(id);
            this_thread::sleep_for(chrono::milliseconds(500)); 
            rwLock.endRead(id);
            this_thread::sleep_for(chrono::milliseconds(500)); 
        }
    }
};

class Writer {
    int id;
    ReadWriteLock& rwLock;

public:
    Writer(int id, ReadWriteLock& rwLock) : id(id), rwLock(rwLock) {}

    void operator()() {
        while (true) {
            rwLock.startWrite(id);
            this_thread::sleep_for(chrono::milliseconds(1000)); 
            rwLock.endWrite(id);
            this_thread::sleep_for(chrono::milliseconds(1500)); 
        }
    }
};

int main() {
    ReadWriteLock rwLock;

    vector<thread> readers;
    vector<thread> writers;

    for (int i = 1; i <= 3; i++) {
        readers.emplace_back(Reader(i, rwLock));
    }
    for (int i = 1; i <= 2; i++) {
        writers.emplace_back(Writer(i, rwLock));
    }

    for (auto& t : readers) t.join();
    for (auto& t : writers) t.join();

    return 0;
}
