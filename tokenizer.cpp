#include "tokenizer.h"
tokenizer::tokenizer(string line)
{
	m_line = line;
	i = 0;
	s = "";
}
string tokenizer::next() 
{
	s = "";
	while((unsigned)i<m_line.size() && m_line[i] != ',')
    	{
		s = s+m_line[i];
		i++;
    	}
	if(m_line[i] == ',')
	{
		i++;
	}
	return s;
}
