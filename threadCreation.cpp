#include <iostream>
#include <thread>
using namespace std;

void threadFunction(const string& message) {
    cout << "Hello from the thread! Message: " << message << endl;
}

int main() {
    string msg = "Thread argument";

    // Create a thread that runs threadFunction with msg as argument
    thread t(threadFunction, msg);

    // Wait for the thread to finish
    t.join();

    cout << "Thread finished" << endl;
    return 0;
}
