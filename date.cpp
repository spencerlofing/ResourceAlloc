#include "date.h"
date::date(int year, int month, int day)
{
	m_year = year;
	m_month = month;
	m_day = day;
}
int date::getYear()
{
	return m_year;
}
int date::getMonth()
{
	return m_month;
}
int date::getDay()
{
	return m_day;
}
int date::getHours()
{
	int hours = m_year*365*24 + ((m_year-1)/4)*24;
	if(m_month > 1)
	{
		hours = hours + 31*24;
	}
	if(m_month > 2)
	{
		hours = hours + 28*24 + (m_year/4)*24 - ((m_year-1)/4)*24;
	}
	if(m_month > 3)
	{
		hours = hours + 31*24;
	}
	if(m_month > 4)
	{
		hours = hours + 30*24;
	}
	if(m_month > 5)
	{
		hours = hours + 31*24;
	}
	if(m_month > 6)
	{
		hours = hours + 30*24;
	}
	if(m_month > 7)
	{
		hours = hours + 31*24;
	}
	if(m_month > 8)
	{
		hours = hours + 31*24;
	}
	if(m_month > 9)
	{
		hours = hours + 31*24;
	}
	if(m_month > 10)
	{
		hours = hours + 31*24;
	}
	if(m_month > 11)
	{
		hours = hours + 30*24;
	}
	hours = hours + (m_day-1)*24;
	return hours;
}
