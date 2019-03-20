#ifndef __MATRIX_ADP_1_H__
#define __MATRIX_ADP_1_H__

#include <iostream>
#include <sstream>

template <typename T>
class Matrix {
private:
	const int ZEILEN, SPALTEN;
	T * data;

public:
	Matrix<T>(int zeilen, int spalten);
	Matrix<T>(const Matrix<T> &);
	~Matrix<T>();
	Matrix<T> & init();
	Matrix<T> & print();
	Matrix<T> & input();
	Matrix<T> add(const Matrix<T> & that) { return *this + that; }
	Matrix<T> & mult(const Matrix<T> & factor, Matrix<T> & result); 
	Matrix<T> & operator+= (const Matrix<T> & that); 
	Matrix<T> operator+ (const Matrix<T> & that); 
};

template <typename T>
Matrix<T>::Matrix<T>(int zeilen, int spalten) : ZEILEN(zeilen), SPALTEN(spalten) {
	this->data = new T[zeilen * spalten];
	this->init(); 
}

template <typename T>
Matrix<T>::Matrix<T>(const Matrix<T> & that) : ZEILEN(that.ZEILEN), SPALTEN(that.SPALTEN) {
	this->data = new T[that.ZEILEN * that.SPALTEN];
}


template <typename T>
Matrix<T>::~Matrix<T>() {
	delete[] this->data;
	this->data = nullptr;
}

template <typename T>
Matrix<T> & Matrix<T>::init() {
	for (int i = 0; i < this->ZEILEN; i++) {
		for (int j = 0; j < this->SPALTEN; j++) {
			this->data[i * this->SPALTEN + j] = 0;
		}
	}
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::print() {
	for (int i = 0; i < this->ZEILEN; i++) {
		for (int j = 0; j < this->SPALTEN; j++) {
			std::cout << this->data[i * this->SPALTEN + j] << "  ";
		}
		std::cout << std::endl;
	}
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::input() {
	for (int i = 0; i < this->ZEILEN; i++) {
		for (int j = 0; j < this->SPALTEN; j++) {
			std::cout << "_(" << i << ", " << j << ") = ";
			std::cin >> this->data[i * this->SPALTEN + j];
		}
	}
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator+=(const Matrix<T> & that) {
	if ((this->ZEILEN != that.ZEILEN) || (this->SPALTEN != that.SPALTEN)) {
		std::ostringstream errortext; 
		errortext << "arithmetic exception: cannot add two different sized matrizes. (" 
			<< this->ZEILEN << " x " << this->SPALTEN << ") + (" 
			<< that.ZEILEN << " x " << that.SPALTEN << ") failed.";
		throw std::exception(errortext.str().c_str());
	}
	int size = this->ZEILEN * this->SPALTEN; 
	for (int i = 0; i < size; i++) {
		this->data[i] += that.data[i]; 
	}
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & that) {
	Matrix<T> result(this->ZEILEN, this->SPALTEN); 
	result += that; 
	return result; 
}


template <typename T>
Matrix<T> & Matrix<T>::mult(const Matrix<T> & factor, Matrix<T> & result) {
	if ((this->SPALTEN != factor.ZEILEN) ||
	    (this->ZEILEN != result.ZEILEN) || 
	    (factor.SPALTEN != result.SPALTEN)) {
		std::ostringstream errortext; 
		errortext << "arithmetic exception: cannot multiply these matrizes. (" 
			<< this->ZEILEN << " x " << this->SPALTEN << ") x (" 
			<< factor.ZEILEN << " x " << factor.SPALTEN << ") = (" 
			<< result.ZEILEN << " x " << result.SPALTEN << ") failed.";
		throw std::exception(errortext.str().c_str()); 
	}
	for (int i = 0; i < this->ZEILEN; i++) {
		for (int j = 0; j < factor.SPALTEN; j++) {
			T accu = 0; 
			for (int k = 0; k < this->SPALTEN; k++) {
				accu += this->data[i * this->SPALTEN + k] * factor.data[k * factor.SPALTEN + j]; 
			}
			result.data[i * factor.SPALTEN + j] = accu; 

		}
	}
	
	return result;
}


#endif