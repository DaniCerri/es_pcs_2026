#include <iostream>

using namespace std;

void bubble_sort(double *a, int n) {
    bool scambiato = true;
    while (scambiato) {
        scambiato = false;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                double temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                scambiato = true;
            }
        }
    }
}

int main() {
    static const int N = 10;
    double arr[N] = {10.0, 2.0, 8.0, 1.0, 5.0, 9.0, 3.0, 4.0, 7.0, 6.0};

    cout << "Array prima dell'ordinamento: \n";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl << endl;

    bubble_sort(arr, N);

    cout << "Array dopo l'ordinamento: \n";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
