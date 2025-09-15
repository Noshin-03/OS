#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of multiplications: ";
    cin >> n;

    int A[100], B[100];
    cout << "Enter A array: ";
    for (int i = 0; i < n; i++) cin >> A[i];
    cout << "Enter B array: ";
    for (int i = 0; i < n; i++) cin >> B[i];

    int result[100];
    for (int i = 0; i < n; i++) {
        result[i] = A[i] * B[i];
    }

    cout << "\nFinal Results:\n";
    for (int i = 0; i < n; i++) {
        cout << "A[" << i << "] * B[" << i << "] = " << result[i] << "\n";
    }

    return 0;
}
