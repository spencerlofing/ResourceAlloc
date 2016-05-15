#include "person.h"
person::person()
{
	m_rating = 0.0;
	m_cost = 0.0;
	m_score = 0.0;
	m_schedule = nullptr;
	m_name = "";
}
person::~person()
{
	delete(m_tree);
	delete(m_tokenizer);
	week* currWeek = m_schedule;
	week* nextWeek = currWeek->getNext();
	while(currWeek != nullptr)
	{
		delete(currWeek);
		currWeek = nextWeek;
		if(nextWeek != nullptr)
		{
			nextWeek = nextWeek->getNext();
		}
	}
}
string person::getName()
{
	return m_name;
}

person* person::getLeft()
{
	return m_left;
}

person* person::getRight()
{
	return m_right;
}

double person::getScore()
{
	return m_tree->postOrderEval();
	/*m_score = m_cost - m_rating*1000;
	return m_score;*/
}

week* person::getSchedule()
{
	return m_schedule;
}
void person::setCost(double cost)
{
	m_cost = cost;
}
double person::getCost()
{
	return m_cost;
}
double person::getRating()
{
	return m_rating;
}
void person::setName(string name)
{
	m_name = name;
}

void person::setSchedule(week* head)
{
	m_schedule = head;
}

void person::setRating(double rating)
{
	m_rating = rating;
}

void person::setEquation(string equation)
{
	m_equation = equation;
	m_tokenizer = new exprtoken(m_equation);
	m_tree = new BSTExpr(m_tokenizer, nullptr, this);
}
