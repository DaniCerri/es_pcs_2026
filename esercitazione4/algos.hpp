#pragma once
#include <vector>

// Bubble sort: ad ogni iterazione gli elementi "pesanti" scendono verso il fondo
// scambiandosi con i vicini, come bolle che salgono
template <typename T>
void bubble_sort(std::vector<T>& a) {
    for (size_t i=0; i<a.size(); i++) {
        for (size_t j=a.size()-1; j>i; j--) {  // partiamo dal fondo e risaliamo
            if (a[j] < a[j-1]) {
                T temp = a[j];  // scambiamo gli elementi adiacenti se sono nell'ordine sbagliato
                a[j] = a[j-1];
                a[j-1] = temp;
            }
        }
    }
};

// Insertion sort: ad ogni passo prendiamo un elemento e lo inseriamo nella
// posizione corretta nella parte gia' ordinata del vettore
template <typename T>
void insertion_sort(std::vector<T>& a) {
    for (int j=1; j<static_cast<int>(a.size()); j++) {  // cast a int perche' i puo' diventare -1
        T key = a[j];  // elemento da inserire
        int i = j - 1;
        while (i >= 0 && a[i] > key) {  // spostiamo gli elementi maggiori di key verso destra
            a[i+1] = a[i];
            i = i - 1;
        }
        a[i+1] = key;  // inseriamo key nella posizione corretta
    }
};

// Selection sort: ad ogni iterazione troviamo il minimo nella parte non ordinata
// e lo scambiamo con il primo elemento non ordinato
template <typename T>
void selection_sort(std::vector<T>& a) {
    for (size_t i=0; i<a.size(); i++) {
        size_t min_idx = i;  // indice del minimo nella parte non ordinata
        for (size_t j=i+1; j<a.size(); j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        T temp = a[i];  // scambiamo il minimo trovato con l'elemento in posizione i
        a[i] = a[min_idx];
        a[min_idx] = temp;
    }
};




