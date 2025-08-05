#include <bits/stdc++.h>
using namespace std;

struct Task {
    string taskName;
    int priority;
    int burstTime;
    int startTime;
    int finishTime;
    int waitingTime;
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

        if (getline(ss, taskName, ',') &&
            getline(ss, priorityString, ',') &&
            getline(ss, burstString)) {

            Task task;
            task.taskName = taskName;
            task.priority = stoi(priorityString);
            task.burstTime = stoi(burstString);
            task.startTime = 0;
            task.waitingTime = 0;
            task.finishTime = 0;
            task.completed = 0;  // ✅ important
            tasks[taskCount++] = task;
        }
    }

    fileName.close();
}

int findShortestJob() {
    int minIndex = -1;
    int minBurst = 1e9;

    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i].completed && tasks[i].burstTime < minBurst) {
            minBurst = tasks[i].burstTime;
            minIndex = i;
        }
    }

    return minIndex;
}

void scheduleTask() {
    cout << "Shortest-Job-First (SJF) Scheduling\n" << endl;
    cout << left
         << setw(10) << "Task"
         << setw(10) << "Priority"
         << setw(10) << "Burst"
         << setw(10) << "Start"
         << setw(10) << "Waiting"
         << setw(10) << "Turnaround" << endl;

    int currentTime = 0, totalFinishTime = 0, totalWaitingTime = 0;
    int completed = 0;

    while (completed < taskCount) {
        int index = findShortestJob();
        if (index == -1) break;

        tasks[index].startTime = currentTime;
        tasks[index].waitingTime = currentTime;
        tasks[index].finishTime = currentTime + tasks[index].burstTime;

        totalWaitingTime += tasks[index].waitingTime;
        totalFinishTime += tasks[index].finishTime;

        cout << left
             << setw(10) << tasks[index].taskName
             << setw(10) << tasks[index].priority
             << setw(10) << tasks[index].burstTime
             << setw(10) << tasks[index].startTime
             << setw(10) << tasks[index].waitingTime
             << setw(10) << tasks[index].finishTime << endl;

        currentTime += tasks[index].burstTime;
        tasks[index].completed = 1;
        completed++;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time   : " << (float)totalWaitingTime / taskCount << endl;
    cout << "Average Turnaround Time : " << (float)totalFinishTime / taskCount << endl;
}

int main() {
    loadTasks("task.txt");
    scheduleTask();
    return 0;
}
