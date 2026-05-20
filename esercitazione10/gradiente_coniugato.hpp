#pragma once
#include <Eigen/Dense>
#include <iostream>
using namespace std;



void gradiente_coniugato(
    const Eigen::MatrixXd& A,
    const Eigen::VectorXd& b,
    Eigen::VectorXd& x,
    const double r_tol
) {
    Eigen::VectorXd r = b - A * x;  // Residuo al passo 0
    Eigen::VectorXd p = r;          // Direzione di ricerca al passo 0
    
    unsigned int k = 0;

    while(r.norm() > r_tol) {
        const double alpha_k = (p.transpose() * r).value() / (p.transpose() * A * p).value();
        x += alpha_k * p;
        r = b - A * x;
        const double beta_k = (p.transpose() * A * r).value() / (p.transpose() * A * p).value();
        p = r - beta_k * p;
        k++;
    }

    cout << "Numero di iterazioni: " << k << endl; 
}
