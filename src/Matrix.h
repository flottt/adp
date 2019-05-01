#ifndef __MATRIX_ADP_1_H__
#define __MATRIX_ADP_1_H__

#include <iostream>
#include <sstream>
#include <exception>
#include <iomanip>

#include "adpHelper.h"
#include "MatrixMultipliziererInterface.h"

template <typename T>
class Matrix {
private:
	static long long instructioncounter; 
	const int ZEILEN, SPALTEN;
	T * data;

public:
	Matrix<T>(int zeilen, int spalten);
	Matrix<T>(const Matrix<T> &);
	~Matrix<T>();
	Matrix<T> & init();
	Matrix<T> & initRandom(T minValue = 0, T maxValue = 100);
	Matrix<T> & print();
	Matrix<T> & input();
	Matrix<T> add(const Matrix<T> & that) { return *this + that; }
	Matrix<T> & mult(const Matrix<T> & factor, Matrix<T> & result); 
	Matrix<T> & quickmult(const Matrix<T> & factor, Matrix<T> & result); 
	Matrix<T> & operator+= (const Matrix<T> & that); 
	Matrix<T> operator+ (const Matrix<T> & that); 
	Matrix<T> & setValue(int line_startWith0, int column_startWith0, T value); 
	T getValue(int line_startWith0, int column_startWith0); 
	long long getInstructionCounter() { return instructioncounter; }
}; //end class


template <typename T>
long long Matrix<T>::instructioncounter = 0; 

template <typename T>
Matrix<T>::Matrix(int zeilen, int spalten) : ZEILEN(zeilen), SPALTEN(spalten) {
	this->data = new T[zeilen * spalten];
	if (this->data == nullptr) {
		throw std::runtime_error("ERROR: OUT OF MEMORY \n"); 
	}
	this->init(); 
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> & that) : ZEILEN(that.ZEILEN), SPALTEN(that.SPALTEN) {
	this->data = new T[that.ZEILEN * that.SPALTEN];
}


template <typename T>
Matrix<T>::~Matrix() {
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

template<typename T>
inline Matrix<T>& Matrix<T>::initRandom(T minValue, T maxValue) {
	initRandomizer();
	int sizeZSm1 = this->ZEILEN * this->SPALTEN - 1; 
	T * x = data + sizeZSm1;
	int range = static_cast<int>(maxValue - minValue); 
	for (int i = sizeZSm1; i >= 0; --i, --x) {
		*x = static_cast<T>(rand() % range + minValue);
	}
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::print() {
	const int width = 7; 
	std::ostringstream result; 
	for (int i = 0; i < this->ZEILEN; i++) {
		for (int j = 0; j < this->SPALTEN; j++) {
			result << std::setw(width) << this->data[i * this->SPALTEN + j] << "  ";
		}
		result << std::endl;
	}
	std::cout << result.str();
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
	Matrix<T>::instructioncounter++;
	if ((this->ZEILEN != that.ZEILEN) || (this->SPALTEN != that.SPALTEN)) {
		std::ostringstream errortext; 
		errortext << "arithmetic exception: cannot add two different sized matrizes. (" 
			<< this->ZEILEN << " x " << this->SPALTEN << ") + (" 
			<< that.ZEILEN << " x " << that.SPALTEN << ") failed.";
		throw std::runtime_error(errortext.str().c_str());
	}

	Matrix<T>::instructioncounter++;
	int size = this->ZEILEN * this->SPALTEN; 
	Matrix<T>::instructioncounter++;
	for (int i = 0; i < size; i++) {
	  Matrix<T>::instructioncounter++;
		this->data[i] += that.data[i]; 
	  Matrix<T>::instructioncounter++;
	}
	Matrix<T>::instructioncounter++;
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
	Matrix<T>::instructioncounter++;
	if ((this->SPALTEN != factor.ZEILEN) ||
	    (this->ZEILEN != result.ZEILEN) || 
	    (factor.SPALTEN != result.SPALTEN)) {
		std::ostringstream errortext; 
		errortext << "arithmetic exception: cannot multiply these matrizes. (" 
			<< this->ZEILEN << " x " << this->SPALTEN << ") x (" 
			<< factor.ZEILEN << " x " << factor.SPALTEN << ") = (" 
			<< result.ZEILEN << " x " << result.SPALTEN << ") failed.";
		throw std::runtime_error(errortext.str().c_str()); 
	}
	Matrix<T>::instructioncounter++;
	for (int i = 0; i < this->ZEILEN; i++) {
	  Matrix<T>::instructioncounter++;
		for (int j = 0; j < factor.SPALTEN; j++) {
	    Matrix<T>::instructioncounter++;
			T accu = 0; 
	    Matrix<T>::instructioncounter++;
			for (int k = 0; k < this->SPALTEN; k++) {
	      Matrix<T>::instructioncounter++;
				accu += this->data[i * this->SPALTEN + k] * factor.data[k * factor.SPALTEN + j]; 
	      Matrix<T>::instructioncounter++;
			}
	    Matrix<T>::instructioncounter++;
			result.data[i * factor.SPALTEN + j] = accu; 
	    Matrix<T>::instructioncounter++;
		}
	}
	
  Matrix<T>::instructioncounter++;
	return result;
}

template<typename T>
inline Matrix<T>& Matrix<T>::quickmult(const Matrix<T>& factor, Matrix<T>& result) {
	if (this->ZEILEN == this->SPALTEN && factor.ZEILEN == factor.SPALTEN && result.ZEILEN == result.SPALTEN && result.ZEILEN == this->ZEILEN && result.ZEILEN == factor.ZEILEN && result.ZEILEN % 2 == 0) {
		MatrixMultipliziererInterface * mquickmult = MatrixMultipliziererInterface::getInstance(this->ZEILEN); 
		mquickmult->setPtrMatrix(MMULT_INDEX__A, this->data, this->ZEILEN); 
		mquickmult->setPtrMatrix(MMULT_INDEX__B, factor.data, this->ZEILEN); 
		mquickmult->executeMultiplication(); 
		mquickmult->setTo(MMULT_INDEX_RESULT, result.data, this->ZEILEN); 

		delete mquickmult;
	}
	return result;
	// TODO: hier Rückgabeanweisung eingeben
}

template <typename T>
Matrix<T> & Matrix<T>::setValue(int zeile, int spalte, T value) {
	this->data[zeile * this->SPALTEN + spalte] = value; 
	return *this; 
}

template <typename T>
T Matrix<T>::getValue(int zeile, int spalte) {
	return this->data[zeile * this->SPALTEN + spalte]; 
}


#endif