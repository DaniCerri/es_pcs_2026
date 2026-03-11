#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Numero di parametri: " << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << "Parametro " << i << " = " << argv[i] << std::endl;
    }
    return 0;
}