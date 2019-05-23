#ifndef __ADP_SKIPLISTE_HPP__
#define __ADP_SKIPLISTE_HPP__

#define myAssert(a, b) {if (!(a)) std::cerr << "ASSERT FAILED: " << b << std::endl; }

#include <iostream>
#include <stdint.h>

template<typename T>
class SkipListe {
public:
	template<typename T>
	struct SkipListObject {
		T o; 
		SkipListObject<T> ** next; 
		int16_t height; 
		SkipListObject(T o, int16_t height) : o(o), height(height), next(nullptr) {
			next = new SkipListObject<T> *[height + 1] { nullptr };
			next[0] = nullptr; 
		}
	}; //end struct SkipListObject

private:
	int16_t maxHeight; 
	int32_t nextRandom; 
	int32_t size; 
	SkipListObject<T> ** first; 
	SkipListObject<T> ** searchTree(const T &); 
	void resetRandom(); 

public:
	SkipListe(); 
	~SkipListe();
	void print(std::ostream &);
	void printDebug(std::ostream &);
	void insertKey(const T &); 
	void deleteKey(const T &); 
	bool searchKey(const T &); 
};

template<typename T>
SkipListe<T>::SkipListObject<T> ** SkipListe<T>::searchTree(const T & o) {
	static int searchTreeHeight = 0; 
	static SkipListe<T>::SkipListObject<T> ** result = nullptr; 
	if (searchTreeHeight < this->maxHeight) {
		delete[] result; 
		searchTreeHeight = this->maxHeight; 
		result = new SkipListe<T>::SkipListObject<T> *[searchTreeHeight];
	}
	
	if (this->first == nullptr) {
		return nullptr; 
	} else {
		SkipListe<T>::SkipListObject<T> * ptr;
		int height;
		//Startturm
		for (height = this->maxHeight; height >= 0; --height) {
			result[height] = nullptr; 
			ptr = this->first[height]; 
			if (ptr != nullptr && o >= ptr->o) {
				break; 
			}
		}

		for (; height >= 0; --height) {
			result[height] = ptr; 
			if (ptr != nullptr) {
				if (ptr != nullptr && o == ptr->o) {
					//Schluessel gefunden
					for (; height >= 0; --height) {
						result[height] = ptr; 
					}
					return result; 
				} else do {
					result[height] = ptr; 
					ptr = ptr->next[height]; 
				} while (ptr != nullptr && o >= ptr->o); 
				ptr = result[height]; 
			}
		}
		return result; 
	}
}

template<typename T>
inline void SkipListe<T>::resetRandom() {
	int64_t random = rand(); 
	int32_t result = 0; 
	for (; result < this->size && random % 2 == 1; result++) {
		random >>= 1; 
	}
	this->nextRandom = result; 
}

template<typename T>
SkipListe<T>::SkipListe() : size(0), nextRandom(0), first(nullptr), maxHeight(10) {
	first = new SkipListObject<T> * [this->maxHeight + 1];
	for (int i = this->maxHeight; i >= 0; --i) {
		first[i] = nullptr;
	}
//	SkipListObject<T> oo; 
//	oo.o = 7; 
}


template<typename T>
SkipListe<T>::~SkipListe() {
}

template<typename T>
void SkipListe<T>::print(std::ostream &) {
	myAssert(first != nullptr, "first = nullptr"); 
	SkipListe<T>::SkipListObject<T> * ptr = first[0]; 
	while (ptr != nullptr) {
		out << ptr->o << " "; 
		ptr = ptr->next[0];
	}
}

template<typename T>
void SkipListe<T>::printDebug(std::ostream & out) {
	myAssert(first != nullptr, "first = nullptr"); 
	out << "Anzahl = " << this->size << std::endl;
	out << "Turm "; 
	for (int i = this->maxHeight; i >= 0; --i) {
		if (first[i] == nullptr) {
			out << ">-"; 
		} else {
			out << ">" << first[i]->o; 
		}
	}
	out << std::endl;

	SkipListe<T>::SkipListObject<T> * ptr = first[0]; 
	while (ptr != nullptr) {
		out << ptr->o << " (h" << ptr->height << ": ";
		for (int i = ptr->height; i >= 0; --i) {
			if (ptr->next[i] == nullptr) {
				out << ">-";
			} else {
				out << ">" << ptr->next[i]->o; 
			}
		}
		out << "), ";
		ptr = ptr->next[0]; 
	}

}

template<typename T>
void SkipListe<T>::insertKey(const T & o) {
	if (size == 0) {
		first[0] = new SkipListe<T>::SkipListObject<T>(o, 0); 
		++size;
	} else {
		SkipListe<T>::SkipListObject<T> ** turm = this->searchTree(o);
		if ((turm[0] != nullptr && turm[0]->o == o) || (first[0] != nullptr && first[0]->o == o)) {
			std::cout << "bereits enthalten: " << o << std::endl;
			return;
		}

		SkipListe<T>::SkipListObject<T> * newNode = new SkipListe<T>::SkipListObject<T>(o, this->nextRandom);
		for (int16_t h = this->nextRandom; h >= 0; --h) {
			if (turm[h] == nullptr) {
				myAssert(first[h] == nullptr || first[h]->o >= o, "Startturmfehler");
				newNode->next[h] = first[h]; 
				first[h] = newNode; 
			} else {
				newNode->next[h] = turm[h]->next[h];
				turm[h]->next[h] = newNode;
			}
		}

		this->resetRandom(); 
		++size;
	}
	
	
	

}

template<typename T>
bool SkipListe<T>::searchKey(const T & o) {
	if (this->size == 0) {
		return false;
	} else {
		SkipListe<T>::SkipListObject<T> ** turm = this->searchTree(o); 
		return (o == turm[0]->o); 
	}
}


#endif //__ADP_SKIPLISTE_HPP__
