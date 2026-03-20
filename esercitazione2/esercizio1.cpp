#include <iostream>

int main()
{
    double ad[4] = {0.0, 1.1, 2.2, 3.3};
    float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    int ai[3] = {0, 1, 2};

    int x = 1;
    float y = 1.1;

    // Stampa degli indirizzi
    std::cout << "Indirizzo di x: " << &x << "\n";
    std::cout << "Indirizzo di y: " << &y << "\n";
    
    std::cout << "Indirizzi di ad: \n";
    for (int i = 0; i < 4; i++) {
        std::cout << "  * Indirizzo di ad[" << i << "]: " << &ad[i] << "\n";
    }
    std::cout << "\n";

    std::cout << "Indirizzi di af: \n";
    for (int i = 0; i < 8; i++) {
        std::cout << "  * Indirizzo di af[" << i << "]: " << &af[i] << "\n";
    }
    std::cout << "\n";

    std::cout << "Indirizzi di ai: \n";
    for (int i = 0; i < 3; i++) {
        std::cout << "  * Indirizzo di ai[" << i << "]: " << &ai[i] << "\n";
    }
    std::cout << "\n";

    
    (&y)[1] = 0; // questa riga causa un buffer overflow, infatti y è un float e non ha un secondo elemento, ma viene trattato come un array di float
    // Nota: il valore di x cambia in 0 a causa del buffer overflow ma solamente con clang, non con g++

    std::cout << x << "\n";

    return 0;
}
