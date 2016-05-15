#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "week.h"

using namespace std;
class week;
class BSTExpr;
class person
{
private:
	double m_rating;
	double m_cost;
	week* m_schedule;
	double m_score;
	string m_name;
	person* m_left;
	person* m_right;
	BSTExpr* m_tree;
	exprtoken* m_tokenizer;
	string m_equation;
public:
	person();
	~person();
	string getName();
	double getScore();
	person* getLeft();
	person* getRight();
	week* getSchedule();
	double getRating();
	double getCost();
	void setName(string name);
	void setSchedule(week* head);
	void setRating(double rating);
	void setCost(double cost);
	void setEquation(string equation);
	void setLeft(person* left);
	void setRight(person* right);
};

#endif //person
