#include <iostream>
#include "Matrix.h"

using namespace std;


int main() {
//	Matrix m(3, 5, 7);   // 3x5 matrix ---> 3 rows 5 columns
	Matrix m2(3, 4, 3);
//	cout << "m: \n" << m.data << endl << m << endl;
//	cout << "m2: \n" << m2.data << endl << m2 << endl;
	Matrix m;

	//m2 = m;
//	cout << "m: \n" << m.data << endl << m << endl;
	//cout << "m2: \n" << m2.data << endl << m2 << endl;

	try {
//		cin >> m;
//		Matrix m3 = m + m2;
//		cout << "m: \n" << m.data << endl << m << endl;
//		cout << "m2: \n" << m2.data << endl << m2 << endl;
//		cout << "m3: \n" << m3.data << endl << m3 << endl;
		cout << "m2(2,3): " << m2(2, 3) << endl << endl;

	} catch (exception &e){
		cout << e.what();
	}

	return 0;
}