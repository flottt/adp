#include "MatrixMultiplizierer.h"

MatrixMultiplizierer::MatrixMultiplizierer(const int ZEILEN) : MatrixMultipliziererInterface(ZEILEN), tinyMult(nullptr) {
	this->tinyMult = MatrixMultipliziererInterface::getInstance(ZEILEN / 2); 
}

MatrixMultiplizierer::~MatrixMultiplizierer() {
	delete this->tinyMult; 
	this->tinyMult = nullptr;
}

void MatrixMultiplizierer::executeMultiplication() {
	this->clearMatrix(MMULT_INDEX_RESULT); 

	const int ZEILEN_HALB = this->ZEILEN / 2;

	const int dLineA = colsAB[0];
	const int dLineB = colsAB[1];
	const int dLineR = colsAB[MMULT_INDEX_RESULT];

	iT * mA = mAB[0];
	iT * mB = mAB[1];
	iT * mR = mAB[MMULT_INDEX_RESULT];

	iT * mA11 = mA; 
	iT * mA12 = mA + ZEILEN_HALB; 
	iT * mA21 = mA + dLineA; 
	iT * mA22 = mA + ZEILEN_HALB + dLineA; 
	
	iT * mB11 = mB; 
	iT * mB12 = mB + ZEILEN_HALB; 
	iT * mB21 = mB + dLineB; 
	iT * mB22 = mB + ZEILEN_HALB + dLineB; 

	iT * mR11 = mR; 
	iT * mR12 = mR + ZEILEN_HALB; 
	iT * mR21 = mR + dLineR; 
	iT * mR22 = mR + ZEILEN_HALB + dLineR; 

	//H1 = (A11 + A22) * (B11 + B22) --> +R11 und +R22
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__A, mA11, mA22, dLineA, +1); 
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__B, mB11, mB22, dLineB, +1); 
	this->tinyMult->executeMultiplication(); 
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR11, dLineR, +1); 
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR22, dLineR, +1); 

	//H2 = (A21 + A22) * B11         --> +R21 und -R22
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__A, mA21, mA22, dLineA, +1);
	this->tinyMult->setPtrMatrix(MMULT_INDEX__B, mB11, dLineB);
	this->tinyMult->executeMultiplication(); 
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR21, dLineR, -1);
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR22, dLineR, +1);

	//H3 = A11 * (B12 - B22)         --> +R12 und +R22
	this->tinyMult->setPtrMatrix(MMULT_INDEX__A, mA11, dLineA);
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__B, mB12, mB22, dLineB, -1);
	this->tinyMult->executeMultiplication();
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR12, dLineR, +1);
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR22, dLineR, +1);

	//H4 = A22 * (B21 - B11)         --> +R11 und +R21
	this->tinyMult->setPtrMatrix(MMULT_INDEX__A, mA22, dLineA);
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__B, mB21, mB11, dLineB, -1);
	this->tinyMult->executeMultiplication();
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR11, dLineR, +1);
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR21, dLineR, +1);

	//H5 = (A11 + A12) * B22         --> +R12 und -R11
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__A, mA11, mA12, dLineA, +1);
	this->tinyMult->setPtrMatrix(MMULT_INDEX__B, mB22, dLineB);
	this->tinyMult->executeMultiplication();
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR12, dLineR, +1);
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR11, dLineR, -1);

	//H6 = (A21 - A11) * (B11 + B12) --> +R22
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__A, mA21, mA11, dLineA, -1);
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__B, mB11, mB12, dLineB, +1);
	this->tinyMult->executeMultiplication();
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR22, dLineR, +1);

	//H7 = (A12 - A22) * (B21 + B22) --> +R11
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__A, mA12, mA22, dLineA, -1);
	this->tinyMult->setAddCopyMatrix(MMULT_INDEX__B, mB21, mB22, dLineB, +1);
	this->tinyMult->executeMultiplication();
	this->tinyMult->addTo(MMULT_INDEX_RESULT, mR11, dLineR, +1);
}
