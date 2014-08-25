#include "../CalendarHelper/CalendarHelper.h"
#include <cstdio>

int main ( void )
{
	daram::DateTime dateTime = daram::DateTime::getNow ();

	printf ( "%4d/%02d/%02d %02d:%02d:%02d (%d)",
		dateTime.getYear (), dateTime.getMonth (), dateTime.getDay (),
		dateTime.getHour (), dateTime.getMinute (), dateTime.getSecond (),
		daram::CalendarHelper::getFirstDayOfMonth ( dateTime.getYear (), dateTime.getMonth () )
		);

	while ( true )
	{
		dateTime = dateTime.getNextSecond ();
		printf ( "\r%4d/%02d/%02d %02d:%02d:%02d (%d)",
			dateTime.getYear (), dateTime.getMonth (), dateTime.getDay (),
			dateTime.getHour (), dateTime.getMinute (), dateTime.getSecond (),
			daram::CalendarHelper::getFirstDayOfMonth ( dateTime.getYear (), dateTime.getMonth () )
			);
	}

	return 0;
}