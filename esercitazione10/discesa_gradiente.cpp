#include <iostream>
#include <cmath>
#include <iomanip>
#include "Eigen/Eigen"
using namespace std;

void print_matrix(const Eigen::MatrixXd &M) {
  for(int i = 0; i < M.rows(); i++) {
    for(int j = 0; j < M.cols(); j++) {
      cout << setw(8) << fixed << setprecision(3) << M(i, j) << " ";
    }
    cout << endl;
  }
}

int main(int argc, char **argv) 
{
  const double tol = 1.0e-15; // Tolleranza per il determinante
  const unsigned int n = 10;  // Dimensione della matrice

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n); // Facciamo una matrice n x n con valori casuali
  if (fabs(B.determinant()) < tol) { // Se la matrice è singolare, usciamo
    cout << "Matrice non invertibile" << endl;
    return -1;
  } 
  
  Eigen::MatrixXd A = B.transpose() * B; // Matrice simmetrica definita positiva
  print_matrix(A);
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);  // Esempio di vettore
  Eigen::VectorXd b = A * x_ex;                     // Vettore risultante da b = A * x_ex
  
  /* Inizializzazione per algoritmo del gradiente */ 
  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);  // Vettore soluzione iniziale
  Eigen::VectorXd res = b - A * x;  // Residuo al passo 0
  double res_norm_0 = res.norm();

  const unsigned int it_max = 10000;  // Massimo numero di iterazioni 
  unsigned int it = 0;  
  const double res_tol = 1.0e-12;  // Tolleranza per il residuo
  
  cout << "Iniziamo a calcolare la soluzione: " << endl; 
  // finchè non raggiungo il numero massimo di iterazioni o il residuo non è abbastanza piccolo
  while(it < it_max && res.norm() > res_tol * res_norm_0) {  
    const double alpha_k = (res.transpose() * res).value() / (res.transpose() * A * res).value();
    x += alpha_k * res;
    res -= alpha_k * A * res;
    it++;  
  }

  const double err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() : (x - x_ex).norm() / x_ex.norm();

  cout << "Iterazioni: " << it << "/" << it_max << endl;
  cout << "Residuo: " << scientific << res.norm() << "/" << scientific << res_tol * res_norm_0 << endl;
  cout << "Errore relativo: " << scientific << err_rel << endl; 
  cout << "Soluzione approssimata: " << scientific << endl; 
  cout << x << endl; 


  return 0; 
}
