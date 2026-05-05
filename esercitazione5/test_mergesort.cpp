#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "merge_sort.hpp"
#include "utils.hpp"
#include "randfiller.h"

#define NUM_TESTS 100

int main() {
    randfiller rf;

    std::vector<int> dims(NUM_TESTS);
    rf.fill(dims, 1, 200);

    // test su vettori di dimensioni diverse con numeri negativi e positivi
    for (int t = 0; t < NUM_TESTS; t++) {
        std::vector<double> v(dims[t]);
        rf.fill(v, -100.0, 100.0);
        merge_sort(v, 0, (int)v.size() - 1);
        if (!is_sorted(v)) {
            std::cerr << "FAIL: test random #" << t << " (n=" << dims[t] << ")\n";
            return EXIT_FAILURE;
        }
    }

    // test su vettore di stringhe
    std::vector<std::string> vs = {
        "lorem", "ipsum", "dolor", "sit", "amet",
        "consectetur", "adipiscing", "elit", "sed", "do"
    };
    merge_sort(vs, 0, (int)vs.size() - 1);
    if (!is_sorted(vs)) {
        std::cerr << "FAIL: test stringhe\n";
        return EXIT_FAILURE;
    }

    std::cout << "merge_sort: tutti i test passati\n";
    return EXIT_SUCCESS;
}
