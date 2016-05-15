/**
Resource allocation software
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
using namespace std;

#include "person.h"
#include "week.h"
#include "task.h"
#include "tokenizer.h"
#include "date.h"

person* root = nullptr;
person* p_curr  = root;
task** tHeap;
task** sortedTasks;
week* head = nullptr;
week* w_curr = nullptr;
int numTasks = 0;
int currTask = 0;
string startDay;

ofstream outdata;
ifstream people;
ifstream ftask;
string line;
tokenizer* tok;
//Takes in the size of a heap and sorts it to a minheap with the smallest value on top
void heapify(int size)
{
	for(int j = size; log(j)>0; j--)
	{
		for(int i = size; i>0; i--)
		{
			if(tHeap[i]->getPriority()<tHeap[(i-1)/2]->getPriority())
			{
				task* temp = tHeap[i];
				tHeap[i] = tHeap[(i-1)/2];
				tHeap[(i-1)/2] = temp;
			}
		}
	}
}
//Takes a minheap, pops the root and pushes it to a new array, moves the rightmost, lowest value to the root and repeats while for the size of the task heap
void sortHeap()
{
	int num = currTask;
	for(int i = 0; i<=currTask; i++)
	{
		sortedTasks[i] = tHeap[0];
		tHeap[0] = tHeap[num];
		num--;
		heapify(num);
	}
}
//Takes the list of tasks from a file and inserts them into a minheap
//returns a minheap in the form of an array
void insertMinHeap()
{
	string today;
	string nextToken;
	string taskEquation;
	if(getline(ftask, line, '\n'))
	{
		tok = new tokenizer(line);
		nextToken = tok->next();
		nextToken = tok->next();
		today = nextToken;
		delete(tok);
	}
	if(getline(ftask, line, '\n'))
	{
		tok = new tokenizer(line);
		nextToken = tok->next();
		nextToken = tok->next();
		taskEquation = nextToken;
		delete(tok);
	}	
	getline(ftask, line, '\n');
	while(getline(ftask, line, '\n'))
	{
		if(!line.empty())
		{
			tok = new tokenizer(line);
			tHeap[currTask] = new task();
			nextToken = tok->next();
			tHeap[currTask]->setName(nextToken);
			nextToken = tok->next();
			tHeap[currTask]->setDifficulty(atoi(nextToken.c_str()));
			nextToken = tok->next();
			tHeap[currTask]->setHoursLeft(stod(nextToken.c_str()));
			nextToken = tok->next();
			tHeap[currTask]->setDeadline(nextToken);
			tHeap[currTask]->setToday(today);
			tHeap[currTask]->setEquation(taskEquation);
			heapify(currTask);
			currTask++;
			delete(tok);
		}
	}
	currTask--;	
}
void writeFile(person* subTree)
{	
	if(subTree->getLeft() != nullptr)
	{
		writeFile(subTree->getLeft());
	}
	week* Wcurr = subTree->getSchedule();
	outdata << subTree->getName();
	outdata << "\nTask One:";
	while(Wcurr != NULL)
	{
		if(Wcurr->getTask1() != nullptr)
		{
			outdata << "," << Wcurr->getTask1()->getName();
		}
		else
		{
			outdata << ",";
		}
		Wcurr = Wcurr->getNext();
	}
	Wcurr = subTree->getSchedule();
	outdata << "\nTask Two:";
	while(Wcurr != NULL)
	{
		if(Wcurr->getTask2() != nullptr)
		{
			outdata << "," << Wcurr->getTask2()->getName();
		}
		else 
		{
			outdata << ",";
		}
		Wcurr = Wcurr->getNext();
	}
	Wcurr = subTree->getSchedule();
	outdata << "\nTask Three:";
	while(Wcurr != NULL)
	{
		if(Wcurr->getTask3() != nullptr)
		{
			outdata << "," << Wcurr->getTask3()->getName();
		}
		else
		{
			outdata << ",";
		}
		Wcurr = Wcurr->getNext();
	}
	outdata << "\n";
	if(subTree->getRight() != nullptr)
	{
		writeFile(subTree->getRight());
	}
}
week* w_linkedlist()
{
	week* sched = new week();
	//sched->setHours(hrs);
	if(head == nullptr)
	{
		head = sched;	
	}
	else if(w_curr == nullptr)
	{
		head->setNext(sched);
		w_curr = sched;
	}
	else
	{	
		w_curr->setNext(sched);
		w_curr = sched;
	}
	return sched;
}
void p_tree(person* subTree, double score, person* pers)
{
	if(root == nullptr)
	{
		root = pers;	
	}
	else if(score <= subTree->getScore())
	{
		if(subTree->getLeft() == nullptr)
		{
			subTree->setLeft(pers);
		}
		else
		{
			p_tree(subTree->getLeft(), score, pers);
		}
	}
	else if(score > subTree->getScore())
	{	
		if(subTree->getRight() == nullptr)
		{
			subTree->setRight(pers);
		}
		else
		{
			p_tree(subTree->getRight(), score, pers);
		}
	}
}
void assignTasks(person* subTree)
{
	if(subTree->getLeft() != nullptr)
	{
		assignTasks(subTree->getLeft());
	}
	week* currWeek = subTree->getSchedule();
	{
		int j = 0;
		while(j<=currTask && currWeek != nullptr)
		{	
			double hoursLeft  = sortedTasks[j]->getHoursLeft();
			double weekHours = currWeek->getHours();
			double netHours = weekHours-hoursLeft;
			if(sortedTasks[j]->getDeadline()->getHours() > currWeek->getWeekOf()->getHours() && hoursLeft>0)
			{
				if(currWeek->getTask1() == nullptr && weekHours > 0)
				{
					if(netHours > 0 )
					{
						sortedTasks[j]->setHoursLeft(0);
						currWeek->setHours(netHours);
						currWeek->setTask1(sortedTasks[j]);
					}
					else if(netHours < 0)
					{
						sortedTasks[j]->setHoursLeft(fabs(netHours));
						currWeek->setHours(0);
						currWeek->setTask1(sortedTasks[j]);
						currWeek = currWeek->getNext();
					}
					else
					{
						sortedTasks[j]->setHoursLeft(0);
						currWeek->setHours(0);
						currWeek->setTask1(sortedTasks[j]);
						currWeek = currWeek->getNext();	
					}
				
				}
				else if(currWeek->getTask2() == nullptr && weekHours > 0 && hoursLeft>0)
				{
					if(netHours > 0 )
					{
						sortedTasks[j]->setHoursLeft(0);
						currWeek->setHours(netHours);
						currWeek->setTask2(sortedTasks[j]);
					}
					else if(netHours < 0)
					{
						sortedTasks[j]->setHoursLeft(fabs(netHours));
						currWeek->setHours(0);
						currWeek->setTask2(sortedTasks[j]);
						currWeek = currWeek->getNext();
					}
					else
					{
						sortedTasks[j]->setHoursLeft(0);
						currWeek->setHours(0);
						currWeek->setTask2(sortedTasks[j]);
						currWeek = currWeek->getNext();	
					}
				}
				else if(currWeek->getTask3() == nullptr && weekHours > 0 && hoursLeft>0)
				{
					if(netHours > 0 )
					{
						sortedTasks[j]->setHoursLeft(0);
						currWeek->setHours(netHours);
						currWeek->setTask3(sortedTasks[j]);
					}
					else if(netHours < 0)
					{
						sortedTasks[j]->setHoursLeft(fabs(netHours));
						currWeek->setHours(0);
						currWeek->setTask3(sortedTasks[j]);
						currWeek = currWeek->getNext();
					}
					else
					{
						sortedTasks[j]->setHoursLeft(0);
						currWeek->setHours(0);
						currWeek->setTask3(sortedTasks[j]);
						currWeek = currWeek->getNext();	
					}
				}
				else
				{
					currWeek = currWeek->getNext();
				}
			}
			else
			{
				j++;
			}
		}
	}
	if(subTree->getRight() != nullptr)
	{
		assignTasks(subTree->getRight());
	}
}
void peopleTerm(person* subTree)
{
	if(subTree->getLeft() != nullptr)
	{
		peopleTerm(subTree->getLeft());
	}
	if(subTree->getRight() != nullptr)
	{
		peopleTerm(subTree->getRight());
	}
	delete(subTree);
}
void tasksTerm()
{
	for(int i = 0; i<=currTask; i++)
	{
		delete(sortedTasks[i]);
	}
	delete(sortedTasks);
	delete(tHeap);
}
int main(int argc, char** argv)
{
	if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
	{
		std::cout << "Usage: <schedules.csv> <tasks.csv> <output.csv>" << std::endl;
	}
	else
	{
		std::cout << "Working" << std::endl;
		people.open(argv[1]);
		ftask.open(argv[2]);
		outdata.open(argv[3]);
		getline(people, line, '\n');
		getline(people, line, '\n');
		string nextToken;
		string scoreEquation;
		tok = new tokenizer(line);
		startDay = tok->next();
		delete(tok);
		int y, m, d;
		sscanf(startDay.c_str(), "%d.%d.%d", &y, &m, &d);
		if(getline(people, line, '\n'))
		{
			tok = new tokenizer(line);
			nextToken = tok->next();
			nextToken = tok->next();
			scoreEquation = nextToken;
			delete(tok);
		}
		while(people.good())
		{
			getline(people, line, '\n');
			if(!line.empty())
			{
				tok = new tokenizer(line);
				nextToken = tok->next();
				person* pers = new person();
				pers->setName(nextToken);
				nextToken = tok->next();
				pers->setRating(stod(nextToken));
				nextToken = tok->next();
				pers->setCost(stod(nextToken));
				pers->setEquation(scoreEquation);
				nextToken = tok->next();
				head = nullptr;
				w_curr = nullptr;
				while(strcmp(nextToken.c_str(), "") != 0)
				{
					if(stod(nextToken.c_str()) || nextToken == "0")
					{
						week* sched = w_linkedlist();
						sched->setHours(stod(nextToken.c_str()));
						date* weekOf = new date(y, m, d);
						sched->setWeekOf(weekOf);
						if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
						{
							if(d+7 > 31)
							{
								if(m == 12)
								{
									y++;
									m = 1;
								}
								else
								{
									m++;
								}
								d = d + 7 - 31;
							}
							else
							{
								d = d + 7;
							}	
						}
						else if(m == 4 || m == 6 || m == 9 || m == 11)
						{
							if(d + 7 > 30)
							{
								m++;
								d = d + 7 - 30;
							}
							else
							{
								d = d + 7;
							}
						}
						else if(m == 2)
						{
							if(y%4 == 0)
							{
								if(d + 7 > 29)
								{
									m++;
									d = d + 7 - 29;
								}
								else
								{
									d = d + 7;
								}
							}
							else
							{
								if(d + 7 > 28)
								{
									m++;
									d = d + 7 - 28;
								}
								else
								{
									d = d + 7;
								}
							}
						} 
					}
					else
					{
						std::cout << "Invalid hours entered for " << pers->getName() << std::endl;
						return(0);
					}
					nextToken = tok->next();
				}
				sscanf(startDay.c_str(), "%d.%d.%d", &y, &m, &d);
				pers->setSchedule(head);
				p_tree(root, pers->getScore(), pers);
				delete(tok);
			}
		}
		while(getline(ftask, line, '\n'))
		{
			numTasks++;
		}
		tHeap = new task*[numTasks];
		sortedTasks = new task*[numTasks];
		ftask.close();
		ftask.open(argv[2]);
		insertMinHeap();
		sortHeap();
		if(root != nullptr)
		{
			assignTasks(root);
		}
		outdata << "Week of:";
		week* currW = root->getSchedule();
		while(currW != nullptr)
		{
			outdata << "," << currW->getWeekOf()->getYear() << "." << currW->getWeekOf()->getMonth() << "." << currW->getWeekOf()->getDay();
			currW = currW->getNext();
		}
		outdata << '\n';
		writeFile(root);
		outdata.close();
		ftask.close();
		people.close();
		bool finished = true;
		for(int i = 0; i<= currTask; i++)
		{
			if(sortedTasks[i]->getHoursLeft() != 0)
			{
				finished = false;
			}
		}
		if(finished)
		{
			std::cout << "All tasks assigned\n";
		}
		else
		{
			std::cout << "Error processing. Not all tasks assigned\n";
		}
		tasksTerm();
		if(root != nullptr)
		{
			peopleTerm(root);
		}
	}
	return(0);
}
