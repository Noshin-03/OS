#include <bits/stdc++.h>
using namespace std;

struct Process {
    string pid;
    int arrival;
    int burst;
    int remaining;
    int start;
    int finish;
    int waiting;
    bool started;
};

bool allDone(vector<Process>& processes) {
    for (auto& p : processes)
        if (p.remaining > 0) return false;
    return true;
}

int findShortestJob(vector<Process>& processes, int currentTime) {
    int idx = -1;
    int minRem = INT_MAX;
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].arrival <= currentTime && processes[i].remaining > 0 && processes[i].remaining < minRem) {
            minRem = processes[i].remaining;
            idx = i;
        }
    }
    return idx;
}

int main() {
    vector<Process> processes = {
        {"P1", 0, 8, 8, -1, 0, 0, false},
        {"P2", 1, 4, 4, -1, 0, 0, false},
        {"P3", 2, 9, 9, -1, 0, 0, false},
        {"P4", 3, 5, 5, -1, 0, 0, false}
    };

    int currentTime = 0;
    while (!allDone(processes)) {
        int idx = findShortestJob(processes, currentTime);
        if (idx == -1) {
            currentTime++;
            continue;
        }

        if (!processes[idx].started) {
            processes[idx].start = currentTime;
            processes[idx].started = true;
        }

        processes[idx].remaining--;
        currentTime++;

        if (processes[idx].remaining == 0) {
            processes[idx].finish = currentTime;
            processes[idx].waiting = processes[idx].finish - processes[idx].arrival - processes[idx].burst;
        }
    }

    float totalWaiting = 0, totalFinish = 0;
    cout << left 
        << setw(10) << "Task" 
        << setw(10) << "Arrival" 
        << setw(10) << "Burst" 
        << setw(10) << "Start" 
        << setw(10) << "Turnaround " 
        << setw(10) << "Waiting" << endl;

    for (auto& p : processes) {
        totalWaiting += p.waiting;
        totalFinish += p.finish;
        cout << left 
            << setw(11) << p.pid 
            << setw(11) << p.arrival 
            << setw(11) << p.burst 
            << setw(11) << p.start 
            << setw(11) << p.finish - p.arrival 
            << setw(11) << p.waiting << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time   : " << totalWaiting / processes.size() << endl;
    cout << "Average Finishing Time : " << totalFinish / processes.size() << endl;

    return 0;
}
