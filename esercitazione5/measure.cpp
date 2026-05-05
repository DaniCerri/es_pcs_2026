#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "quick_sort_hybrid.hpp"
#include "randfiller.h"
#include "timecounter.h"

#define N_VEC  100
#define N_SIZE 100000

int main() {
    randfiller rf(42);  // seed fisso per risultati riproducibili
    timecounter tc;

    // preallocazione: niente alloc/fill dentro le misure
    std::vector<std::vector<int>> base(N_VEC, std::vector<int>(N_SIZE));
    for (auto& v : base) rf.fill(v, -1000, 1000);

    // merge_sort
    std::vector<std::vector<int>> v1 = base;
    tc.tic();
    for (auto& v : v1) merge_sort(v, 0, (int)v.size() - 1);
    double t_merge = tc.toc();

    // quick_sort
    std::vector<std::vector<int>> v2 = base;
    tc.tic();
    for (auto& v : v2) quick_sort(v, 0, (int)v.size() - 1);
    double t_quick = tc.toc();

    // quick_sort ibrido
    std::vector<std::vector<int>> v3 = base;
    tc.tic();
    for (auto& v : v3) quick_sort_hybrid(v, 0, (int)v.size() - 1);
    double t_hybrid = tc.toc();

    // std::sort della libreria standard
    std::vector<std::vector<int>> v4 = base;
    tc.tic();
    for (auto& v : v4) std::sort(v.begin(), v.end());
    double t_std = tc.toc();

    std::cout << "Tempo medio per vettore (" << N_VEC << " vettori da " << N_SIZE << " elementi):\n";
    std::cout << "  merge_sort:        " << t_merge  / N_VEC << " s\n";
    std::cout << "  quick_sort:        " << t_quick  / N_VEC << " s\n";
    std::cout << "  quick_sort_hybrid: " << t_hybrid / N_VEC << " s\n";
    std::cout << "  std::sort:         " << t_std    / N_VEC << " s\n";

    return EXIT_SUCCESS;
}
