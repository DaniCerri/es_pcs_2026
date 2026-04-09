#pragma once
#include <optional>
#include <vector>

// Verifica se un vettore e' ordinato in modo crescente.
// Un vettore vuoto e' considerato ordinato per definizione
// (il ciclo non viene eseguito e si ritorna true)
template <typename T>
bool is_sorted(const std::vector<T>& a) {
    for (size_t i=1; i<a.size(); i++) {  // partiamo da 1 per evitare underflow su vettore vuoto
        if (a[i] < a[i-1]) {
            return false;
        }
    }
    return true;
}






