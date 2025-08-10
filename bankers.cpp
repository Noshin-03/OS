#include <iostream>
using namespace std;

int main() {
    int n = 5; 
    int m = 3; 

    int alloc[10][10] = {
        {0, 1, 0},  
        {2, 0, 0},  
        {3, 0, 2},  
        {2, 1, 1},  
        {0, 0, 2}   
    };

    int maxNeed[10][10] = {
        {7, 5, 3},  
        {3, 2, 2},  
        {9, 0, 2},  
        {2, 2, 2},  
        {4, 3, 3}   
    };

    int avail[10] = {3, 3, 2};

    int need[10][10];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxNeed[i][j] - alloc[i][j];
        }
    }

    bool finish[10] = {false};
    int safeSeq[10], work[10];
    for (int j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[p][j];
                    }
                    
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "\nSystem is NOT in a safe state.\n";
            return 0;
        }
    }

    cout << "\nSystem is in a SAFE state.\nSafe sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
