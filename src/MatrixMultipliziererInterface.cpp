#include "MatrixMultipliziererInterface.h"
#include "MatrixMultiplizierer.h"
#include "MatrixMultipliziererDirect.h"

#define MMULT_ANZAHL_MATRIZEN_RAM 3

MatrixMultipliziererInterface::MatrixMultipliziererInterface(const int ZEILEN) : ZEILEN(ZEILEN) {
	this->matrix = new iT[ZEILEN * ZEILEN * MMULT_ANZAHL_MATRIZEN_RAM];
	this->mAB = new iT*[MMULT_ANZAHL_MATRIZEN_RAM]; // (iT**)malloc(MMULT_ANZAHL_MATRIZEN_RAM * sizeof(void*));
	this->colsAB = new int[MMULT_ANZAHL_MATRIZEN_RAM]; 

	for (int i = 0; i < MMULT_ANZAHL_MATRIZEN_RAM; ++i) {
		this->mAB[i] = this->matrix + (ZEILEN * i); 
		this->colsAB[i] = ZEILEN; 
	}
}

MatrixMultipliziererInterface::~MatrixMultipliziererInterface() {
	delete[] this->matrix; 
	this->matrix = nullptr;
	delete[] this->mAB; // free(this->mAB);
	this->mAB= nullptr;
	delete[] this->colsAB; 
	this->colsAB = nullptr; 
}

MatrixMultipliziererInterface * MatrixMultipliziererInterface::getInstance(const int ZEILEN) {
	if (ZEILEN >= 50 && ZEILEN % 2 == 0) {
		return new MatrixMultiplizierer(ZEILEN);
	} else {
		return new MatrixMultipliziererDirect(ZEILEN); 
	}
}

void MatrixMultipliziererInterface::setCopyMatrix(const int indexInto, const iT * maFrom, int columnsPerLineFrom) {
	iT * matrixData = this->mAB[indexInto] = this->matrix + (this->ZEILEN * indexInto); 
	this->colsAB[indexInto] = this->ZEILEN;
	columnsPerLineFrom -= this->ZEILEN; 

	for (int i = 0; i < this->ZEILEN; ++i) {
		for (int j = 0; j < this->ZEILEN; ++j) {
			*matrixData = *maFrom; 
			++matrixData; 
			++maFrom;
		}
		maFrom += columnsPerLineFrom;
	}
}

void MatrixMultipliziererInterface::setAddCopyMatrix(const int indexInto, const iT * maFrom1, const iT * maFrom2, int columnsPerLineFrom, int vorzeichenFactor) {
	iT * matrixData = this->mAB[indexInto] = this->matrix + (this->ZEILEN * indexInto);
	this->colsAB[indexInto] = this->ZEILEN;
	columnsPerLineFrom -= this->ZEILEN;

	for (int i = 0; i < this->ZEILEN; ++i) {
		for (int j = 0; j < this->ZEILEN; ++j) {
			*matrixData = *maFrom1 + (vorzeichenFactor * *maFrom2);
			++matrixData;
			++maFrom1;
			++maFrom2; 
		}
		maFrom1 += columnsPerLineFrom;
		maFrom2 += columnsPerLineFrom;
	}

}

void MatrixMultipliziererInterface::setPtrMatrix(const int indexInto, iT * maFrom, int columnsPerLineFrom) {
	this->mAB[indexInto] = maFrom;
	this->colsAB[indexInto] = columnsPerLineFrom;
}

void MatrixMultipliziererInterface::clearMatrix(const int indexInto) {
	iT * matrixDataStart = this->mAB[indexInto] = matrix + (this->ZEILEN * indexInto); 
	this->colsAB[indexInto] = 0; 
	for (iT * matrixData = matrixDataStart + this->ZEILEN - 1; matrixData >= matrixDataStart; --matrixData) {
		*matrixData = 0; 
	}
}

void MatrixMultipliziererInterface::addTo(const int indexFrom, iT * maAddTo, int columnsPerLineAddTo, int vorzeichenFactor) {
	iT * summand = this->mAB[indexFrom]; 
	int columnsPerLineSummand = this->colsAB[indexFrom] - this->ZEILEN; 
	columnsPerLineAddTo -= this->ZEILEN; 

	for (int i = 0; i < this->ZEILEN; ++i) {
		for (int j = 0; j < this->ZEILEN; ++j) {
			*maAddTo += vorzeichenFactor * *summand; 
			++summand;
			++maAddTo; 
		}
		summand += columnsPerLineSummand; 
		maAddTo += columnsPerLineAddTo; 
	}
}

void MatrixMultipliziererInterface::setTo(const int indexFrom, iT * maAddTo, int columnsPerLineAddTo) {
	iT * summand = this->mAB[indexFrom];
	int columnsPerLineSummand = this->colsAB[indexFrom] - this->ZEILEN;
	columnsPerLineAddTo -= this->ZEILEN;

	for (int i = 0; i < this->ZEILEN; ++i) {
		for (int j = 0; j < this->ZEILEN; ++j) {
			*maAddTo = *summand;
			++summand;
			++maAddTo;
		}
		summand += columnsPerLineSummand;
		maAddTo += columnsPerLineAddTo;
	}
}
