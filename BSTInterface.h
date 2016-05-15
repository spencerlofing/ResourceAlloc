#ifndef BSTINTERFACE_H
#define BSTINTERFACE_H
#include "Node.h"
template <typename T>
class BST
{
	private:
		Node<T>* m_root;
	public:
		virtual ~BSTInterface(){};
		virtual void insert(Node<T>* newNode)=0;
};
#endif
