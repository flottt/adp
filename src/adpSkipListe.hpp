#ifndef __ADP_SKIPLISTE_HPP__
#define __ADP_SKIPLISTE_HPP__

#define myAssert(a, b) {if (!(a)) std::cerr << "ASSERT FAILED: " << b << std::endl; }

#include <iostream>
#include <stdint.h>
#include <time.h>

template <typename T>
class SkipListe {
public:
	template <typename TT>
	struct SkipListObject {
		TT o; 
		SkipListObject<TT> ** next; 
		int16_t height; 
		SkipListObject(TT o, int16_t height) : o(o), height(height), next(nullptr) {
			this->next = new SkipListObject<TT> *[height + 1] { nullptr };
			this->next[0] = nullptr; 
		}
		~SkipListObject() {
			for (int i = this->height; i >= 0; --i) {
				this->next[i] = nullptr;
			}
			delete[] this->next; 
			this->next = nullptr; 
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
	void print(std::ostream &) const;
	void printDebug(std::ostream &) const;
	void insertKey(const T &); 
	void removeKey(const T &); 
	bool searchKey(const T &); 
	SkipListe<T> & operator+=(const T &); 
	SkipListe<T> & operator-=(const T &); 
	template <typename TT>	
	friend std::ostream & operator<<(std::ostream &, const SkipListe<TT> &); 
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
	if (result > this->maxHeight) {
		//TODO 
		this->nextRandom = this->maxHeight; 
	
	}
	
}

/** constructor */
template<typename T>
SkipListe<T>::SkipListe() : size(0), nextRandom(0), first(nullptr), maxHeight(10) {
	first = new SkipListObject<T> * [this->maxHeight + 1];
	for (int i = this->maxHeight; i >= 0; --i) {
		first[i] = nullptr;
	}
	srand(time(0)); 
}

/** destructor*/
template<typename T>
SkipListe<T>::~SkipListe() {
	for (SkipListe<T>::SkipListObject<T> * ptr = first[0], * nextPtr = nullptr; ptr != nullptr; ptr = nextPtr) {
		nextPtr = ptr->next[0]; 
		ptr->next[0] = nullptr; 
		delete ptr; 
	}
	delete[] first; 
}

template<typename T>
void SkipListe<T>::print(std::ostream & out) const {
	myAssert(first != nullptr, "first = nullptr"); 
	SkipListe<T>::SkipListObject<T> * ptr = first[0]; 
	while (ptr != nullptr) {
		out << ptr->o << " "; 
		ptr = ptr->next[0];
	}
}

template<typename T>
void SkipListe<T>::printDebug(std::ostream & out) const {
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
		out << "), " << std::endl;
		ptr = ptr->next[0]; 
	}

}

template<typename T>
void SkipListe<T>::insertKey(const T & o) {
	if (this->size == 0) {
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

template<typename T>
void SkipListe<T>::removeKey(const T & o) {
  if (this->size > 0) {
		SkipListe<T>::SkipListObject<T> ** turm = this->searchTree(o);
		if (turm[0] != nullptr && turm[0]->o == o) { //Element exisitert
			//suche Element zuvor
			int16_t h = turm[0]->height; 
			SkipListObject<T> * vorher = nullptr, * vorherNext = nullptr; 			
			if (h == this->maxHeight) {
				vorher = first[h]; 
			} else if (turm[h + 1] == nullptr) {
				vorher = first[h]; 
			} else {
				vorher = turm[h + 1]; 
			} 
			//ganz vorn
			for (; h >= 0 && *turm == first[h]; --h) {
				first[h] = first[h]->next[h];
				if (h > 0) {
					vorher = first[h - 1]; 
				}
			}

			//TODO ganz vorn			
			myAssert(vorher != turm[0], "unlogischer Turm beim loeschen");
			for (; h >= 0; --h) {
				vorherNext = vorher; 
				do {				
					vorher = vorherNext; 
					vorherNext = vorher->next[h]; 
					myAssert(vorherNext != nullptr, "Loch in Skipliste. Missing zu loeschendes Element. ");
				} while(vorherNext != turm[0]); 
				vorher->next[h] = turm[0]->next[h];
				turm[0]->next[h] = nullptr;  
			} //next h
			delete turm[0]; 
			return; 
		} //end if Element existiert
	}//end if size > 0
	std::cout << "cannot delete non-existent element " << o << std::endl; 
}

template<typename T>
SkipListe<T> & SkipListe<T>::operator+=(const T & o) {
  this->insertKey(o);
  return *this;
}

template<typename T>
SkipListe<T> & SkipListe<T>::operator-=(const T & o) {
  this->removeKey(o); 
  return *this;
}

template <typename T>	
std::ostream & operator<<(std::ostream & out, const SkipListe<T> & liste) {
	liste.print(out); 
	return out;
} 

#endif //__ADP_SKIPLISTE_HPP__
