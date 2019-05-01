#ifndef __ADP_MATRIX_MULTIPLY_DIRECT__H__
#define __ADP_MATRIX_MULTIPLY_DIRECT__H__

#include "MatrixMultipliziererInterface.h"

class MatrixMultipliziererDirect : public MatrixMultipliziererInterface {
friend class MatrixMultipliziererInterface;

public:
	MatrixMultipliziererDirect(const int ZEILEN); 
	virtual void executeMultiplication(); 
};

#endif //__ADP_MATRIX_MULTIPLY_DIRECT__H__