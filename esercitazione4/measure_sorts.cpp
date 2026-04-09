#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "algos.hpp"
#include "randfiller.h"
#include "timecounter.h"

int main() {
    randfiller rf(42);  // seed fisso per avere risultati riproducibili
    timecounter tc;

    // dimensioni richieste: potenze di 2 da 4 a 8192
    for (int n = 4; n <= 8192; n *= 2) {
        // creiamo un vettore base con numeri casuali, inclusi negativi
        std::vector<int> base(n);
        rf.fill(base, -1000, 1000);

        // per ogni algoritmo copiamo il vettore base cosi' partiamo tutti dallo stesso input

        // Bubble sort
        std::vector<int> v1 = base;
        tc.tic();
        bubble_sort(v1);
        double t1 = tc.toc();
        std::cout << "bubble_sort, n=" << n << ": " << t1 << " s\n";

        // Insertion sort
        std::vector<int> v2 = base;
        tc.tic();
        insertion_sort(v2);
        double t2 = tc.toc();
        std::cout << "insertion_sort, n=" << n << ": " << t2 << " s\n";

        // Selection sort
        std::vector<int> v3 = base;
        tc.tic();
        selection_sort(v3);
        double t3 = tc.toc();
        std::cout << "selection_sort, n=" << n << ": " << t3 << " s\n";

        // std::sort della libreria standard per confronto
        std::vector<int> v4 = base;
        tc.tic();
        std::sort(v4.begin(), v4.end());
        double t4 = tc.toc();
        std::cout << "std::sort, n=" << n << ": " << t4 << " s\n";

        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}
