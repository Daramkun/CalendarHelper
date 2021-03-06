#ifndef __CALENDAR_HELPER_H__
#define __CALENDAR_HELPER_H__

namespace daram
{
    enum Day
    {
        Day_Sunday = 0,
        Day_Monday = 1,
        Day_Tuesday = 2,
        Day_Wednesday = 3,
        Day_Thursday = 4,
        Day_Friday = 5,
        Day_Saturday = 6,
    };
    
    enum Month
    {
        Month_January = 1,
        Month_February = 2,
        Month_March = 3,
        Month_April = 4,
        Month_May = 5,
        Month_June = 6,
        Month_July = 7,
        Month_August = 8,
        Month_September = 9,
        Month_October = 10,
        Month_November = 11,
        Month_December = 12,
    };
    
    enum DateTimeUnit
    {
        DateTimeUnit_Seconds,
        DateTimeUnit_Minutes,
        DateTimeUnit_Hours,
        DateTimeUnit_Days,
        DateTimeUnit_Monthes,
        DateTimeUnit_Years,
    };
    
    enum DateOrdering
    {
        DateOrdering_YMD,
        DateOrdering_MDY,
        DateOrdering_DMY,
    };
    
    enum TimeFormat
    {
        TimeFormat_NoTime,
        TimeFormat_24Hour,
        TimeFormat_12Hour,
    };
    
    class DateTime;
    
    class CalendarHelper
    {
    public:
        static char getTotalDaysOfMonth ( short year, char month );
        static Day getFirstDayOfMonth ( short year, char month );
        static void getDateTimeUnit ( long long timeStampDifferents, DateTimeUnit & unit, int & value );
        static bool isLeapYear ( short year );
        
    public:
        static const char* getDayLongString ( Day day );
        static const char* getDayShortString ( Day day );
        static const char* getMonthLongString ( char month );
        static const char* getMonthShortString ( char month );
        
    public:
        static void toString ( char * buffer, DateTime & dateTime, DateOrdering dateOrdering = DateOrdering_YMD, TimeFormat timeFormat = TimeFormat_24Hour );
        
    private:
        CalendarHelper ();
    };
    
    class DateTime
    {
    public:
        static DateTime getNow ();
        
    public:
        DateTime ();
        DateTime ( long long timeStamp );
        DateTime ( short year, char month, char day );
        DateTime ( char hour, char minute, char second );
        DateTime ( short year, char month, char day, char hour, char minute, char second );
        
    public:
        void setYear ( short year );
        void setMonth ( char month );
        void setDay ( char day );
        
        void setHour ( char hour );
        void setMinute ( char minute );
        void setSecond ( char second );
        
        void setDate ( short year, char month, char day );
        void setTime ( char hour, char minute, char second );
        
    public:
        short getYear ();
        char getMonth ();
        char getDay ();
        
        char getHour ();
        char getMinute ();
        char getSecond ();
        
        void getDate ( short & year, char & month, char & day );
        void getTime ( char & hour, char & minute, char & second );
        
    public:
        long long getTimeStamp ();
        void setTimeStamp ( long long timeStamp );
        
    public:
        DateTime getPreviousDay ();
        DateTime getNextDay ();
        
        DateTime getPreviousWeek ();
        DateTime getNextWeek ();
        
        DateTime getPreviousMonth ();
        DateTime getNextMonth ();
        
    public:
        DateTime getPreviousSecond ();
        DateTime getNextSecond ();
        
        DateTime getPreviousMinute ();
        DateTime getNextMinute ();
        
        DateTime getPreviousHour ();
        DateTime getNextHour ();
        
    public:
        int getTotalDaysFrom1970 ();
        
    public:
        bool isToday ();
        bool isThisMonth ();
        bool isSameDay ( DateTime & otherDateTime );
        int dayCompare ( DateTime & otherDateTime );
        
    public:
        bool operator== ( DateTime & dateTime );
        bool operator> ( DateTime & dateTime );
        bool operator< ( DateTime & dateTime );
        
    private:
#ifdef WIN32
#pragma pack ( push, 1 )
#else
#pragma pack ( 1 )
#endif
		short year;
		char month;
		char day;
		char hour;
		char minute;
		char second;
		char _reserved;
#ifdef WIN32
#pragma pack ( pop )
#else
#pragma pack ()
#endif
    };
};
#endif