#include "MatrixMultipliziererDirect.h"

MatrixMultipliziererDirect::MatrixMultipliziererDirect(const int ZEILEN) : MatrixMultipliziererInterface(ZEILEN) {
}

void MatrixMultipliziererDirect::executeMultiplication() {
	const iT * mA = mAB[0]; 
	const iT * mB = mAB[1]; 
	iT * mR = mAB[MMULT_INDEX_RESULT]; 
	int dLineA = colsAB[0]; 
	int dLineB = colsAB[1]; 
	int ddLineR = colsAB[MMULT_INDEX_RESULT] - this->ZEILEN; 

	for (int i = 0; i < this->ZEILEN; ++i) {
		for (int j = 0; j < this->ZEILEN; ++j, ++mR) {
			*mR = 0; 

			for (int k = 0; k < this->ZEILEN; ++k) {
				*mR += mA[i * dLineA + k] * mB[k * dLineB + j]; 
			}
		}
		mR += ddLineR; 
	}
}
