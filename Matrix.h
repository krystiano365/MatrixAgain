//
// Created by krystian on 26.12.18.
//

#ifndef MATRIXAGAIN_MATRIX_H
#define MATRIXAGAIN_MATRIX_H


#include <iostream>
#include <cstddef>


using namespace std;

class Matrix {
private:
	struct rcm;
	rcm *data;
public:
	Matrix(size_t rows, size_t columns);
	~Matrix();
	friend ostream & operator<< (ostream &s, const Matrix &m);
};


#endif //MATRIXAGAIN_MATRIX_H
