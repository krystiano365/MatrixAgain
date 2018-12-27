#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
	Matrix m(3, 5, 7);   // 3x5 matrix
	Matrix m2(2, 2, 3);
	cout << "m: \n" << m.data << endl << m << endl;
	cout << "m2: \n" << m2.data << endl << m2 << endl;
	m2 = m;
	cout << "m: \n" << m.data << endl << m << endl;
	cout << "m2: \n" << m2.data << endl << m2 << endl;
	return 0;
}