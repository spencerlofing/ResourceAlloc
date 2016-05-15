#include "week.h"

week::week()
{
	m_hrs = 0.0;
	m_task1 = nullptr;
	m_task2 = nullptr;
	m_task3 = nullptr;
}
week::~week()
{
	delete(m_weekOf);
}
task* week::getTask1()
{
	return m_task1;
}

task* week::getTask2()
{
	return m_task2;
}

task* week::getTask3()
{
	return m_task3;
}

week* week::getNext()
{
	return m_next;
}

double week::getHours()
{
	return m_hrs;
}

date* week::getWeekOf()
{
	return m_weekOf;
}

void week::setTask1(task* task)
{
	m_task1 = task;
}
void week::setTask2(task* task)
{
	m_task2 = task;
}
void week::setTask3(task* task)
{
	m_task3 = task;
}
void week::setHours(double hours)
{
	m_hrs = hours;
}

void week::setNext(week* next)
{
	m_next = next;
}

void week::setWeekOf(date* weekOf)
{
	m_weekOf = weekOf;
}
