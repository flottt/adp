#ifndef __ADP_PRINTING_CONSOLE_HELPER__
#define __ADP_PRINTING_CONSOLE_HELPER__
#include <iostream> 

void initRandomizer();
void initArrayRandom(int * a, const int n, const int minValue = 0, const int maxValue = 100);

void swop(int * a, const int x1, const int x2);
void printArrayInOneLine(const int * a, const int n);
void printArray(const int * a, const int n); 
void printMatrix(const int * a, const int size, const bool strict = false); 
void printBinaryTreeLeftAligned(std::ostream & out, const int * tree, int size, const char * name = nullptr);

void testAssertInt(int a, int b, const char * c); 

#endif // !__ADP_PRINTING_CONSOLE_HELPER__