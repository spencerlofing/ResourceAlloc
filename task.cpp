#include "task.h"
task::task()
{
	m_hrsLeft = 0.0;
	m_difficulty = 3.0;
	m_name = "";
	m_priority = 0.0;
}
task::~task()
{
	delete(m_deadline);
	delete(m_today);
	delete(m_tokenizer);
	delete(m_tree);
}
void task::setHoursLeft(double hrsLeft)
{
	m_hrsLeft = hrsLeft;
}
void task::setName(string name)
{
	m_name = name;
}
void task::setDeadline(string deadline)
{
	int y, m, d;
	sscanf(deadline.c_str(), "%d.%d.%d", &y, &m, &d);
	m_deadline = new date(y, m, d);
}
void task::setDifficulty(int difficulty)
{
	m_difficulty = difficulty;
}
double task::getHoursLeft()
{
	return m_hrsLeft;
}
string task::getName()
{
	return m_name;
}
date* task::getDeadline()
{
	return m_deadline;
}
date* task::getToday()
{
	return m_today;
}
void task::setToday(string today)
{
	int y, m, d;
	sscanf(today.c_str(), "%d.%d.%d", &y, &m, &d);
	m_today = new date(y, m, d);
}
int task::getDifficulty()
{
	return m_difficulty;
}
void task::setEquation(string equation)
{
	m_equation = equation;
	m_tokenizer = new exprtoken(equation);
	m_tree = new BSTExpr(m_tokenizer, this, nullptr);
}
double task::getPriority()
{
	return m_tree->postOrderEval();
	//return m_deadline->getHours() - m_today->getHours() - m_hrsLeft*(m_difficulty/3.0);
	//-(m_hrsLeft*(m_difficulty/3.0))	
}

