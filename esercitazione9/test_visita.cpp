#include <fstream>
#include "unidirected_graph.hpp"
#include "graph_visit.hpp"
#include "recursive_dfs.hpp"
#include "dijkstra.hpp"
#include "queue.hpp"
#include "stack.hpp"

// Funzione per salvare il grafo in un file .dot
template <typename T>
void salva_dot(const UnidirectedGraph<T>& g, const std::string& filename, const std::string& nome) {
    std::ofstream f(filename);
    g.to_dot(f, nome);
    std::cout << "Salvato: " << filename << "\n";
}

int main() {
    UnidirectedGraph<int> g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(1, 6);

    g.add_edge(2, 4);
    g.add_edge(2, 5);
    g.add_edge(2, 7);

    g.add_edge(3, 6);

    g.add_edge(4, 6);
    g.add_edge(4, 7);

    g.add_edge(5, 7);

    g.add_edge(6, 7);
    g.add_edge(6, 8);

    g.add_edge(7, 9);
    g.add_edge(8, 9);

    salva_dot(g, "grafo_originale.dot", "Originale");

    // BFS
    {
        Queue<int> q;
        auto albero_bfs = graph_visit(g, 1, q);
        salva_dot(albero_bfs, "albero_bfs.dot", "BFS");
    }

    // DFS normale
    {
        Stack<int> s;
        auto albero_dfs = graph_visit(g, 1, s);
        salva_dot(albero_dfs, "albero_dfs.dot", "DFS");
    }

    // DFS ricorsivo
    {
        auto albero_recursive_dfs = recursive_dfs(g, 1);
        salva_dot(albero_recursive_dfs, "albero_recursive_dfs.dot", "ricorsivo");
    }

    // Dijkstra
    {
        auto path = dijkstra(g, 1, 9);
        salva_dot(path, "dijkstra_1_9.dot", "Dijkstra_1_9");
    }
    {
        auto path = dijkstra(g, 5, 8);
        salva_dot(path, "dijkstra_5_8.dot", "Dijkstra_5_8");
    }

    return 0;
}
