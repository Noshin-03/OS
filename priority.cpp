#include <bits/stdc++.h>
using namespace std;

struct Task {
    string taskName;
    int priority;
    int burstTime;
    int startTime;
    int waitingTime;
    int finishTime;
    int completed;
};

const int MAX_TASKS = 100;
Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks(const string& filename) {
    ifstream fileName(filename);
    if (!fileName.is_open()) {
        cerr << "File can't be open" << endl;
        exit(1);
    }

    string line;
    while (getline(fileName, line)) {
        stringstream ss(line);
        string taskName, priorityString, burstString;

        if (getline(ss, taskName, ',') && getline(ss, priorityString, ',') && getline(ss, burstString)) {
            Task task;
            task.taskName = taskName;
            task.priority = stoi(priorityString);
            task.burstTime = stoi(burstString);
            task.startTime = 0;
            task.waitingTime = 0;
            task.finishTime = 0;
            task.completed = 0;
            tasks[taskCount++] = task;
        }
    }

    fileName.close();
}

int findHighestPriority() {
    int maxIndex = -1;
    int maxPriority = -1;

    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i].completed && tasks[i].priority > maxPriority) {
            maxPriority = tasks[i].priority;
            maxIndex = i;
        }
    }

    return maxIndex;
}

void scheduleTask() {
    cout << "\nPriority-Based Scheduling (Non-Preemptive)\n" << endl;

    cout << left
         << setw(10) << "Task"
         << setw(10) << "Priority"
         << setw(10) << "Burst"
         << setw(10) << "Start"
         << setw(10) << "Waiting"
         << setw(10) << "Turnaround" << endl;

    int currentTime = 0, totalWaitingTime = 0, totalFinishTime = 0;
    int completed = 0;

    while (completed < taskCount) {
        int idx = findHighestPriority();
        if (idx == -1) break;

        tasks[idx].startTime = currentTime;
        tasks[idx].waitingTime = currentTime;
        tasks[idx].finishTime = currentTime + tasks[idx].burstTime;

        totalWaitingTime += tasks[idx].waitingTime;
        totalFinishTime += tasks[idx].finishTime;

        cout << left
             << setw(10) << tasks[idx].taskName
             << setw(10) << tasks[idx].priority
             << setw(10) << tasks[idx].burstTime
             << setw(10) << tasks[idx].startTime
             << setw(10) << tasks[idx].waitingTime
             << setw(10) << tasks[idx].finishTime << endl;

        currentTime += tasks[idx].burstTime;
        tasks[idx].completed = 1;
        completed++;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time   : " << (float)totalWaitingTime / taskCount << endl;
    cout << "Average Finishing Time : " << (float)totalFinishTime / taskCount << endl;
}

int main() {
    loadTasks("task.txt");
    scheduleTask();
    return 0;
}
