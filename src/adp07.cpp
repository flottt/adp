#include <iostream>
#include <iomanip>
#include <random>
#include "adpHelper.h"
#include "AdpAvlTree.h"

int adp07_1_main(void) {
	//Beispiel 1:
	//int pre[10] = { 12, 7, 1, 8, 20, 30 };
	//int in[10] = { 1, 7, 8, 12, 20, 30 };
	//BinTree<int> baum(pre, in, 11);
	
	//Beispiel 2: 
	int in[12] = {3, 1, 2, 4, 17, 5, 36, 21, 22, 23, 37};
	int pre[12] = {17, 4, 1, 3, 2, 5, 36, 37, 22, 21, 23};
	BinTree<int> baum(pre, in, 11);

	//Fehler-Baum: 
	//int pre[12] = {3, 1, 2, 4, 17, 5, 36, 21, 22, 23, 37};
	//int in[12] = {17, 4, 1, 3, 2, 5, 36, 37, 22, 21, 23};
	//BinTree<int> baum(pre, in, 11);
	
	baum.printInOrderRecursive(std::cout);
	return 0;
}
//Eingabe von Preorder in Suchbaum ist Standardeingabe...


int adp07_2_main(void) {
	int werteAdd[] = { 5, 6, 9, 12, 13, 3, 8, 10, 11, 16, 15, 14, 4, 2, 1, 0 }; 
	int werteDel[] = { 12, 8, 5, 4, 3, 6, 15, 14, 0 };
	
	AvlTree<int> baum; 
	for (int i = 0; werteAdd[i] != 0; ++i) {
		baum.add(werteAdd[i]);
		baum.printInOrderRecursive(std::cout);
	}

	std::cout << "+------------------------------------------------------------------------+" << std::endl
            << "| Begin deletion of elements                                             |" << std::endl
	          << "+------------------------------------------------------------------------+" << std::endl;

	for (int i = 0; werteDel[i] != 0; ++i) {
		baum.remove(werteDel[i]); 
		baum.printInOrderRecursive(std::cout);
	}
	return 0;
}

/** Ein Minimaler AVL-Baum hat an jedem Knoten der Höhe h einen Astknoten der Höhe h-1 und einen der Höhe h-2 für h >= 1. */
int countMinAVLTrees(int hoehe) {
	if (hoehe < 2) {
		if (hoehe == 1) return 2; 
		else if (hoehe == 0) return 1; 
		else return 0;
	} else {
		int hoehe_i_minus2 = 1;  //hoehe 0 
		int hoehe_i_minus1 = 2;  //hoehe 1
		int hoehe_i; 
		for (int i = 2; i <= hoehe; ++i) {
			hoehe_i = 2 * hoehe_i_minus1 * hoehe_i_minus2; 
			//erhoehe i 
			hoehe_i_minus2 = hoehe_i_minus1; 
			hoehe_i_minus1 = hoehe_i; 
		}
		return hoehe_i;
	}
}

/** Zaehlt die Anzahl der Knoten eines AVL-Baums der Hoehe hoehe */
int countMinAVLNodes(const int hoehe) {
	if (hoehe < 2) {
		if (hoehe == 1) return 2; 
		else if (hoehe == 0) return 1; 
		else return 0;
	} else {
		int result_i_minus2 = 1; //hoehe 0
		int result_i_minus1 = 2; //hoehe 1
		int result_i; 
		for (int i = 2; i <= hoehe; ++i) {
			result_i = result_i_minus1 + result_i_minus2 + 1;
			//erhoehe i
			result_i_minus2 = result_i_minus1; 
			result_i_minus1 = result_i;
		}
		return result_i;
	}
}

/** Erstellt einen Minimalbaum-Knoten 
 * @param int height Gewuenschte Hoehe 
 * @param int & zahl Laufende Zahl fuer die Knoten. Der erste Knoten bekommt zahl+1. 
 * @param int & key Der wievielte Baum erstellt werden soll. Der Inhalt wird dabei veraendert auf 0. 
 * @return BinAvlTreeNode<int> * Knoten, der an eine Wurzel eines neuen AVL-Baums gesetzt werden kann. */
BinAvlTreeNode<int> * createMinTree(int height, int & zahl, int & key) {
	if (height < 0) {
		return nullptr; 
	} else if (height == 0) {
		return new BinAvlTreeNode<int>(++zahl); 
	} else {
		int heightLeft = ((key % 2) ? (height - 1) : (height - 2));
		int heightRight = 2 * height - heightLeft - 3;
		key /= 2; 
		BinAvlTreeNode<int> * leftNode = createMinTree(heightLeft, zahl, key); 
		BinAvlTreeNode<int> * result = new BinAvlTreeNode<int>(++zahl);
		BinAvlTreeNode<int> * rightNode = createMinTree(heightRight, zahl, key);
		if (leftNode == nullptr) {
			result->left = nullptr;
		} else {
			result->left = leftNode;
			leftNode->top = result;
		}
		if (rightNode == nullptr) {
			result->right = nullptr;
		} else {
			result->right = rightNode;
			rightNode->top = result;
		}
		return result;
	}
}

/** minimale AVL-Baeume */
int adp07_3_main(void) {
	const int hoehe = 5; 
	int countTrees = countMinAVLTrees(hoehe); 
	int countNodes = countMinAVLNodes(hoehe);
	std::cout << "Es gibt " << countTrees << " minimale AVL-Baeume der Hoehe " << hoehe << " und dieser hat " << countNodes << " Knoten. " << std::endl;
	for (int treeIndex = 0; treeIndex < countTrees; ++treeIndex) {
		std::cout << "Baum #" << std::setw(5) << (treeIndex + 1) << ": "; 
		int zahl = 0; 
		int key = treeIndex; 
		AvlTree<int> baum; 
		baum.root = createMinTree(hoehe, zahl, key); 
		baum.printInOrderRecursive(std::cout);
	}
	return 0;
}
// Ergebnis: Es gibt 4096 minimale AVL-Baeume der Hoehe 5

/** Mit AVL Baeumen sortieren */
int adp07_4_main(void) {
	initRandomizer();
	AvlTree<int> baum; 
	for (int i = 0; i < 10000; ++i) {
		baum.add(rand() % 100000);
	}
	baum.printInOrderRecursive(std::cout);
	return 0; 
}
