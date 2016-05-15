#include "BSTExpr.h"

BSTExpr::BSTExpr(exprtoken* TokenIter, task* Task, person* pers)
{
	m_root = nullptr;
	m_tokenIter = TokenIter;
	nextToken = m_tokenIter->next();
	m_task = Task;
	m_pers = pers;
}
BSTExpr::~BSTExpr()
{
	deletion(m_root);
}
void BSTExpr::deletion(TreeNode* subTree)
{
	if(subTree->getLeft() != nullptr)
	{
		deletion(subTree->getLeft());
	}
	if(subTree->getRight() != nullptr)
	{
		deletion(subTree->getRight());
	}
	delete(subTree);
}
double BSTExpr::postOrderEval()
{
	insert();
	return postOrderEval(m_root);
}
double BSTExpr::postOrderEval(TreeNode* subTree)
{
	double operand1;
	double operand2;
	if(subTree->getLeft() != nullptr)
	{
		operand1 = postOrderEval(subTree->getLeft());
	}
	if(subTree->getRight() != nullptr)
	{
		operand2 = postOrderEval(subTree->getRight());
	}
	/*std::cout << operand1 << std::endl;
	std::cout << operand2 << std::endl;
	std::cout << subTree->getItem() << std::endl;*/
	if(isdigit(subTree->getItem()[0]) || strcmp(toLowerCase(subTree->getItem()).c_str(), "deadline") == 0 || strcmp(toLowerCase(subTree->getItem()).c_str(), "today") == 0 || strcmp(toLowerCase(subTree->getItem()).c_str(), "hoursleft") == 0 || strcmp(toLowerCase(subTree->getItem()).c_str(), "difficulty") == 0 || strcmp(toLowerCase(subTree->getItem()).c_str(), "rating") == 0 || strcmp(toLowerCase(subTree->getItem()).c_str(), "cost") == 0)
	{
		return subTree->getVal();
	}
	else if(strcmp(subTree->getItem().c_str(), "+") == 0)
	{
		return operand1 + operand2;
	}
	else if(strcmp(subTree->getItem().c_str(), "-") == 0)
	{
		return operand1 - operand2;
	}
	else if(strcmp(subTree->getItem().c_str(), "*") == 0)
	{
		return operand1 * operand2;
	}
	else if(strcmp(subTree->getItem().c_str(), "/") == 0)
	{
		return operand1/operand2;
	}
	else
	{
		std::cout << "Invalid Expression" << std::endl;
		exit(0);
	}
}

void BSTExpr::insert()
{
	if(!nextToken.empty())
	{
		m_root = expr();
	}
	if(!nextToken.empty())
	{
		std::cout << "end of line expected" << std::endl;
	}
}
//expr = term + term | term - term | term
TreeNode* BSTExpr::expr()
{
	TreeNode* lnode = term();
    	TreeNode* rnode;
    	if(!nextToken.empty() && (strcmp(nextToken.c_str(), "+") == 0 || strcmp(nextToken.c_str(), "-") == 0))
    	{
		string op = nextToken;
    		nextToken = m_tokenIter->next();
    		rnode = term();
    		TreeNode* exp = new TreeNode(op);
		exp->setLeft(lnode);
		exp->setRight(rnode);
    		while(!nextToken.empty() && (strcmp(nextToken.c_str(), "+") == 0 || strcmp(nextToken.c_str(), "-") == 0))
    		{
			op = nextToken;
    			lnode = exp;
    			nextToken = m_tokenIter->next();
    			rnode = term();
    			exp = new TreeNode(op);
			exp->setLeft(lnode);
			exp->setRight(rnode);
    		}
    		return exp;
    	}
    	return lnode; 	
}
//term = factor * factor | factor / factor | factor
TreeNode* BSTExpr::term()
{
	TreeNode* lnode = factor();
	TreeNode* rnode;
	if(!nextToken.empty() && (strcmp(nextToken.c_str(), "*") == 0 || strcmp(nextToken.c_str(), "/") == 0))
	{
		string op = nextToken;
		//std::cout << op << std::endl;
		nextToken = m_tokenIter->next();
		rnode = factor();
		TreeNode* term = new TreeNode(op);
		term->setLeft(lnode);
		term->setRight(rnode);
		while(!nextToken.empty() && (strcmp(nextToken.c_str(), "*") == 0 || strcmp(nextToken.c_str(), "/") == 0))
		{
			op = nextToken;
			lnode = term;
    			nextToken = m_tokenIter->next();
    			rnode = factor();
    			term = new TreeNode(op);
			term->setLeft(lnode);
			term->setRight(rnode);
		}
		return term;
	}
	return lnode;
}
string BSTExpr::toLowerCase(string str)
{	
	int differ = 'A'-'a';
	for (unsigned int i=0; i <strlen(str.c_str());i++)
	{
		if (str[i]>='A' && str[i]<='Z')
		{
			str[i] = str[i]-differ;
		}
	}
	return str;
}
//factor = "deadline" | "today" | "hoursleft" | (expr)
TreeNode* BSTExpr::factor()
{
	//std::cout << nextToken << std::endl;
	TreeNode* node;
	if(isdigit(nextToken[0]))
	{
		node = new TreeNode(nextToken);
		node->setVal(stod(nextToken));
		nextToken = m_tokenIter->next();
	}
	else if(strcmp(nextToken.c_str(), "(") == 0)
	{
		nextToken = m_tokenIter->next();
		node = expr();
		if(strcmp(nextToken.c_str(), ")") == 0)
		{
			nextToken = m_tokenIter->next();
		}
		else
		{
			std::cout << "Invalid input for priority equation" << std::endl;
			exit(0);
		}
	}
	else if(m_task != nullptr)
	{
		node = new TreeNode(nextToken);
		if(strcmp(toLowerCase(nextToken).c_str(), "deadline") == 0)
		{
			node->setVal(m_task->getDeadline()->getHours());
		}
		else if(strcmp(toLowerCase(nextToken).c_str(), "today") == 0)
		{
			node->setVal(m_task->getToday()->getHours());
		}
		else if(strcmp(toLowerCase(nextToken).c_str(), "hoursleft") == 0)
		{
			node->setVal(m_task->getHoursLeft());
		}
		else if(strcmp(toLowerCase(nextToken).c_str(), "difficulty") == 0)
		{
			node->setVal(m_task->getDifficulty());
		}
		nextToken = m_tokenIter->next();
	}
	else if(m_pers != nullptr)
	{
		node = new TreeNode(nextToken);
		if(strcmp(toLowerCase(nextToken).c_str(), "rating") == 0)
		{
			node->setVal(m_pers->getRating());
		}
		else if(strcmp(toLowerCase(nextToken).c_str(), "cost") == 0)
		{
			node->setVal(m_pers->getCost());
		}
		nextToken = m_tokenIter->next();
	}
	else
	{
		std::cout << "Invalid input for priority equation" << std::endl;
		exit(0);
	}
	return node;
}
