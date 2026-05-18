#pragma once
#include <map>
#include <queue>
#include <vector>
#include <utility>
#include <functional>
#include "unidirected_graph.hpp"

template<typename T>
UnidirectedGraph<T> dijkstra(const UnidirectedGraph<T>& g, const T& nodo_sorgente, const T& nodo_arrivo) {
    UnidirectedGraph<T> albero_risultante;
    std::map<T, int> dist;  // distanza minima nota da sorgente (chiave assente = non ancora raggiunto)
    std::map<T, T> pred; // predecessore nel cammino minimo

    pred[nodo_sorgente] = nodo_sorgente;  // convenzione: pred[s] = s
    dist[nodo_sorgente] = 0;

    // Min-heap di coppie (distanza, nodo)
    using Entry = std::pair<int, T>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> PQ;
    PQ.push({0, nodo_sorgente});

    while (!PQ.empty()) {
        auto [p, u] = PQ.top();
        PQ.pop();

        // Entry obsoleta (priority_queue non supporta DecreaseKey, lasciamo i duplicati e li scartiamo qui)
        if (p > dist[u]) continue;

        // Rilassamento dei vicini di u
        for (const auto& w : g.neighbours(u)) {
            int peso = 1;  // grafo senza pesi
            int nuova_dist = dist[u] + peso;
            // w mai raggiunto -> equivale a distanza infinita -> rilassa sempre
            if (!dist.contains(w) || nuova_dist < dist[w]) {
                dist[w] = nuova_dist;
                pred[w] = u;
                PQ.push({nuova_dist, w});
            }
        }
    }

    if (!pred.contains(nodo_arrivo)) return albero_risultante;

    // Ricostruzione del path da arrivo a sorgente seguendo pred
    T cur = nodo_arrivo;
    while (cur != nodo_sorgente) {
        T p = pred.at(cur);
        albero_risultante.add_edge(p, cur);
        cur = p;
    }

    return albero_risultante;
}
