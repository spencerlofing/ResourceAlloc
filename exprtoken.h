#ifndef EXPRTOKEN_H
#define EXPRTOKEN_H

#include <string>
#include <iostream>
using namespace std;
class exprtoken
{
private:
	string m_line;
	int i;
	string s;
public:
	exprtoken(string line);
	bool hasNext();
	string next();
};

#endif //EXPRTOKEN_H
