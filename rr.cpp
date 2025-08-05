#include <bits/stdc++.h>
using namespace std;

struct Task {
    string taskName;
    int priority;
    int burstTime;
    int startTime;
    int finishTime;
    int waitingTime;
    int remainingTime;
    bool hasStarted; 
};

const int MAX_TASKS = 100;
Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks(const string& filename) {
    ifstream fileName(filename);
    if (!fileName.is_open()) {
        cerr << "File can't be opened" << endl;
        exit(1);
    }

    string line;
    while (getline(fileName, line)) {
        stringstream ss(line);
        string taskName, priorityString, burstString;

        if (getline(ss, taskName, ',') &&
            getline(ss, priorityString, ',') &&
            getline(ss, burstString)) {

            Task task;
            task.taskName = taskName;
            task.priority = stoi(priorityString);
            task.burstTime = stoi(burstString);
            task.startTime = -1;
            task.finishTime = 0;
            task.waitingTime = 0;
            task.remainingTime = task.burstTime;
            task.hasStarted = false;
            tasks[taskCount++] = task;
        }
    }

    fileName.close();
}

void scheduleTasks(int timeQuantum) {
    cout << "\nRound-Robin (RR) Scheduling\n" << endl;
    cout << left 
         << setw(10) << "Task" 
         << setw(10) << "Priority"
         << setw(10) << "Burst" 
         << setw(10) << "Start"
         << setw(10) << "Waiting"
         << setw(10) << "Turnaround" << endl;

    queue<int> readyQueue;
    for (int i = 0; i < taskCount; i++) {
        readyQueue.push(i);
    }

    int currentTime = 0;
    int totalWaitingTime = 0, totalFinishTime = 0;

    while (!readyQueue.empty()) {
        int index = readyQueue.front();
        readyQueue.pop();

        if (!tasks[index].hasStarted) {
            tasks[index].startTime = currentTime;
            tasks[index].hasStarted = true;
        }

        int timeUsed = min(timeQuantum, tasks[index].remainingTime);
        currentTime += timeUsed;
        tasks[index].remainingTime -= timeUsed;

        if (tasks[index].remainingTime == 0) {
            tasks[index].finishTime = currentTime;
            tasks[index].waitingTime = tasks[index].finishTime - tasks[index].burstTime;

            totalWaitingTime += tasks[index].waitingTime;
            totalFinishTime += tasks[index].finishTime;
        } else {
            readyQueue.push(index);
        }
    }

    for (int i = 0; i < taskCount; i++) {
        cout << left
             << setw(10) << tasks[i].taskName
             << setw(10) << tasks[i].priority
             << setw(10) << tasks[i].burstTime
             << setw(10) << tasks[i].startTime
             << setw(10) << tasks[i].waitingTime 
             << setw(10) << tasks[i].finishTime << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time   : " << (float)totalWaitingTime / taskCount << endl;
    cout << "Average Finishing Time : " << (float)totalFinishTime / taskCount << endl;
}

int main() {
    loadTasks("task.txt");
    int timeQuantum;
    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;
    scheduleTasks(timeQuantum);
    return 0;
}
