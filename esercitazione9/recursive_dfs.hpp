#pragma once
#include <set>
#include "unidirected_graph.hpp"

template<typename T>
void dfs_visit(const UnidirectedGraph<T>& grafo, const T& u, std::set<T>& reached, UnidirectedGraph<T>& albero_risultante) {
    for (const auto& v : grafo.neighbours(u)){
        if(reached.contains(v)) continue;
        reached.insert(v);
        albero_risultante.add_edge(u, v);
        dfs_visit(grafo, v, reached, albero_risultante);
    }
}

template<typename T>
UnidirectedGraph<T> recursive_dfs(const UnidirectedGraph<T>& g, const T& nodo_sorgente) {    
    UnidirectedGraph<T> albero_risultante;
    std::set<T> reached;
    reached.insert(nodo_sorgente);
    dfs_visit(g, nodo_sorgente, reached, albero_risultante);

    return albero_risultante;

}
