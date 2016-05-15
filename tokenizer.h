#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <iostream>
using namespace std;
class tokenizer
{
private:
	string m_line;
	int i;
	string s;
public:
	tokenizer(string line);
	string next();
};
#endif //TOKENIZER_H
