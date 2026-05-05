#pragma once
#include <vector>

// Fonde le due meta' ordinate a[low..mid] e a[mid+1..high]
template <typename T>
void merge(std::vector<T>& a, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    std::vector<T> left(n1), right(n2);
    for (int i = 0; i < n1; i++) left[i] = a[low + i];
    for (int i = 0; i < n2; i++) right[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) a[k++] = left[i++];  // <= mantiene la stabilita'
        else                     a[k++] = right[j++];
    }
    while (i < n1) a[k++] = left[i++];
    while (j < n2) a[k++] = right[j++];
}

// Divide-et-impera: divide, ordina ricorsivamente, fonde
template <typename T>
void merge_sort(std::vector<T>& a, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;  // forma anti-overflow
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}
