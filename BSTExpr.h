#ifndef BSTEXPR_H
#define BSTEXPR_H
#include "exprtoken.h"
#include "TreeNode.h"
#include "task.h"
#include "person.h"
#include <cctype>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class person;
class task;
class BSTExpr
{
private:
	TreeNode* m_root;
	exprtoken* m_tokenIter;
	string nextToken;
	task* m_task;
	person* m_pers;
public:
	BSTExpr(exprtoken* TokenIter, task* Task, person* pers);
	~BSTExpr();
	void deletion(TreeNode* subTree);	
	double postOrderEval();
	double postOrderEval(TreeNode* subTree);
	void insert();
	TreeNode* expr();
	string toLowerCase(string str);
	TreeNode* factor();
	TreeNode* term();
};
#endif //BSTEXPR_H
