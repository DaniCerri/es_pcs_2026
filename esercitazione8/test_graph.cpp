#include <cstdlib>
#include <iostream>
#include <string>
#include "unidirected_graph.hpp"

int main() {
    {
        UnidirectedGraph<int> g;
        g.add_edge(1, 2);
        g.add_edge(2, 3);
        g.add_edge(3, 1);
        g.add_edge(1, 2); // duplicato

        if (g.all_nodes().size() != 3) {
            return EXIT_FAILURE;
        }
        if (g.all_edges().size() != 3) {
            return EXIT_FAILURE;
        }
    }

    {
        UnidirectedGraph<int> g;
        g.add_edge(1, 2);
        g.add_edge(1, 3);
        g.add_edge(1, 4);
        g.add_edge(2, 3);

        if (g.neighbours(1).size() != 3) {
            return EXIT_FAILURE;
        }
        auto n4 = g.neighbours(4);
        if (n4.size() != 1 || n4.front() != 1) {
            return EXIT_FAILURE;
        }
        if (!g.neighbours(99).empty()) {
            return EXIT_FAILURE;
        }
    }

    {
        UnidirectedGraph<int> g;
        g.add_edge(1, 2);
        g.add_edge(3, 4);
        g.add_edge(5, 6);

        if (g.edge_number(UnidirectedEdge<int>(1, 2)) != 0 ||
            g.edge_number(UnidirectedEdge<int>(3, 4)) != 1 ||
            g.edge_number(UnidirectedEdge<int>(5, 6)) != 2) {
            return EXIT_FAILURE;
        }
        if (!(g.edge_at(0) == UnidirectedEdge<int>(1, 2)) ||
            !(g.edge_at(2) == UnidirectedEdge<int>(5, 6))) {
            return EXIT_FAILURE;
        }
        if (g.edge_number(UnidirectedEdge<int>(7, 8)) != g.all_edges().size()) {
            return EXIT_FAILURE;
        }
    }

    {
        UnidirectedGraph<int> g1;
        g1.add_edge(1, 2);
        g1.add_edge(2, 3);
        g1.add_edge(3, 4);

        UnidirectedGraph<int> g2;
        g2.add_edge(2, 3);
        g2.add_edge(5, 6);

        auto diff = (g1 - g2).all_edges();
        if (diff.size() != 2 ||
            diff.count(UnidirectedEdge<int>(1, 2)) != 1 ||
            diff.count(UnidirectedEdge<int>(3, 4)) != 1 ||
            diff.count(UnidirectedEdge<int>(2, 3)) != 0) {
            return EXIT_FAILURE;
        }
    }

    {
        UnidirectedGraph<int> g1;
        g1.add_edge(1, 2);
        UnidirectedGraph<int> g2(g1);
        g2.add_edge(3, 4);

        if (g1.all_edges().size() != 1 || g2.all_edges().size() != 2) {
            return EXIT_FAILURE;
        }
    }
    {
        UnidirectedGraph<std::string> g;
        g.add_edge("alice", "bob");
        g.add_edge("bob", "carl");

        if (g.neighbours("bob").size() != 2) {
            return EXIT_FAILURE;
        }
        if (g.all_nodes().size() != 3) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
