#pragma once
#include <vector>

// Bubble sort: gli elementi "pesanti" scendono a fondo come bolle
template <typename T>
void bubble_sort(std::vector<T>& a) {
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = a.size() - 1; j > i; j--) {
            if (a[j] < a[j-1]) {
                T tmp = a[j]; a[j] = a[j-1]; a[j-1] = tmp;
            }
        }
    }
}

// Insertion sort: ad ogni passo inseriamo l'elemento corrente nella parte gia' ordinata
template <typename T>
void insertion_sort(std::vector<T>& a) {
    for (int j = 1; j < (int)a.size(); j++) {
        T key = a[j];
        int i = j - 1;
        while (i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}

// Variante su una fetta [low..high], usata dal quicksort ibrido
template <typename T>
void insertion_sort_range(std::vector<T>& a, int low, int high) {
    for (int j = low + 1; j <= high; j++) {
        T key = a[j];
        int i = j - 1;
        while (i >= low && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}

// Selection sort: troviamo il minimo nella parte non ordinata e lo portiamo a sinistra
template <typename T>
void selection_sort(std::vector<T>& a) {
    for (size_t i = 0; i < a.size(); i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < a.size(); j++) {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        T tmp = a[i]; a[i] = a[min_idx]; a[min_idx] = tmp;
    }
}
