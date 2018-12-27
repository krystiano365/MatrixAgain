//
// Created by krystian on 26.12.18.
//

#include "Matrix.h"

//  class Matrix  ->  rcm *data  ->  double matrix[][]
//
//
//====================================================================================================================== MEMBER CLASSES

struct Matrix::rcm{

	double **matrix;
	size_t rows_no, columns_no;
	unsigned int references;

	rcm(size_t rows, size_t columns, double filling = 0) : columns_no(columns), rows_no(rows){
		references = 1;
		matrix = new double*[rows_no];
		for(size_t r = 0; r < rows_no; r++) {
			matrix[r] = new double[columns_no];
			for (size_t c = 0; c < columns_no; c++)
				matrix[r][c] = filling;
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

//====================================================================================================================== MEMBER CLASSES
//----------------------------------------------------------------------------------------------------------------------
//====================================================================================================================== CONSTRUCTORS

Matrix::Matrix() {
	data = nullptr;
}

Matrix::Matrix(const Matrix &m) {
	if(m.data != nullptr) {
		this->data = m.data;
		m.data->references++;
		detachPointer();
	}
}

Matrix::Matrix(size_t rows, size_t columns, double filling) {
	data = new rcm(rows, columns, filling);
}

Matrix::~Matrix() {
	if(data != nullptr) {

		data->references--;

		destroyData();
	}
}

//====================================================================================================================== CONSTRUCTORS
//----------------------------------------------------------------------------------------------------------------------
//====================================================================================================================== METHODS

void Matrix::destroyData() {
	if(data->references == 0){
		delete data;
	} else {
		data = nullptr;
	}
}

void Matrix::detachPointer() {
	if(this->data != nullptr){
		if(this->data->references > 1){   //jesli jest wiecej niz jedno odniesienie do tych danych, to
			this->data->references--;	  //zmniejszam ilosc odniesien o 1 i tworze nowa instancje z danymi
			this->data = new rcm(this->data->rows_no, this->data->columns_no, this->data->matrix);
		} // jesli brak odniesien ale licznik references nadal wskazuje, ze istnieje jedno odniesienie, wtedy
		  // zaczyna sprzatac destruktor. Odejmuje 1, sprawdza czy references = 0 i usuwa dane.
	}
}

void Matrix::operator=(const Matrix &m) {

	if(this->data != nullptr){
		this->data->references--;
		destroyData();
	}

	this->data = m.data;
	m.data->references++;
}

//====================================================================================================================== METHODS
//----------------------------------------------------------------------------------------------------------------------
//====================================================================================================================== FRIEND FUNCTIONS


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







//====================================================================================================================== FRIEND FUNCTIONS
//======================================================================================================================
//====================================================================================================================== END