#include "exprtoken.h"
exprtoken::exprtoken(string line)
{
	m_line = line;
	i = 0;
	s = "";
}
string exprtoken::next() 
{
	s = "";
	if(isalpha(m_line[i]))
	{
		while((unsigned)i<m_line.size() && isalpha(m_line[i]))
		{
			s = s+m_line[i];
			i++;
		}
	}
	else if(isdigit(m_line[i]))
	{
		while((unsigned)i<m_line.size() && (isdigit(m_line[i]) || m_line[i] == '.'))
		{
			s = s+m_line[i];
			i++;
		}
	}
	else if(m_line[i] == '+' || m_line[i] == '-' || m_line[i] == '*' || m_line[i] == '/' || m_line[i] == '(' || m_line[i] == ')')
	{
		s = s + m_line[i];
		i++;
	}
	else
	{
		i++;
	}
	return s;
}
