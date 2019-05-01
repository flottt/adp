#ifndef __ADP_AVL_TREE__H__
#define __ADP_AVL_TREE__H__

#include "AdpSuchTree.h"

template <typename T>
class BinAvlTreeNode : public BinTreeNode<T> {
public:
	int hoch; 
	BinAvlTreeNode(T o);
	int calcHochDiff(); 
}; //end class BinTreeNode

template <typename T>
class AvlTree : public SuchTreeSingle<T> {
protected: 
	void rotationLeft(BinAvlTreeNode<T> * node); 
	void rotationRight(BinAvlTreeNode<T> * node); 
public: 
	void add(T x);
	void remove(T x);
};

#endif // !__ADP_AVL_TREE__H__

template<typename T>
inline BinAvlTreeNode<T>::BinAvlTreeNode(T o) : BinTreeNode<T>(o), hoch(0) {}

template<typename T>
inline int BinAvlTreeNode<T>::calcHochDiff() {
	int hochLeft  = (  (this->left == nullptr) ? -1 : (static_cast<BinAvlTreeNode *>(this->left))->hoch);
	int hochRight = ((this->right == nullptr) ? -1 : (static_cast<BinAvlTreeNode *>(this->right))->hoch);
	this->hoch = 1 + ((hochLeft < hochRight) ? hochRight : hochLeft); 
	return hochRight - hochLeft; 
}

template<typename T>
inline void AvlTree<T>::rotationLeft(BinAvlTreeNode<T> * nodeOldSrc) {
	BinAvlTreeNode<T> * nodeNewSrc = static_cast<BinAvlTreeNode<T> *> (nodeOldSrc->right);
	if (_TREE_DEBUG) std::cout << "rotationLinks: " << nodeOldSrc->o << " sink down and " << nodeNewSrc->o << " fly up" << std::endl;
	
	//Wurzelknoten
	if (nodeOldSrc->top == nullptr) {
		this->root = nodeNewSrc;
		nodeNewSrc->top = nullptr; 
	} else if (nodeOldSrc->top->left == nodeOldSrc) {
		nodeOldSrc->top->left = nodeNewSrc;
		nodeNewSrc->top = nodeOldSrc->top; 
	} else {
		nodeOldSrc->top->right = nodeNewSrc; 
		nodeNewSrc->top = nodeOldSrc->top; 
	}

	//switching middle branch
	if (nodeNewSrc->left == nullptr) {
		nodeOldSrc->right = nullptr; 
	} else {
		nodeOldSrc->right = nodeNewSrc->left;
		nodeOldSrc->right->top = nodeOldSrc;
	}
	//lifting new over old
	nodeNewSrc->left = nodeOldSrc; 
	nodeOldSrc->top = nodeNewSrc; 

	nodeOldSrc->calcHochDiff();
	nodeNewSrc->calcHochDiff();
}

template<typename T>
inline void AvlTree<T>::rotationRight(BinAvlTreeNode<T> * nodeOldSrc) {
	BinAvlTreeNode<T> * nodeNewSrc = static_cast<BinAvlTreeNode<T> *> (nodeOldSrc->left);
	if (_TREE_DEBUG) std::cout << "rotationRight: " << nodeOldSrc->o << " sink down and " << nodeNewSrc->o << " fly up" << std::endl;

	//Wurzelknoten
	if (nodeOldSrc->top == nullptr) {
		this->root = nodeNewSrc;
		nodeNewSrc->top = nullptr;
	} else if (nodeOldSrc->top->left == nodeOldSrc) {
		nodeOldSrc->top->left = nodeNewSrc;
		nodeNewSrc->top = nodeOldSrc->top;
	} else {
		nodeOldSrc->top->right = nodeNewSrc;
		nodeNewSrc->top = nodeOldSrc->top;
	}

	//switching middle branch
	if (nodeNewSrc->right == nullptr) {
		nodeOldSrc->left = nullptr; 
	} else {
		nodeOldSrc->left = nodeNewSrc->right;
		nodeOldSrc->left->top = nodeOldSrc;
	}

	//lifting new over old
	nodeNewSrc->right = nodeOldSrc;
	nodeOldSrc->top = nodeNewSrc;

	nodeOldSrc->calcHochDiff();
	nodeNewSrc->calcHochDiff();
}

template<typename T>
inline void AvlTree<T>::add(T x) {
	if (this->root == nullptr) {
		BinAvlTreeNode<T> * newNode = new BinAvlTreeNode<T>(x);
		this->root = newNode;
	} else {
		BinAvlTreeNode<T> * aktNode = static_cast<BinAvlTreeNode<T> *>(this->find(x));
		if (aktNode->o == x) {
			if (_TREE_DEBUG) std::cout << "overwriting " << x << " into node " << aktNode->o << std::endl;
			aktNode->o = x;
		} else {
			int diff; 
			BinAvlTreeNode<T> * newNode = new BinAvlTreeNode<T>(x);
			if (_TREE_DEBUG) std::cout << "adding " << x << " to node " << aktNode->o << std::endl;
			newNode->glueTo(*aktNode, (x < aktNode->o));

			while (aktNode != nullptr) {
				diff = aktNode->calcHochDiff();
				if (diff < -1) {
					//Linker Ast ist wesentlich höher als rechter Ast ==> RechtsRotation!
					diff = (static_cast<BinAvlTreeNode<T> *>(aktNode->left))->calcHochDiff(); 
					if (diff > 0) {
						//Doppelrotation
						this->rotationLeft(static_cast<BinAvlTreeNode<T> *> (aktNode->left));
						(static_cast<BinAvlTreeNode<T> *>(aktNode->left))->calcHochDiff();
					}
					this->rotationRight(aktNode);
					(static_cast<BinAvlTreeNode<T> *>(aktNode))->calcHochDiff();
				} else if (diff > 1) {
					//Rechter Ast ist wesentlich höher als linker Ast ==> LinksRotation!
					diff = (static_cast<BinAvlTreeNode<T> *>(aktNode->right))->calcHochDiff();
					if (diff < 0) {
						//Doppelrotation
						this->rotationRight(static_cast<BinAvlTreeNode<T> *> (aktNode->right));
						(static_cast<BinAvlTreeNode<T> *>(aktNode->right))->calcHochDiff();
					}
					this->rotationLeft(aktNode);
					(static_cast<BinAvlTreeNode<T> *>(aktNode))->calcHochDiff();
				}

				aktNode = static_cast<BinAvlTreeNode<T>*>(aktNode->top);
			}
		}
	}
}

template<typename T>
void AvlTree<T>::remove(T x) {
	int diff; 
	BinAvlTreeNode<T> * node = static_cast<BinAvlTreeNode<T>*>(SuchTreeSingle<T>::remove(x));
	BinAvlTreeNode<T> * nodeDown = nullptr; 
	while (node != nullptr) {
		diff = node->calcHochDiff();
		if (diff < -1) {
			nodeDown = static_cast<BinAvlTreeNode<T>*>(node->left);
			diff = nodeDown->calcHochDiff();
			if (diff >= 1) {
				this->rotationLeft(nodeDown); 
				nodeDown->calcHochDiff();
			}
			//linker Ast viel laenger als rechter Ast
			std::cout << "avl Baum defekt" << diff << std::endl;
			this->rotationRight(node);
			diff = node->calcHochDiff();

		} else if (diff > 1) {
			nodeDown = static_cast<BinAvlTreeNode<T>*>(node->right);
			//rechter Ast viel laenger als linker Ast
			diff = nodeDown->calcHochDiff();
			if (diff <= -1) {
				this->rotationRight(nodeDown);
				nodeDown->calcHochDiff();
			}
			//std::cout << "avl Baum defekt" << diff << std::endl;
			this->rotationLeft(node);
			diff = node->calcHochDiff();
			
		}
		node = static_cast<BinAvlTreeNode<T>*>(node->top);
	}
}
