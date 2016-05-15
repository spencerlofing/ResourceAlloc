#ifndef DATE_H
#define DATE_H

class date
{
private:
	int m_year;
	int m_month;
	int m_day;
public:
	date(int year, int month, int day);
	int getYear();
	int getMonth();
	int getDay();
	int getHours();
};
#endif //DATE_H
