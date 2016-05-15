#ifndef NODE_H
#define NODE_H
template <typename T>
class Node
{
private:
	Node<T>* m_left;
	Node<T>* m_right;
public:
	Node();
	Node<T>* getLeft();
	Node<T>* getRight();
	void setLeft(Node<T>* left);
	void setRight(Node<T>* right);
};

#endif //NODE_H
