#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

int main() {
    ifstream inFile("fifoInput.txt");
    if (!inFile) {
        cout << "Error: fifoInput.txt not found!" << endl;
        return 1;
    }

    int framesCount, pagesCount;
    inFile >> framesCount;
    inFile >> pagesCount;

    int pages[200];   
    for (int i = 0; i < pagesCount; i++) {
        inFile >> pages[i];
    }
    inFile.close();

    int frames[50];   
    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
    }

    int pageFaults = 0, pageHits = 0, nextToReplace = 0;

    
    cout << left << setw(8) << "Page";
    for (int i = 0; i < framesCount; i++) {
        cout << "Frame" << i + 1 << setw(8 - 6) << " ";
    }
    cout << "Status" << endl;
    cout << string(40, '-') << endl;

    
    for (int i = 0; i < pagesCount; i++) {
        int page = pages[i];
        bool found = false;

        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == page) {
                found = true;
                break;
            }
        }

        if (found) {
            pageHits++;
        } else {
            frames[nextToReplace] = page;
            nextToReplace = (nextToReplace + 1) % framesCount;
            pageFaults++;
        }
        
        cout << left << setw(8) << page;
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == -1) cout << setw(8) << "-";
            else cout << setw(8) << frames[j];
        }
        if (found) cout << "Page Hit ✅";
        else cout << "Page Fault";
        cout << endl;
    }

    cout << "\nTotal Page Faults = " << pageFaults;
    cout << "\nTotal Page Hits   = " << pageHits << endl;

    return 0;
}
