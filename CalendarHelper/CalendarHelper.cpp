#define _CRT_SECURE_NO_WARNINGS
#include "CalendarHelper.h"
#include <ctime>

using namespace daram;

char CalendarHelper::getTotalDaysOfMonth ( int year, int month )
{
	switch ( month )
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		if ( year % 100 == 0 && year % 400 == 0 && year % 4 )
			return 29;
		else return 28;
	}
	return -1;
}

Day CalendarHelper::getFirstDayOfMonth ( int year, int month )
{
	int dayCode = 0;
	int x1 = ( int ) ( ( year - 1 ) / 4.0f ), x2 = ( int ) ( ( year - 1 ) / 100.0f ), x3 = ( int ) ( ( year - 1 ) / 400.0f );
	dayCode = ( year + x1 - x2 + x3 ) % 7;
	for ( int i = 1; i < month; ++i )
		dayCode += CalendarHelper::getTotalDaysOfMonth ( year, i );
	return ( Day ) ( dayCode % 7 );
}

void CalendarHelper::getDateTimeUnit ( long long timeStampDifferents, DateTimeUnit & unit, int & value )
{
	if ( timeStampDifferents <= 60 )
	{
		unit = DateTimeUnit_Seconds;
		value = ( int ) timeStampDifferents;
	}
	else if ( timeStampDifferents <= 3600 )
	{
		unit = DateTimeUnit_Minutes;
		value = ( int ) timeStampDifferents / 60;
	}
	else if ( timeStampDifferents <= 86400 )
	{
		unit = DateTimeUnit_Hours;
		value = ( int ) timeStampDifferents / 60 / 60;
	}
	else if ( timeStampDifferents <= 2678400 )
	{
		unit = DateTimeUnit_Days;
		value = ( int ) timeStampDifferents / 60 / 60 / 24;
	}
	else if ( timeStampDifferents <= 32140800 )
	{
		unit = DateTimeUnit_Monthes;
		value = ( int ) timeStampDifferents / 60 / 60 / 24 / 31;
	}
	else
	{
		unit = DateTimeUnit_Years;
		value = ( int ) timeStampDifferents / 60 / 60 / 24 / 31 / 12;
	}
}

CalendarHelper::CalendarHelper () { }

DateTime DateTime::getNow ()
{
    DateTime dateTime; dateTime.setTimeStamp (
#ifdef WIN32
                                              _time64 ( nullptr )
#else
                                              time ( nullptr )
#endif
                                              );
    return dateTime;
}

DateTime::DateTime () { year = month = day = hour = minute = second = 0; }
DateTime::DateTime ( long long timeStamp ) { setTimeStamp ( timeStamp ); }
DateTime::DateTime ( short year, char month, char day ) { this->year = year; this->month = month; this->day = day; }
DateTime::DateTime ( char hour, char minute, char second ) { this->hour = hour; this->minute = minute; this->second = second; }
DateTime::DateTime ( short year, char month, char day, char hour, char minute, char second )
{
	this->year = year; this->month = month; this->day = day;
	this->hour = hour; this->minute = minute; this->second = second;
}

void DateTime::setYear ( short year ) { this->year = year; }
void DateTime::setMonth ( char month ) { this->month = month; }
void DateTime::setDay ( char day ) { this->day = day; }
void DateTime::setHour ( char hour ) { this->hour = hour; }
void DateTime::setMinute ( char minute ) { this->minute = minute; }
void DateTime::setSecond ( char second ) { this->second = second; }

void DateTime::setDate ( short year, char month, char day ) { this->year = year; this->month = month; this->day = day; }
void DateTime::setTime ( char hour, char minute, char second ) { this->hour = hour; this->minute = minute; this->second = second; }

short DateTime::getYear () { return year; }
char DateTime::getMonth () { return month; }
char DateTime::getDay () { return day; }
char DateTime::getHour () { return hour; }
char DateTime::getMinute () { return minute; }
char DateTime::getSecond () { return second; }

void DateTime::getDate ( short & year, char & month, char & day ) { year = this->year; month = this->month; day = this->day; }
void DateTime::getTime ( char & hour, char & minute, char & second ) { hour = this->hour; minute = this->minute; second = this->second; }

long long DateTime::getTimeStamp ()
{
	tm time = { 0, };
	time.tm_year = year - 1900;
	time.tm_mon = month - 1;
	time.tm_mday = day;

	time.tm_hour = hour;
	time.tm_min = minute;
	time.tm_sec = second;

#ifdef WIN32
	return _mktime64 ( &time );
#else
    return mktime ( &time );
#endif
}

void DateTime::setTimeStamp ( long long timeStamp )
{
	tm time = { 0, };
#ifdef WIN32
	_localtime64_s ( &time, &timeStamp );
#else
    localtime_r ( ( time_t* ) &timeStamp, &time );
#endif

	year = time.tm_year + 1900;
	month = time.tm_mon + 1;
	day = time.tm_mday;

	hour = time.tm_hour;
	minute = time.tm_min;
	second = time.tm_sec;
}

DateTime DateTime::getPreviousDay ()
{
	DateTime dateTime = *this;
	--dateTime.day;
	if ( dateTime.day < 1 )
	{
		--dateTime.month;
		if ( dateTime.month < 1 )
		{
			--dateTime.year;
			dateTime.month = 12;
		}
		dateTime.day = CalendarHelper::getTotalDaysOfMonth ( dateTime.year, dateTime.month );
	}
	return dateTime;
}

DateTime DateTime::getNextDay ()
{
	DateTime dateTime = *this;
	++dateTime.day;
	if ( dateTime.day >= CalendarHelper::getTotalDaysOfMonth ( dateTime.year, dateTime.month ) )
	{
		++dateTime.month;
		if ( dateTime.month > 12 )
		{
			++dateTime.year;
			dateTime.month = 1;
		}
		dateTime.day = 1;
	}
	return dateTime;
}


DateTime DateTime::getPreviousWeek ()
{
	DateTime dateTime = *this;
	dateTime.day -= 7;
	if ( dateTime.day < 1 )
	{
		--dateTime.month;
		if ( dateTime.month < 1 )
		{
			dateTime.year -= 1;
			dateTime.month = 12;
		}
		dateTime.day = CalendarHelper::getTotalDaysOfMonth ( dateTime.year, dateTime.month ) + dateTime.day;
	}
	return dateTime;
}

DateTime DateTime::getNextWeek ()
{
	DateTime dateTime = *this;
	dateTime.day += 7;
	int temp;
	if ( dateTime.day > ( temp = CalendarHelper::getTotalDaysOfMonth ( dateTime.year, dateTime.month ) ) )
	{
		++dateTime.month;
		if ( dateTime.month > 12 )
		{
			++dateTime.year;
			dateTime.month = 1;
		}
		dateTime.day = dateTime.day - temp;
	}
	return dateTime;
}


DateTime DateTime::getPreviousMonth ()
{
	DateTime dateTime = *this;
	--dateTime.month;
	if ( dateTime.month < 1 )
	{
		dateTime.month = 12;
		--dateTime.year;
	}
	return dateTime;
}

DateTime DateTime::getNextMonth ()
{
	DateTime dateTime = *this;
	++dateTime.month;
	if ( dateTime.month > 12 )
	{
		dateTime.month = 1;
		++dateTime.year;
	}
	return dateTime;
}

DateTime DateTime::getPreviousSecond ()
{
	DateTime dateTime = *this;
	--dateTime.second;
	if ( dateTime.second < 1 )
	{
		--dateTime.minute;
		dateTime.second = 59;
		if ( dateTime.minute < 1 )
		{
			--dateTime.hour;
			dateTime.minute = 59;
			if ( dateTime.hour < 1 )
			{
				dateTime.hour = 23;
				dateTime = dateTime.getPreviousDay ();
			}
		}
	}
	return dateTime;
}

DateTime DateTime::getNextSecond ()
{
	DateTime dateTime = *this;
	++dateTime.second;
	if ( dateTime.second > 59 )
	{
		++dateTime.minute;
		dateTime.second = 0;
		if ( dateTime.minute > 59 )
		{
			++dateTime.hour;
			dateTime.minute = 0;
			if ( dateTime.hour > 23 )
			{
				dateTime.hour = 1;
				dateTime = dateTime.getNextDay ();
			}
		}
	}
	return dateTime;
}

DateTime DateTime::getPreviousMinute ()
{
	DateTime dateTime = *this;
	--dateTime.minute;
	if ( dateTime.minute < 1 )
	{
		--dateTime.hour;
		dateTime.minute = 59;
		if ( dateTime.hour < 1 )
		{
			dateTime.hour = 23;
			dateTime = dateTime.getPreviousDay ();
		}
	}
	return dateTime;
}

DateTime DateTime::getNextMinute ()
{
	DateTime dateTime = *this;
	++dateTime.minute;
	if ( dateTime.minute > 59 )
	{
		++dateTime.hour;
		dateTime.minute = 0;
		if ( dateTime.hour > 23 )
		{
			dateTime.hour = 1;
			dateTime = dateTime.getNextDay ();
		}
	}
	return dateTime;
}

DateTime DateTime::getPreviousHour ()
{
	DateTime dateTime = *this;
	--dateTime.hour;
	if ( dateTime.hour < 1 )
	{
		dateTime.hour = 23;
		dateTime = dateTime.getPreviousDay ();
	}
	return dateTime;
}

DateTime DateTime::getNextHour ()
{
	DateTime dateTime = *this;
	++dateTime.hour;
	dateTime.minute = 59;
	if ( dateTime.hour > 23 )
	{
		dateTime.hour = 1;
		dateTime = dateTime.getNextDay ();
	}
	return dateTime;
}

int DateTime::getTotalDaysFrom1970 ()
{
	int totalDays = 0;
	for ( int i = 1970; i < year; ++i )
		totalDays += ( i % 4 == 0 && i % 100 == 0 && i % 400 == 0 ) ? 366 : 365;
	for ( int i = 1; i < month; ++i )
		totalDays += CalendarHelper::getTotalDaysOfMonth ( year, i );
	totalDays += day;
	return totalDays;
}

bool DateTime::isToday ()
{
    DateTime now = DateTime::getNow ();
	return isSameDay ( now );
}

bool DateTime::isThisMonth ()
{
	DateTime now = DateTime::getNow ();
	return ( year == now.year && month == now.month );
}

bool DateTime::isSameDay ( DateTime & otherDateTime )
{
	return otherDateTime.year == year && otherDateTime.month == month && otherDateTime.day == day;
}

int DateTime::dayCompare ( DateTime & otherDateTime )
{
	return getTotalDaysFrom1970 () - otherDateTime.getTotalDaysFrom1970 ();
}

bool DateTime::operator== ( DateTime& dateTime )
{
	return dateTime.year == year && dateTime.month == month && dateTime.day == day &&
		dateTime.hour == hour && dateTime.minute == minute && dateTime.second == second;
}

bool DateTime::operator> ( DateTime & dateTime )
{
	return getTimeStamp () > dateTime.getTimeStamp ();
}

bool DateTime::operator< ( DateTime & dateTime )
{
	return getTimeStamp () < dateTime.getTimeStamp ();
}