#ifndef __ADP_SUCH_TREE__H__
#define __ADP_SUCH_TREE__H__
#define _TREE_DEBUG 1

#include "AdpBinTree.h"

/** A search tree for primitive (--> no delete) and unique (--> overwrites duplicates) Objects */
template <typename T>
class SuchTreeSingle : public BinTree<T> {
protected:
	BinTreeNode<T> * find(T x);
public:
	void add(T x); 
	BinTreeNode<T> * remove(T x); 
};


template<typename T>
inline BinTreeNode<T> * SuchTreeSingle<T>::find(T x) {
	BinTreeNode<T> *result = this->root, *nextNode = this->root;
	if (result == nullptr) {
		return nullptr;
	} else {
		while (nextNode != nullptr) {
			result = nextNode; 
			if (x == nextNode->o) {
				return result; 
			} else if (x < nextNode->o) {
				nextNode = nextNode->left; 
			} else {
				nextNode = nextNode->right;
			}
		}
		return result;
	}
}

template<typename T>
inline void SuchTreeSingle<T>::add(T x) {
	if (this->root == nullptr) {
		BinTreeNode<T> * newNode = new BinTreeNode<T>(x);
		this->root = newNode; 
	} else {
		BinTreeNode<T> * aktNode = this->find(x); 
		if (aktNode->o == x) {
			if (_TREE_DEBUG) std::cout << "overwriting " << x << " into node " << aktNode->o << std::endl;
			aktNode->o = x; 
		} else {
			BinTreeNode<T> * newNode = new BinTreeNode<T>(x);
			if (_TREE_DEBUG) std::cout << "adding " << x << " to node " << aktNode->o << std::endl;
			newNode->glueTo(*aktNode, (x < aktNode->o)); 
		}
	}
}

template<typename T>
inline BinTreeNode<T> * SuchTreeSingle<T>::remove(T x) {
	BinTreeNode<T> * deleteNode = this->find(x);
	BinTreeNode<T> * parentNode = nullptr, * childNode = nullptr;
	bool wasLeftNode = false; 

	if (deleteNode != nullptr && deleteNode->o == x) {
		if (deleteNode->left == nullptr) {
			if (deleteNode->right == nullptr) {
				//(---, [x], ---)
				if (_TREE_DEBUG) std::cout << "removing leaf " << x << std::endl;
				parentNode = deleteNode->top; 
				this->cutNodeTop(*deleteNode);
				delete deleteNode;
				return parentNode; 
			} else {
				//(---, [x], r)
				if (_TREE_DEBUG) std::cout << "shorting right branch " << x << std::endl;
				parentNode = deleteNode->top;
				wasLeftNode = deleteNode->isLeftNode(); 
				this->cutNodeTop(*deleteNode);
				childNode = deleteNode->right; 
				childNode->glueTo(*parentNode, wasLeftNode); 
				delete deleteNode; 
				return parentNode;
			}
		}	else {
			if (deleteNode->right == nullptr) {
				//(l, [x], ---) 
				if (_TREE_DEBUG) std::cout << "shorting left branch " << x << std::endl;
				parentNode = deleteNode->top;
				wasLeftNode = deleteNode->isLeftNode();
				this->cutNodeTop(*deleteNode);
				childNode = deleteNode->left;
				childNode->glueTo(*parentNode, wasLeftNode); 
				delete deleteNode;
				return parentNode;
			} else {
				//(l, [x], r) 
				childNode = deleteNode->left; 
				while (childNode->right != nullptr) {
					childNode = childNode->right;
				}
				deleteNode->o = childNode->o; 
				if (childNode->left == nullptr) {
					if (_TREE_DEBUG) std::cout << "moving leaf " << childNode->o << " up into node " << x << std::endl;
					parentNode = childNode->top;
					this->cutNodeTop(*childNode); 
					delete childNode; 
					return parentNode; 
				} else {
					parentNode = childNode->top; 
					wasLeftNode = childNode->isLeftNode();
					if (_TREE_DEBUG) std::cout << "moving branch " << childNode->o << " up into node " << x << std::endl;
					this->cutNodeTop(*childNode); 
					childNode->left->glueTo(*parentNode, wasLeftNode);
					//parentNode = childNode->top;
					delete childNode; 
					return parentNode; 
				}
			}
		}	
	} else if (_TREE_DEBUG) {
		std::cout << "could not find " << x << " --> no delete" << std::endl;
		return nullptr;
	}
}

#endif // !__ADP_SUCH_TREE__H__
