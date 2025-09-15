#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0, counter = 0;
int next_produced = 1;
int next_consumed = 0;
bool done = false;

void produce_one()
{
    if (counter == BUFFER_SIZE)
    {
        cout << "Buffer is full" << endl;
        return;
    }

    buffer[in] = next_produced;
    cout << "Produced: " << next_produced << " at " << in << endl;
    in = (in + 1) % BUFFER_SIZE;
    counter++;
    next_produced++;

    //     if (next_produced > 10) {
    //         done = true;
    //     }
}

void consume_one()
{
    if (counter == 0)
    {
        cout << "Buffer is empty" << endl;
        return;
    }

    next_consumed = buffer[out];
    cout << "Consumed: " << next_consumed << " from " << out << endl;
    out = (out + 1) % BUFFER_SIZE;
    counter--;
}

int main()
{
    // while (!done || counter > 0) {
    //     produce_one();
    //     consume_one();

    //     this_thread::sleep_for(chrono::milliseconds(200));
    // }
    produce_one();
    produce_one();

    consume_one();
    produce_one();
    produce_one();
    consume_one();

    produce_one();
    produce_one();
    produce_one();
    produce_one();
    produce_one();
    produce_one();

    consume_one();
    produce_one();

    return 0;
}
