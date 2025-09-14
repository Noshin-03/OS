#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

int findOptimal(int frames[], int framesCount, int pages[], int currentIndex, int pagesCount) {
    int pos = -1, farthest = currentIndex;
    for (int i = 0; i < framesCount; i++) {
        int j;
        for (j = currentIndex; j < pagesCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == pagesCount) 
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    ifstream inFile("fifoInput.txt");
    if (!inFile) {
        cout << "Error: input.txt not found!" << endl;
        return 1;
    }

    int framesCount, pagesCount;
    inFile >> framesCount >> pagesCount;

    int pages[200];
    for (int i = 0; i < pagesCount; i++) inFile >> pages[i];
    inFile.close();

    int frames[50];
    for (int i = 0; i < framesCount; i++) frames[i] = -1;

    int pageFaults = 0, pageHits = 0;

    cout << left << setw(8) << "Page";
    for (int i = 0; i < framesCount; i++) cout << "Frame" << i + 1 << setw(8 - 6) << " ";
    cout << "Status\n" << string(40, '-') << endl;

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
            int empty = -1;
            for (int j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }
            if (empty != -1) {
                frames[empty] = page;
            } else {
                int pos = findOptimal(frames, framesCount, pages, i + 1, pagesCount);
                frames[pos] = page;
            }
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
