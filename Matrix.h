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
	class Proxy;
	void detachPointer();
	void destroyData();
public:
	rcm *data;
	Matrix();
	Matrix(const Matrix &m);
	Matrix(size_t rows, size_t columns, double filling = 0);
	~Matrix();
	void operator= (const Matrix &m);
	Proxy operator() (size_t r, size_t c);
	Matrix operator- () const;
	Matrix & operator+= (const Matrix &m);
	Matrix & operator-= (const Matrix &m);
	Matrix & operator*= (const Matrix &m);
	Matrix operator+ (const Matrix &m) const;
	Matrix operator- (const Matrix &m) const;
	Matrix operator* (const Matrix &m) const;
	bool operator== (const Matrix &m) const;
	bool operator!= (const Matrix &m) const;
	friend ostream & operator<< (ostream &s, const Matrix &m);
	friend istream & operator>> (istream &in, Matrix &m);
};

struct Matrix::rcm{
	double **matrix;
	size_t rows_no, columns_no;
	unsigned int references;
	rcm(size_t rows, size_t columns, double filling = 0);
	rcm(size_t rows, size_t columns, double** data);
	~rcm();
};

class Matrix::Proxy{
private:
	//friend class Matrix;
	Matrix& m;
	size_t row, column;
public:
	Proxy(Matrix& mat, size_t r, size_t c): m(mat), column(c), row(r) {}
	operator double() const;
	Proxy& operator=(double n);
	Proxy& operator=(const Proxy&);
};


class DifferentSizesException : public exception { };

class AdditionDifferentSizesException : public DifferentSizesException {
	string msg;
public:
	AdditionDifferentSizesException(size_t r1, size_t c1, size_t r2, size_t c2) {
		msg = ">>>>>>>ERROR<<<<<<<\nUnable to add matrices: both matrices must have equal sizes.\nCurrent sizes are (rows x columns): " +
					 to_string(r1) + "x" + to_string(c1) + " and " + to_string(r2) + "x" + to_string(c2) + "\n";
	}
	const char* what() const noexcept override{
		return msg.c_str();
	}
};

class MultiplicationDifferentSizesException : public DifferentSizesException {
	string msg;
public:
	MultiplicationDifferentSizesException(size_t r1, size_t c1, size_t r2, size_t c2) {
		msg = ">>>>>>>ERROR<<<<<<<\nUnable to multiply matrices: first matrix's COLUMNS NUMBER(" + to_string(c1) +
				") must be equal to the second matrix's ROWS NUMBER(" + to_string(r2) + ")\nCurrent sizes are (rows x columns): "
				+ to_string(r1) + "x" + to_string(c1) + " and " + to_string(r2) + "x" + to_string(c2) + "\n";
	}
	const char* what() const noexcept override {
		return msg.c_str();
	}
};

class WrongDoubleInputException : public exception {
public:
	const char* what() const noexcept override {
		return ">>>>>>>ERROR<<<<<<<\nImproper input type: input should be of type double\n";
	}
};

class WrongIntInputException : public exception {
public:
	const char* what() const noexcept override {
		return ">>>>>>>ERROR<<<<<<<\nImproper input type: input should be of type int\n";
	}
};
#endif //MATRIXAGAIN_MATRIX_H
