#ifndef WEEK_H
#define WEEK_H
#include "task.h"
#include "date.h"
class task;
class week
{
private:
	double m_hrs;
	date* m_weekOf;
	task* m_task1;
	task* m_task2;
	task* m_task3;
	week* m_next;
public:
	week();
	~week();
	void setNext(week* next);
	void setWeekOf(date* weekNum);
	void setTask1(task* task);
	void setTask2(task* task);
	void setTask3(task* task);
	date* getWeekOf();
	week* getNext();
	task* getTask1();
	task* getTask2();
	task* getTask3();
	double getHours();
	void setHours(double hours);
};
#endif //WEEK_H
