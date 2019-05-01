#ifndef __ADP_MATRIX_MULTIPLY_INTERFACE__H__
#define __ADP_MATRIX_MULTIPLY_INTERFACE__H__
#include <cstdlib>

#define MMULT_INDEX__A 0
#define MMULT_INDEX__B 1
#define MMULT_INDEX_RESULT 2
#define MMULT_INDEX_H 3 
typedef int iT;

class MatrixMultipliziererInterface {
public: 
	const int ZEILEN; 

public: 
	MatrixMultipliziererInterface(const int ZEILEN); 
	iT *matrix; //A, B, C, H
	iT **mAB; 
	int * colsAB; 
	void setCopyMatrix(const int indexInto, const iT *maFrom, int columnsPerLineFrom); 
	void setAddCopyMatrix(const int indexInto, const iT *maFrom1, const iT *maFrom2, int columnsPerLineFrom, int vorzeichenFactor); 
	void setPtrMatrix(const int indexInto, iT *maFrom, int columnsPerLineFrom); 
	void clearMatrix(const int indexInto); 
	void addTo(const int indexFrom, iT *maAddTo, int columnsPerLineAddTo, int vorzeichenFactor); 
	void setTo(const int indexFrom, iT *maAddTo, int columnsPerLineAddTo); 
	virtual void executeMultiplication() = 0; 

public: 
	~MatrixMultipliziererInterface();
	static MatrixMultipliziererInterface * getInstance(const int ZEILEN); 

};

#endif //_ADP_MATRIX_MULTIPLY_INTERFACE__H__
