//
// Created by krystian on 26.12.18.
//

#include "Matrix.h"

//  class Matrix  ->  rcm *data  ->  double matrix[][]
//
//
//====================================================================================================================== MEMBER CLASSES


Matrix::rcm::rcm(size_t rows, size_t columns, double filling) : columns_no(columns), rows_no(rows){
	references = 1;
	matrix = new double*[rows_no];
	for(size_t r = 0; r < rows_no; r++) {
		matrix[r] = new double[columns_no];
		for (size_t c = 0; c < columns_no; c++)
			matrix[r][c] = filling;
	}
};

Matrix::rcm::rcm(size_t rows, size_t columns, double** data) : columns_no(columns), rows_no(rows){
	references = 1;
	matrix = new double*[rows_no];
	for(size_t r = 0; r < rows_no; r++) {
		matrix[r] = new double[columns_no];
		for (size_t c = 0; c < columns_no; c++)
			matrix[r][c] = data[r][c];
	}
};

Matrix::rcm::~rcm(){
	for(size_t r = 0; r < rows_no; r++){
		delete[] matrix[r];
	}
	delete[] matrix;

};

Matrix::Proxy::operator double() const
{
	return m.data->matrix[row][column];
}

Matrix::Proxy & Matrix::Proxy::operator=(double n) {
	m.detachPointer();
	m.data->matrix[row][column] = n;
	return *this;
}

Matrix::Proxy & Matrix::Proxy::operator=(const Matrix::Proxy& reference) {
	return operator=((double)reference);
}

//====================================================================================================================== MEMBER CLASSES
//----------------------------------------------------------------------------------------------------------------------
//====================================================================================================================== PRIVATE METHODS

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

//====================================================================================================================== PRIVATE METHODS
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
		cout<< "destructor called"<< endl;
		destroyData();
	}
}

//====================================================================================================================== CONSTRUCTORS
//----------------------------------------------------------------------------------------------------------------------
//====================================================================================================================== PUBLIC METHODS

Matrix Matrix::operator-() const{
	if(data != nullptr) {
		Matrix aux (this->data->rows_no, this->data->columns_no);
		for (size_t r = 0; r < this->data->rows_no; r++) {
			for (size_t c = 0; c < this->data->columns_no; c++) {
				aux.data->matrix[r][c] = -(this->data->matrix[r][c]);
			}
		}
		return aux;
	}
	return *this;
}

void Matrix::operator=(const Matrix &m) {

	if(this->data != nullptr){
		this->data->references--;
		destroyData();
	}

	this->data = m.data;
	m.data->references++;
}

Matrix::Proxy Matrix::operator()(size_t r, size_t c) {
	return Proxy(*this, r, c);
}

Matrix &Matrix::operator+=(const Matrix &m) {

	if(data && m.data) {
		if (this->data->rows_no == m.data->rows_no && this->data->columns_no == m.data->columns_no){

			this->detachPointer();

			for(size_t r = 0; r < this->data->rows_no; r++){
				for(size_t c = 0; c < this->data->columns_no; c++){
					this->data->matrix[r][c] += m.data->matrix[r][c];
				}
			}

			return *this;
		} else {
			throw AdditionDifferentSizesException(this->data->rows_no,
					this->data->columns_no,
					m.data->rows_no,
					m.data->columns_no);
		}
	}
	return *this;
}

Matrix &Matrix::operator-=(const Matrix &m) {
	Matrix aux(-m);
	*this += aux;
	return *this;
}

Matrix &Matrix::operator*=(const Matrix &m) {
	if (this->data && m.data) {
		if (this->data->columns_no == m.data->rows_no) {

			this->detachPointer();

			size_t rows, columns;
			if (this->data->columns_no != 0) {
				rows = this->data->rows_no;
				columns = m.data->columns_no;
			} else {
				rows = columns = 0;
			}
			Matrix result(rows, columns);
			for (unsigned int k = 0; k < rows; k++) {
				for (unsigned int j = 0; j < columns; j++) {
					for (unsigned int i = 0; i < this->data->columns_no; i++) {
						result.data->matrix[k][j] += (this->data->matrix[k][i] * m.data->matrix[i][j]);
					}
				}
			}
			*this = result;
		} else {
			throw MultiplicationDifferentSizesException(data->rows_no, data->columns_no, m.data->rows_no,
														m.data->columns_no);
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix &m) const{
	Matrix newMat(*this);
	newMat += m;
	return Matrix(newMat);
}

Matrix Matrix::operator-(const Matrix &m) const{
	Matrix newMat(*this);
	newMat -= m;
	return Matrix(newMat);
}

Matrix Matrix::operator*(const Matrix &m) const{
	Matrix newMat(*this);
	newMat *= m;
	return Matrix(newMat);
}

bool Matrix::operator==(const Matrix &m) const {
	if (this->data && m.data) {
		if (this->data == m.data) {
			return true;
		} else if(this->data->rows_no == m.data->rows_no && this->data->columns_no == m.data->columns_no) {
			for (size_t r = 0; r < this->data->rows_no; r++) {
				for (size_t c = 0; c < this->data->columns_no; c++) {
					if (this->data->matrix[r][c] != m.data->matrix[r][c]) {
						return false;
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool Matrix::operator!=(const Matrix &m) const {
	return !(*this == m);
}


//====================================================================================================================== PUBLIC METHODS
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

istream &operator>> (istream &in, Matrix &m) {
	size_t rows = 0, columns = 0;
	if (m.data == nullptr) {
		if (&in == &cin) {
			cout << "Input number of rows: \n";
			if (!(in >> rows))
				throw WrongIntInputException();

			cout << "Input number of columns: \n";
			if (!(in >> columns))
				throw WrongIntInputException();

			m.data = new Matrix::rcm(rows, columns);
		}
	} else {
		rows = m.data->rows_no;
		columns = m.data->columns_no;
	}

	if (&in == &cin){
		for (size_t r = 0; r < rows; r++) {
			for (size_t c = 0; c < columns; c++) {

				cout << "Input matrix value at (" << r+1 << ", " << c+1 << ") <rows, columns>" << endl;
				if (!(in >> m.data->matrix[r][c]))
					throw WrongDoubleInputException();
			}
		}
	}
	return in;
}



//====================================================================================================================== FRIEND FUNCTIONS
//======================================================================================================================
//====================================================================================================================== END