#include <iostream>
#include <fstream>

using namespace std;

double mean(double t1, double t2, double t3, double t4) {
    return (t1 + t2 + t3 + t4) / 4.0;
}


int main(int argc, char* argv[]) {
    double t1, t2, t3, t4;  // variabili in cui tenere la temperatura
    string citta;           // stringa in cui tenere la citta

    if (argc - 1 != 1) {  // controlliamo che ci sia esattamente un parametro, altrimenti diamo errore
        cerr << "Bisogna passare esattamente un parametro <percorso/file.txt>" << endl;
        return -1;
    } 

    ifstream filein(argv[1]);  // file in input

    if (!filein) {  // controlliamo che il file di lettura sia stato aperto correttamente
        cerr << "Errore nell'apertura del file" << argv[1] << endl;
        return -1;
    }

    while(filein >> citta >> t1 >> t2 >> t3 >> t4) {  // per ogni riga del file, finchè non finiscono
        cout << citta << ": " << mean(t1, t2, t3, t4) << endl;  // stampiamo la città e la media delle temperature
    }

    return 0;
}