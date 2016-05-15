#include "TreeNode.h"
TreeNode::TreeNode(string item)
{
	m_left = nullptr;
	m_right = nullptr;
	m_item = item;
}
string TreeNode::getItem()
{
	return m_item;
}
void TreeNode::setVal(double value)
{
	m_val = value;
}
double TreeNode::getVal()
{
	return m_val;
}
void TreeNode::setLeft(TreeNode* lnode)
{
	m_left = lnode;
}
void TreeNode::setRight(TreeNode* rnode)
{
	m_right = rnode;
}
TreeNode* TreeNode::getLeft()
{
	return m_left;
}
TreeNode* TreeNode::getRight()
{
	return m_right;
}
