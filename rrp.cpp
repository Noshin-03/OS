#include <bits/stdc++.h>
using namespace std;

const int MAX_TASKS = 100;
const int QUANTUM = 10;

struct Task {
    string name;
    int priority;
    int burst;
    int remaining;
    int start;
    int finish;
    bool done;
    bool started;
};

Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, prioStr, burstStr;

        if (getline(ss, name, ',') && getline(ss, prioStr, ',') && getline(ss, burstStr)) {
            Task task;
            task.name = name;
            task.priority = stoi(prioStr);
            task.burst = stoi(burstStr);
            task.remaining = task.burst;
            task.start = -1;
            task.finish = 0;
            task.done = false;
            task.started = false;
            tasks[taskCount++] = task;
        }
    }

    file.close();
}

int findHighestPriority() {
    int maxPriority = -1;
    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i].done && tasks[i].priority > maxPriority) {
            maxPriority = tasks[i].priority;
        }
    }
    return maxPriority;
}

bool hasRemainingTasksInPriority(int prio) {
    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i].done && tasks[i].priority == prio) {
            return true;
        }
    }
    return false;
}

void scheduleRoundRobinWithPriority() {
    int currentTime = 0;

    while (true) {
        int highestPrio = findHighestPriority();
        if (highestPrio == -1) break;

        while (hasRemainingTasksInPriority(highestPrio)) {
            for (int i = 0; i < taskCount; i++) {
                if (!tasks[i].done && tasks[i].priority == highestPrio) {
                    if (!tasks[i].started) {
                        tasks[i].start = currentTime;
                        tasks[i].started = true;
                    }

                    int runTime = min(QUANTUM, tasks[i].remaining);
                    currentTime += runTime;
                    tasks[i].remaining -= runTime;

                    if (tasks[i].remaining == 0) {
                        tasks[i].done = true;
                        tasks[i].finish = currentTime;
                    }
                }
            }
        }
    }

    float totalWait = 0, totalFinish = 0;

    cout << "\nTask      Priority  Burst     Start     Finish    Waiting\n";
    for (int i = 0; i < taskCount; i++) {
        int waiting = tasks[i].finish - tasks[i].burst;
        totalWait += waiting;
        totalFinish += tasks[i].finish;

        cout << left << setw(10) << tasks[i].name
             << setw(10) << tasks[i].priority
             << setw(10) << tasks[i].burst
             << setw(10) << tasks[i].start
             << setw(10) << tasks[i].finish
             << waiting << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time   : " << totalWait / taskCount << endl;
    cout << "Average Finishing Time : " << totalFinish / taskCount << endl;
}

int main() {
    loadTasks("task.txt");
    scheduleRoundRobinWithPriority();
    return 0;
}
