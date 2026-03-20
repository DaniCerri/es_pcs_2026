#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

double minimo(double *a, int n) {
    double minimo = a[0];
    for (int i = 1; i < n; i++) {
        minimo = min(minimo, a[i]);
    }
    return minimo;
}

double massimo(double *a, int n) {
    double massimo = a[0];
    for (int i = 1; i < n; i++) {
        massimo = max(massimo, a[i]);
    }
    return massimo;
}

double media(double *a, int n) {
    double media = 0;
    for (int i = 0; i < n; i++) {
        media += a[i];
    }
    return media / n;
}

double std_dev(double *a, int n) {
    double media_valori = media(a, n);
    double totale = 0;
    for (int i = 0; i < n; i++) {
        totale += pow(a[i] - media_valori, 2);
    }
    return sqrt(totale / n);
}

int main() {
    static const int N = 10;
    double arr[N] = {10.0, 2.0, 8.0, 1.0, 5.0, 9.0, 3.0, 4.0, 7.0, 6.0};

    cout << "Minimo dell'array: " << minimo(arr, N) << endl;
    cout << "Massimo dell'array: " << massimo(arr, N) << endl;
    cout << "Media dell'array: " << media(arr, N) << endl;
    cout << "Deviazione standard dell'array: " << std_dev(arr, N) << endl;

    return 0;
}