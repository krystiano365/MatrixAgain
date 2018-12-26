//
// Created by krystian on 26.12.18.
//

#ifndef MATRIXAGAIN_MATRIX_H
#define MATRIXAGAIN_MATRIX_H


#include <iostream>
#include <cstddef>


using namespace std;

class Matrix {
	struct rcm;
private:
	rcm *data;
public:
	friend ostream &operator<< (ostream &s, const Matrix &m);
};
//			 Y
//			 |
//		X-->[0][1][2][3][4][5][6][7]
//			 |  |  |  |  |  |  |  |
//			[0][0][ ][ ][ ][ ][ ][ ]
//			[1][1][ ][ ][ ][ ][ ][ ]
//			[2][2][ ][ ][ ][ ][ ][ ]
//			[3][3][ ][ ][ ][ ][ ][ ]
//			[4][4][ ][ ][ ][ ][ ][ ]
//

struct Matrix::rcm{
private:
	double **matrix;
	size_t sizeX, sizeY;
	unsigned int references;
public:
	rcm(size_t width, size_t height) : sizeX(width), sizeY(height){
		references = 1;
		matrix = new double*[sizeX];
		for(size_t x = 0; x < sizeX; x++) {
			matrix[x] = new double[sizeY];
			for (size_t y = 0; y < sizeY; y++)
				matrix[x][y] = 0;
		}
	};

	rcm(size_t width, size_t height, double** data) : sizeX(width), sizeY(height){
		references = 1;
		matrix = new double*[sizeX];
		for(size_t x = 0; x < sizeX; x++) {
			matrix[x] = new double[sizeY];
			for (size_t y = 0; y < sizeY; y++)
				matrix[x][y] = data[x][y];
		}
	};

	~rcm(){
		for(size_t i = 0; i < sizeX; i++){
			delete[] matrix[i];
		}
		delete[] matrix;
	};
};


ostream &operator<<(ostream &s, const Matrix &m) {
	if (&(m.array) && m.rows_no > 0 && m.columns_no > 0) {
		for (unsigned int r = 0; r < m.rows_no; r++) {
			s << "[";
			for (unsigned int c = 0; c < m.columns_no; c++) {
				s << " " << m.array[r][c];
			}
			s << " ] r:" << r + 1 << endl;
		}
		s << "c:";
		for (unsigned int c = 1; c <= m.columns_no; c++) s << c % 10 << " ";
		s << endl;
		return s;
	} else {
		s << "[none]"  << endl;
		return s;
	}
}
#endif //MATRIXAGAIN_MATRIX_H
