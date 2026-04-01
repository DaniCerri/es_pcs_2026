#include <iostream>
#include "rational.hpp"

using namespace std;

int main() {
    Rational<int> a(1, 2);   // 1/2
    Rational<int> b(2, 3);   // 2/3
    Rational<int> c(-3, 4);  // -3/4

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    cout << "\na + b = " << a + b << endl;
    cout << "a - c = " << a - c << endl;
    cout << "b * c = " << b * c << endl;
    cout << "a / b = " << a / b << endl;

    cout << "\na + b + c = " << a + b + c << endl;
    cout << "a * b * c = " << a * b * c << endl;

    return 0;
}
