#ifndef __ADP_MATRIX_MULTIPLY__H__
#define __ADP_MATRIX_MULTIPLY__H__

#include "MatrixMultipliziererInterface.h"

/** Dieser MatrixMultiplizierer multipliziert ZEILEN x ZEILEN - Matrizen. */
class MatrixMultiplizierer : public MatrixMultipliziererInterface {
friend class MatrixMultipliziererInterface; 

private: 
	MatrixMultipliziererInterface * tinyMult; 

public: 
	MatrixMultiplizierer(const int ZEILEN); 
	~MatrixMultiplizierer(); 
	void executeMultiplication(); 

};

#endif // !__ADP_MATRIX_MULTIPLY__H__
