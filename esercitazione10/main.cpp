#include "gradiente_coniugato.hpp"
#include <iostream>
#include <iomanip>
#include <Eigen/Dense>

using namespace std;

void print_matrix(const Eigen::MatrixXd &M) {
  for(int i = 0; i < M.rows(); i++) {
    for(int j = 0; j < M.cols(); j++) {
      cout << setw(8) << fixed << setprecision(3) << M(i, j) << " ";
    }
    cout << endl;
  }
}

int main() {
    const double tol = 1.0e-15; // Tolleranza per il determinante
    const unsigned int n = 10;  // Dimensione della matrice

    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n); // Facciamo una matrice n x n con valori casuali
    if (fabs(B.determinant()) < tol) { // Se la matrice è singolare, usciamo
        cout << "Matrice non invertibile" << endl;
        return -1;
    } 
  
    Eigen::MatrixXd A = B.transpose() * B; // Matrice simmetrica definita positiva
    print_matrix(A);
    Eigen::VectorXd x_ex = Eigen::VectorXd::Random(n);  // Esempio di vettore da trovare
    // Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);  // Esempio di vettore da trovare
    Eigen::VectorXd b = A * x_ex;                     // Vettore risultante da b = A * x_ex
  
    /* Inizializzazione per algoritmo del gradiente */ 
    Eigen::VectorXd x = Eigen::VectorXd::Zero(n);

    const double res_tol = 1.0e-12;  // Tolleranza per il residuo
    gradiente_coniugato(A, b, x, res_tol);

    cout << "Soluzione approssimata: " << endl; 
    cout << scientific << x << endl;    

    cout << "Errore relativo: " << scientific << (x - x_ex).norm() / x_ex.norm() << endl; 

    return 0;
}