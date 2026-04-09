#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "algos.hpp"
#include "utils.hpp"
#include "randfiller.h"

#define NUM_TESTS 100  // numero di test da eseguire

int main() {
    randfiller rf;

    // genero tutte le dimensioni casuali in un colpo solo
    std::vector<int> dims(NUM_TESTS);
    rf.fill(dims, 1, 200);

    // test su 100 vettori di dimensioni diverse con numeri negativi e positivi
    for (int t = 0; t < NUM_TESTS; t++) {
        int n = dims[t];

        std::vector<int> v(n);
        rf.fill(v, -1000, 1000);  // riempiamo con numeri tra -1000 e 1000
        insertion_sort(v);
        if (!is_sorted(v)) {  // verifichiamo che il vettore sia effettivamente ordinato
            std::cerr << "FAIL: test random #" << t << " (n=" << n << ")\n";
            return EXIT_FAILURE;
        }
    }

    // test su vettore di stringhe per verificare che il template funzioni anche con std::string
    std::vector<std::string> vs = {
        "lorem", "ipsum", "dolor", "sit", "amet",
        "consectetur", "adipiscing", "elit", "sed", "do"
    };
    insertion_sort(vs);
    if (!is_sorted(vs)) {
        std::cerr << "FAIL: test stringhe\n";
        return EXIT_FAILURE;
    }

    std::cout << "insertion_sort: tutti i test passati\n";
    return EXIT_SUCCESS;
}
