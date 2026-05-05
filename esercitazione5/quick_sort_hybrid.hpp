#pragma once
#include <vector>
#include "quick_sort.hpp"
#include "algos.hpp"

#define HYBRID_THRESHOLD 32  // sotto questa dimensione conviene insertion_sort

template <typename T>
void quick_sort_hybrid(std::vector<T>& a, int low, int high) {
    if (low < high) {
        if (high - low + 1 <= HYBRID_THRESHOLD) {
            insertion_sort_range(a, low, high);
            return;
        }
        int p = partition(a, low, high);
        quick_sort_hybrid(a, low, p - 1);
        quick_sort_hybrid(a, p + 1, high);
    }
}
