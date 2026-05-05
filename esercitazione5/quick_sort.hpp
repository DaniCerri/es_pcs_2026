#pragma once
#include <vector>

template <typename T>
int partition(std::vector<T>& a, int low, int high) {
    T x = a[high];  // pivot: ultimo elemento della fetta
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] <= x) {
            i++;
            T tmp = a[i]; a[i] = a[j]; a[j] = tmp;
        }
    }
    T tmp = a[i+1]; a[i+1] = a[high]; a[high] = tmp;
    return i + 1;
}

// Divide-et-impera in-place
template <typename T>
void quick_sort(std::vector<T>& a, int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quick_sort(a, low, p - 1);
        quick_sort(a, p + 1, high);
    }
}
