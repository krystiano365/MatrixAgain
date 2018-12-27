//
// Created by krystian on 26.12.18.
//

#include "Matrix.h"

struct Matrix::rcm{

	double **matrix;
	size_t rows_no, columns_no;
	unsigned int references;

	rcm(size_t rows, size_t columns) : columns_no(columns), rows_no(rows){
		references = 1;
		matrix = new double*[rows_no];
		for(size_t r = 0; r < rows_no; r++) {
			matrix[r] = new double[columns_no];
			for (size_t c = 0; c < columns_no; c++)
				matrix[r][c] = 0;
		}
	};

	rcm(size_t rows, size_t columns, double** data) : columns_no(columns), rows_no(rows){
		references = 1;
		matrix = new double*[rows_no];
		for(size_t r = 0; r < rows_no; r++) {
			matrix[r] = new double[columns_no];
			for (size_t c = 0; c < columns_no; c++)
				matrix[r][c] = data[r][c];
		}
	};

	~rcm(){
		for(size_t r = 0; r < rows_no; r++){
			delete[] matrix[r];
		}
		delete[] matrix;
	};
};

Matrix::Matrix(size_t rows, size_t columns) {
	data = new rcm(rows, columns);
}

Matrix::~Matrix() {
	if(data != nullptr) {

		data->references--;

		if(data->references == 0){
			delete data;
		} else {
			data = nullptr;
		}
	}
}


ostream & operator<<(ostream &s, const Matrix &m) {
	if (&(m.data->matrix) && m.data->rows_no > 0 && m.data->columns_no > 0) {

		for (unsigned int r = 0; r < m.data->rows_no; r++) {
			s << "[";
			for (unsigned int c = 0; c < m.data->columns_no; c++) {
				s << " " << m.data->matrix[r][c];
			}
			s << " ] r:" << r + 1 << endl;
		}

		s << "c:";

		for (unsigned int c = 1; c <= m.data->columns_no; c++) s << c % 10 << " ";

		s << endl;

		return s;

	} else {
		s << "[none]"  << endl;
		return s;
	}
}
