#ifndef TREENODE_H
#define TREENODE_H

#include <string>
using namespace std;
class TreeNode
{
private:
	TreeNode* m_left;
	TreeNode* m_right;
	double m_val;
	string m_item;
public:
	TreeNode(string item);
	string getItem();
	void setVal(double value);
	double getVal();
	void setLeft(TreeNode* lnode);
	void setRight(TreeNode* rnode);
	TreeNode* getLeft();
	TreeNode* getRight();
};
#endif //TREENODE_H
