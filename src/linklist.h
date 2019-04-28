#ifndef __ADP6_LINKNODE__H__
#define __ADP6_LINKNODE__H__

#include <iostream>
typedef int intT;

/** Knoten fuer linklist und fuer ringlist */
struct linknode {
	intT x;
	linknode * next;
	linknode(intT xx); 
};

/** einfach verkettete Liste mit Start und Ende */
struct linklist {
	linknode * first;
	linknode * last;

	linklist(); 
	~linklist();
	void push_back(intT x); 
	void push_back_steal_all(linklist & liste); 
	void push_front(intT x); 
	intT pop_front(); 
	bool isEmpty(); 

	void quicksort(); 

	friend std::ostream & operator<< (std::ostream &, const linklist &);
};

/** einfache Ringliste */
struct ringlist {
	linknode * lastSeen; 

	ringlist(); 
	~ringlist(); 

	void push(intT x); 
	intT get(int skip, bool remove); 
	intT pop(int skip = 0); 
	bool isEmpty();
	intT operator[](int skip);
};


#endif // !__ADP6_LINKNODE__H__
