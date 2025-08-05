#include <bits/stdc++.h>
using namespace std;

struct Task {
    string taskName;
    int priority;
    int burstTime;
    int startTime;
    int finishTime;
    int waitingTime;
};

const int MAX_TASKS = 100;
Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks(const string& filename) {
    ifstream fileName(filename);
    if(!fileName.is_open()) {
        cerr << "File is not open" << endl;
        exit(1);
    }

    string line;
    while(getline(fileName, line)) {
        stringstream ss(line);
        string taskName, priorityString, burstString;

        if(getline(ss,taskName,',') and getline(ss,priorityString,',') and getline(ss,burstString)) {
            Task task;
            task.taskName = taskName;
            task.priority = stoi(priorityString);
            task.burstTime = stoi(burstString);
            tasks[taskCount++] = task;
        }
    }


    fileName.close();
}

void scheduleTask() {
    cout << "First-Come-First-Service(FCFS) Scheduling\n" << endl;
    cout << left
         << setw(10) << "Task"
         << setw(10) << "Priority"
         << setw(10) << "Burst"
         << setw(10) << "Start"
         << setw(10) << "Turnaround"
         << setw(10) << "Waiting" << endl;

    int currentTime = 0, totalFinishingTime = 0, totalWaitingTime = 0;

    for(int i = 0; i < taskCount; i++) {
        tasks[i].startTime = currentTime;
        tasks[i].waitingTime = currentTime;
        tasks[i].finishTime = currentTime + tasks[i].burstTime;

        int finish_Time = tasks[i].finishTime;
        totalWaitingTime += tasks[i].waitingTime;
        totalFinishingTime += finish_Time;

        cout << left
             << setw(10) << tasks[i].taskName
             << setw(10) << tasks[i].priority
             << setw(10) << tasks[i].burstTime
             << setw(10) << tasks[i].startTime
             << setw(10) << tasks[i].finishTime
             << setw(10) << tasks[i].waitingTime << endl;
             
        currentTime = tasks[i].finishTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time : " << (float)totalWaitingTime / taskCount << endl;
    cout << "\nAverage Turnaround Time : " << (float)totalFinishingTime / taskCount << endl;
}

int main() {
    loadTasks("task.txt");
    scheduleTask();
    return 0;
}