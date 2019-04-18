#ifndef __ADP_PRINTING_CONSOLE_HELPER__
#define __ADP_PRINTING_CONSOLE_HELPER__

void swop(int * a, const int x1, const int x2);
void printArrayInOneLine(const int * a, const int n);
void printArray(const int * a, const int n); 
void printBinaryTreeLeftAligned(std::ostream & out, const int * tree, int size, const char * name = nullptr);

#endif // !__ADP_PRINTING_CONSOLE_HELPER__