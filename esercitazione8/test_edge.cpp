#include <cstdlib>
#include <iostream>
#include <sstream>
#include "unidirected_edge.hpp"

int main() {
    {
        UnidirectedEdge<int> e(5, 2);
        if (e.from() != 2 || e.to() != 5) {
            return EXIT_FAILURE;
        }
        UnidirectedEdge<int> e2(2, 5);
        if (e2.from() != 2 || e2.to() != 5) {
            return EXIT_FAILURE;
        }
    }

    {
        UnidirectedEdge<int> a(2, 5);
        UnidirectedEdge<int> b(5, 2);
        UnidirectedEdge<int> c(1, 5);
        if (!(a == b)) {
            return EXIT_FAILURE;
        }
        if (a == c) {
            return EXIT_FAILURE;
        }
    }

    {
        UnidirectedEdge<int> a(1, 2);
        UnidirectedEdge<int> b(1, 3);
        UnidirectedEdge<int> c(2, 3);
        if (!(a < b) || !(b < c) || (c < a)) {
            return EXIT_FAILURE;
        }
    }

    {
        UnidirectedEdge<int> e(3, 1);
        std::ostringstream oss;
        oss << e;
        if (oss.str() != "(1, 3)") {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
