#ifndef __ADP_BIN_TREE__H__
#define __ADP_BIN_TREE__H__
#include <cassert>
#include <iostream>

template <typename T>
class BinTreeNode {
public:
	T o;
	BinTreeNode<T> *left, *right, *top; 
	BinTreeNode<T> *getMostDownLeft();
	bool isLeftNode(); 

public: 
	BinTreeNode(T o); 
	~BinTreeNode();

	void glueTo(BinTreeNode<T> & parent, bool left); 
	void printInOrderRecursive(std::ostream & out); 
}; //end class BinTreeNode

/** general binary tree */
template <typename T>
class BinTree {
public:
	BinTreeNode<T> * root; 

public: 
	BinTree(); 
	BinTree(T * preOrder, T * inOrder, int anzahl); 
	~BinTree();

	BinTreeNode<T> & cutNodeTop(BinTreeNode<T> & node); 
	void printInOrderRecursive(std::ostream & out);
}; //end class BinTree


template<typename T>
BinTreeNode<T>::BinTreeNode(T o) : left(nullptr), right(nullptr), top(nullptr), o(o) {
}

template<typename T>
BinTreeNode<T>::~BinTreeNode() {
	if (this->left != nullptr || this->right != nullptr) {
		BinTreeNode<T> *node = this->getMostDownLeft();
		BinTreeNode<T> *topNode = node->top;

		while (node != this && node != nullptr) {
			topNode = node->top;
			if (topNode == nullptr) {
			} else if (node->isLeftNode()) {
				topNode->left = nullptr;
			} else {
				topNode->right = nullptr;
			}

			delete node; 
			node = topNode->getMostDownLeft(); 
		}
	}
}

template<typename T>
void BinTreeNode<T>::glueTo(BinTreeNode<T> & parent, bool toLeft) {
	if (this->top != &parent) {
		if (toLeft) {
			delete parent.left; 
			parent.left = this;
		} else {
			delete parent.right;
			parent.right = this;
		}

		if (this->top != nullptr) {
			if (this->top->left == this) {
				this->top->left = nullptr;
			} else if (this->top->right == this) {
				this->top->right = nullptr;
			}
		}
		this->top = &parent;
	}
}

template<typename T>
inline void BinTreeNode<T>::printInOrderRecursive(std::ostream & out) {
	if (this->left == nullptr && this->right == nullptr) {
		out << this->o;
	} else {
		out << '(';
		if (this->left == nullptr) {
			out << '-'; 
		} else {
			this->left->printInOrderRecursive(out);
		}
		out << ',' << this->o << ',';
		if (this->right == nullptr) {
			out << '-';
		} else {
			this->right->printInOrderRecursive(out);
		}
		out << ')';
	}
}

template<typename T>
inline BinTreeNode<T> * BinTreeNode<T>::getMostDownLeft() {
	BinTreeNode *node = this, *nextNode = this; 
	while (nextNode != nullptr) {
		while (nextNode != nullptr) {
			node = nextNode; 
			nextNode = nextNode->left; 
		}
		nextNode = node->right;
	}
	return node; 
}

template<typename T>
inline bool BinTreeNode<T>::isLeftNode() {
	return (this->top != nullptr && this->top->left == this);
}

template<typename T>
BinTree<T>::BinTree() : root(nullptr) {
}

template<typename T>
inline BinTree<T>::BinTree(T * preOrder, T * inOrder, int anzahl) : root(nullptr) {
	bool left = true; 
	BinTreeNode<T> * node, *node2 = nullptr; 
	if (anzahl > 0) {
		this->root = node = new BinTreeNode<T>(*preOrder); 
		--anzahl; 
		++preOrder; 
	}
	while (anzahl > 0) {
		while (*inOrder != node->o) {
			node2 = new BinTreeNode<T>(*preOrder); 
			if (node->left == nullptr && left) {
				node->left = node2; 
			} else {
				node->right = node2; 
			}
			node2->top = node; 
			node = node2; 
			--anzahl; 
			++preOrder; 
			left = true; 
			if (anzahl <= 0) {
				return; 
			}
		}
		left = false;
		++inOrder; 
		while (*inOrder != *preOrder) {
			while (node->o != *inOrder) {
				node = node->top;
				if (node == nullptr) {
					throw "Illegal Tree";
				}
			}
			++inOrder;
		}
		//now *inOrder == *preOrder
		node2 = new BinTreeNode<T>(*preOrder); 
		node->right = node2; 
		node2->top = node; 
		node = node2; 
		--anzahl; 
		++preOrder; 
		++inOrder;
		if (anzahl <= 0) {
			return; 
		}
		//node2 = node; 
		while (node2 != nullptr) {
			node2 = node2->top; 
			if (node2 != nullptr && node2->o == *inOrder) {
				++inOrder; 
				node = node2; 
			}
		}
	}
}

template<typename T>
inline BinTree<T>::~BinTree() {
	delete root;
	root = nullptr;
}
template<typename T>
BinTreeNode<T> & BinTree<T>::cutNodeTop(BinTreeNode<T> & node) {
	if (&node == this->root) {
		root = nullptr; 
	} else if (node.isLeftNode()) {
		node.top->left = nullptr;
		node.top = nullptr; 
	} else {
		node.top->right = nullptr; 
		node.top = nullptr;
	}
	return node;
}
template<typename T>
void BinTree<T>::printInOrderRecursive(std::ostream & out) {
	if (this->root == nullptr) {
		out << "---" << std::endl;
	} else {
		this->root->printInOrderRecursive(out); out << std::endl; 
	}
}
#endif // !__ADP_BIN_TREE__H__
