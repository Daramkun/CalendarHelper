#define _CRT_SECURE_NO_WARNINGS
#include "CalendarHelper.h"
#include <ctime>
#include <cstdio>

using namespace daram;

#pragma mark -

char daram::CalendarHelper::getTotalDaysOfMonth ( short year, char month )
{
	switch ( month )
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
	case 4: case 6: case 9: case 11: return 30;
	case 2:
        if ( CalendarHelper::isLeapYear( year ) ) return 29;
		else return 28;
	}
	return -1;
}

Day daram::CalendarHelper::getFirstDayOfMonth ( short year, char month )
{
	int dayCode = 0;
	int x1 = ( int ) ( ( year - 1 ) / 4.0f ), x2 = ( int ) ( ( year - 1 ) / 100.0f ), x3 = ( int ) ( ( year - 1 ) / 400.0f );
	dayCode = ( year + x1 - x2 + x3 ) % 7;
	for ( int i = 1; i < month; ++i )
		dayCode += CalendarHelper::getTotalDaysOfMonth ( year, i );
	return ( Day ) ( dayCode % 7 );
}

void daram::CalendarHelper::getDateTimeUnit ( long long timeStampDifferents, DateTimeUnit & unit, int & value )
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

bool daram::CalendarHelper::isLeapYear ( short year )
{
    return year % 100 == 0 && year % 400 == 0 && year % 4;
}

const char* daram::CalendarHelper::getDayLongString ( Day day )
{
    switch ( day )
    {
        case Day_Sunday: return "Sunday";
        case Day_Monday: return "Monday";
        case Day_Tuesday: return "Tuesday";
        case Day_Wednesday: return "Wednesday";
        case Day_Thursday: return "Thursday";
        case Day_Friday: return "Friday";
        case Day_Saturday: return "Saturday";
            
        default: return nullptr;
    }
}

const char* daram::CalendarHelper::getDayShortString ( Day day )
{
    switch ( day )
    {
        case Day_Sunday: return "SUN";
        case Day_Monday: return "MON";
        case Day_Tuesday: return "TUE";
        case Day_Wednesday: return "WED";
        case Day_Thursday: return "THU";
        case Day_Friday: return "FRI";
        case Day_Saturday: return "SAT";
            
        default: return nullptr;
    }
}

const char* daram::CalendarHelper::getMonthLongString ( char month )
{
    switch ( month )
    {
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
            
        default: return nullptr;
    }
}

const char* daram::CalendarHelper::getMonthShortString ( char month )
{
    switch ( month )
    {
        case 1: return "JAN";
        case 2: return "FEB";
        case 3: return "MAR";
        case 4: return "APR";
        case 5: return "MAY";
        case 6: return "JUN";
        case 7: return "JUL";
        case 8: return "AUG";
        case 9: return "SEP";
        case 10: return "OCT";
        case 11: return "NOV";
        case 12: return "DEC";
            
        default: return nullptr;
    }
}

void daram::CalendarHelper::toString ( char * buffer, DateTime & dateTime, DateOrdering dateOrdering, TimeFormat timeFormat )
{
    switch (dateOrdering)
    {
        case DateOrdering_YMD:
            switch (timeFormat)
            {
                case TimeFormat_24Hour:
                    sprintf(buffer, "%4d-%2d-%2d %2d:%2d:%2d", dateTime.getYear(), dateTime.getMonth(), dateTime.getDay(), dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond());
                    break;
                case TimeFormat_12Hour:
                    sprintf(buffer, "%4d-%2d-%2d %s %2d:%2d:%2d", dateTime.getYear(), dateTime.getMonth(), dateTime.getDay(), dateTime.getHour() > 12 ? "PM" : "AM", dateTime.getHour() % 12, dateTime.getMinute(), dateTime.getSecond());
                    break;
                    
                default:
                    sprintf(buffer, "%4d-%2d-%2d", dateTime.getYear(), dateTime.getMonth(), dateTime.getDay());
                    break;
            }
            break;
        case DateOrdering_MDY:
            switch (timeFormat)
            {
                case TimeFormat_24Hour:
                    sprintf(buffer, "%2d-%2d-%4d %2d:%2d:%2d", dateTime.getMonth(), dateTime.getDay(), dateTime.getYear(), dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond());
                    break;
                case TimeFormat_12Hour:
                    sprintf(buffer, "%2d-%2d-%4d %s %2d:%2d:%2d", dateTime.getMonth(), dateTime.getDay(), dateTime.getYear(), dateTime.getHour() > 12 ? "PM" : "AM", dateTime.getHour() % 12, dateTime.getMinute(), dateTime.getSecond());
                    break;
                
                default:
                    sprintf(buffer, "%2d-%2d-%4d", dateTime.getMonth(), dateTime.getDay(), dateTime.getYear());
                    break;
            }
            break;
        case DateOrdering_DMY:
            
            switch (timeFormat)
            {
                case TimeFormat_24Hour:
                    sprintf(buffer, "%2d-%2d-%4d %2d:%2d:%2d", dateTime.getDay(), dateTime.getMonth(), dateTime.getYear(), dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond());
                    break;
                case TimeFormat_12Hour:
                    sprintf(buffer, "%2d-%2d-%4d %s %2d:%2d:%2d", dateTime.getDay(), dateTime.getMonth(), dateTime.getYear(), dateTime.getHour() > 12 ? "PM" : "AM", dateTime.getHour() % 12, dateTime.getMinute(), dateTime.getSecond());
                    break;
                
                default:
                    sprintf(buffer, "%2d-%2d-%4d", dateTime.getDay(), dateTime.getMonth(), dateTime.getYear());
                    break;
            }
            break;
            
        default: return;
    }
}

daram::CalendarHelper::CalendarHelper () { }

#pragma mark -

DateTime daram::DateTime::getNow ()
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

daram::DateTime::DateTime () { year = hour = minute = second = 0; month = day = 1; }
daram::DateTime::DateTime ( long long timeStamp ) { setTimeStamp ( timeStamp ); }
daram::DateTime::DateTime ( short year, char month, char day ) { this->year = year; this->month = month; this->day = day; }
daram::DateTime::DateTime ( char hour, char minute, char second ) { this->hour = hour; this->minute = minute; this->second = second; }
daram::DateTime::DateTime ( short year, char month, char day, char hour, char minute, char second )
{
	this->year = year; this->month = month; this->day = day;
	this->hour = hour; this->minute = minute; this->second = second;
}

void daram::DateTime::setYear ( short year ) { this->year = year; }
void daram::DateTime::setMonth ( char month ) { this->month = month; }
void daram::DateTime::setDay ( char day ) { this->day = day; }
void daram::DateTime::setHour ( char hour ) { this->hour = hour; }
void daram::DateTime::setMinute ( char minute ) { this->minute = minute; }
void daram::DateTime::setSecond ( char second ) { this->second = second; }

void daram::DateTime::setDate ( short year, char month, char day ) { this->year = year; this->month = month; this->day = day; }
void daram::DateTime::setTime ( char hour, char minute, char second ) { this->hour = hour; this->minute = minute; this->second = second; }

short daram::DateTime::getYear () { return year; }
char daram::DateTime::getMonth () { return month; }
char daram::DateTime::getDay () { return day; }
char daram::DateTime::getHour () { return hour; }
char daram::DateTime::getMinute () { return minute; }
char daram::DateTime::getSecond () { return second; }

void daram::DateTime::getDate ( short & year, char & month, char & day ) { year = this->year; month = this->month; day = this->day; }
void daram::DateTime::getTime ( char & hour, char & minute, char & second ) { hour = this->hour; minute = this->minute; second = this->second; }

long long daram::DateTime::getTimeStamp ()
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

void daram::DateTime::setTimeStamp ( long long timeStamp )
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

DateTime daram::DateTime::getPreviousDay ()
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

DateTime daram::DateTime::getNextDay ()
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


DateTime daram::DateTime::getPreviousWeek ()
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

DateTime daram::DateTime::getNextWeek ()
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


DateTime daram::DateTime::getPreviousMonth ()
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

DateTime daram::DateTime::getNextMonth ()
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

DateTime daram::DateTime::getPreviousSecond ()
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

DateTime daram::DateTime::getNextSecond ()
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

DateTime daram::DateTime::getPreviousMinute ()
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

DateTime daram::DateTime::getNextMinute ()
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

DateTime daram::DateTime::getPreviousHour ()
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

DateTime daram::DateTime::getNextHour ()
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

int daram::DateTime::getTotalDaysFrom1970 ()
{
	int totalDays = 0;
	for ( int i = 1970; i < year; ++i )
		totalDays += ( i % 4 == 0 && i % 100 == 0 && i % 400 == 0 ) ? 366 : 365;
	for ( int i = 1; i < month; ++i )
		totalDays += CalendarHelper::getTotalDaysOfMonth ( year, i );
	totalDays += day;
	return totalDays;
}

bool daram::DateTime::isToday ()
{
    DateTime now = DateTime::getNow ();
	return isSameDay ( now );
}

bool daram::DateTime::isThisMonth ()
{
	DateTime now = DateTime::getNow ();
	return ( year == now.year && month == now.month );
}

bool daram::DateTime::isSameDay ( DateTime & otherDateTime )
{
	return otherDateTime.year == year && otherDateTime.month == month && otherDateTime.day == day;
}

int daram::DateTime::dayCompare ( DateTime & otherDateTime )
{
	return getTotalDaysFrom1970 () - otherDateTime.getTotalDaysFrom1970 ();
}

bool daram::DateTime::operator== ( DateTime& dateTime )
{
	return dateTime.year == year && dateTime.month == month && dateTime.day == day &&
		dateTime.hour == hour && dateTime.minute == minute && dateTime.second == second;
}

bool daram::DateTime::operator> ( DateTime & dateTime )
{
	return getTimeStamp () > dateTime.getTimeStamp ();
}

bool daram::DateTime::operator< ( DateTime & dateTime )
{
	return getTimeStamp () < dateTime.getTimeStamp ();
}