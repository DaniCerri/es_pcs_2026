// Confronto sui vettori piccoli per stimare la soglia sotto la quale
// gli algoritmi quadratici battono quicksort/mergesort
#include <cstdlib>
#include <iostream>
#include <vector>
#include "algos.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "randfiller.h"
#include "timecounter.h"

#define N_VEC 200

int main() {
    randfiller rf(42);
    timecounter tc;

    int sizes[] = {4, 8, 16, 32, 50, 64, 80, 100, 150, 200};

    std::cout << "size\tbubble\tselect\tinsert\tquick\tmerge\t(microsecondi/vettore)\n";

    for (int sz : sizes) {
        std::vector<std::vector<int>> base(N_VEC, std::vector<int>(sz));
        for (auto& v : base) rf.fill(v, -1000, 1000);

        std::vector<std::vector<int>> v1 = base;
        tc.tic();
        for (auto& v : v1) bubble_sort(v);
        double tb = tc.toc() / N_VEC * 1e6;

        std::vector<std::vector<int>> v2 = base;
        tc.tic();
        for (auto& v : v2) selection_sort(v);
        double ts = tc.toc() / N_VEC * 1e6;

        std::vector<std::vector<int>> v3 = base;
        tc.tic();
        for (auto& v : v3) insertion_sort(v);
        double ti = tc.toc() / N_VEC * 1e6;

        std::vector<std::vector<int>> v4 = base;
        tc.tic();
        for (auto& v : v4) quick_sort(v, 0, (int)v.size() - 1);
        double tq = tc.toc() / N_VEC * 1e6;

        std::vector<std::vector<int>> v5 = base;
        tc.tic();
        for (auto& v : v5) merge_sort(v, 0, (int)v.size() - 1);
        double tm = tc.toc() / N_VEC * 1e6;

        std::cout << sz << "\t" << tb << "\t" << ts << "\t" << ti
                  << "\t" << tq << "\t" << tm << "\n";
    }

    return EXIT_SUCCESS;
}
