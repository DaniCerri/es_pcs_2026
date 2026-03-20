#include <iostream>

int main()
{
    double ad[4] = {0.0, 1.1, 2.2, 3.3};
    float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    int ai[3] = {0, 1, 2};

    int x = 1;
    float y = 1.1;

    // Stampa di alcuni indirizzi
    std::cout << "Indirizzo di x: " << &x << "\n";
    std::cout << "Indirizzo di y: " << &y << "\n";
    std::cout << "Indirizzo di ad[3]: " << &ad[3] << "\n";
    std::cout << "Indirizzo di af[7]: " << &af[7] << "\n";
    std::cout << "Indirizzo di ai[1]: " << &ai[1] << "\n";


    
    (&y)[1] = 0; // questa riga causa un buffer overflow, infatti y è un float e non ha un secondo elemento, ma viene trattato come un array di float
    // Nota: il valore di x cambia in 0 a causa del buffer overflow ma solamente con clang, non con g++




    std::cout << x << "\n";

    return 0;
}
