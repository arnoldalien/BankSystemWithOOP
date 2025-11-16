
#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
    short _Year;
    short _Month;
    short _Day;

public:

    clsDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(string sDate)
    {
        vector <string> vDate;
        vDate = clsString::Split(sDate, "/");
    
        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(short Day, short Month, short Year)
    {
        _Year = Year;
        _Month = Month;
        _Day = Day;
    }

    clsDate(short DateOrderInYear, short Year)
    {
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);

        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
    }

    void SetYear(short year) {

        _Year = year;
    }

    short GetYear() {

        return _Year;
    }
    __declspec(property(get = GetYear, put = SetYear))  short Year;

    void SetMonth(short month) {

        _Month = month;
    }

    short GetMonth() {

        return _Month;
    }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetDay(short day) {

        _Day = day;
    }

    short GetDay() {

        return _Day;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void Print()
    {
        cout << DateToString() << endl;
    }

    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;

        return clsDate(Day, Month, Year);
    }

    static string GetSystemDateTimeString()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/"
            + to_string(Year) + " - "
            + to_string(Hour) + ":" + to_string(Minute)
            + ":" + to_string(Second));
    }

    static bool IsValidDate(clsDate Date)
    {
        if (Date.Day < 1 || Date.Day > 31)
            return false;

        if (Date.Month < 1 || Date.Month > 12)
            return false;

        if(Date.Month == 2)
        {
            if (IsLeapYear(Date.Year))
            {
                if (Date.Day > 29)
                    return false;
            }
            else
            {
                if (Date.Day > 28)
                    return false;
            }
        }

        short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > DaysInMonth)
            return false;

        return true;
    }

    bool IsValidDate()
    {
        return IsValidDate(*this);
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date._Day) + "/" +
            to_string(Date._Month) + "/" +
            to_string(Date._Year);
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    static bool IsLeapYear(short Year)
    {
        return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
    }

    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return IsLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year);
    }

    static int NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;

        int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? IsLeapYear(Year) ? 29 : 28 : NumberOfDays[Month - 1];
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static int NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    int NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
    }   

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, Year);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

        return arrDayNames[DayOfWeekOrder];

    }

    static string DayShortName(short Day, short Month, short Year)
    {

        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];

    }

    string DayShortName()
    {

        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

        return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];

    }

    static string MonthShortName(short MonthNumber)
    {
        string Monthtext[] = { "Jan", "Feb", "Mar","Apr",
                                "May", "Jun", "Jul","Aug",
                                "Sep", "Oct", "Nov", "Dec"
        };

        return Monthtext[MonthNumber - 1];
    }

    string MonthShortName()
    {
        return MonthShortName(_Month);
    }

    static void PrintMonthCalendar(short Month, short Year)
    {
        int NumberOfDays;
        int Current = DayOfWeekOrder(1, Month, Year); 

        NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        printf("\n  _______________%s_______________\n\n",
            MonthShortName(Month).c_str());

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;
        for (i = 0; i < Current; i++)
            printf("     ");

        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar()
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(int Year)
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", Year);
        printf("  _________________________________\n");

        for (short i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar()
    {
         PrintYearCalendar(_Year);
    }

    static int DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        int TotalDays = 0;

        for (int i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }

        TotalDays += Day;

        return TotalDays;
    }

    int FromTheBeginingOfTheYear()
    {
        return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
    }

    static clsDate GetDateFromDayOrderInYear(int DaysOrderInYear, short Year)
    {
        clsDate Date;

        int RemainingDays = DaysOrderInYear;
        short MonthDays = 0;

        Date._Year = Year;
        Date._Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date._Month++;
            }
            else
            {
                Date._Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    static clsDate DateAddDays(short Days, clsDate Date)
    {
        short RemainingDays = Days + DaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year);
        short MonthDays = 0;

        Date._Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;

                Date._Month++;

                if (Date._Month > 12)
                {
                    Date._Month = 1;
                    Date._Year++;
                }
            }
            else
            {
                Date._Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    void DateAddDays(short HowManyDays)
    {
        *this = DateAddDays(HowManyDays, *this);
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    { 
        return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ?
            (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ?
                Date1._Day < Date2._Day : false)) : false);
    }

    bool IsDate1BeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2) 
    { 
        return  (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ?
            ((Date1._Day == Date2._Day) ? true : false) : false) : false;
    }

    bool IsDate1EqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));;
    }

    bool IsDate1AfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(clsDate Date1)
    {
        return (Date1._Day == NumberOfDaysInAMonth(Date1._Month, Date1._Year));
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(clsDate Date1)
    {
        return (Date1._Month == 12);
    }

    bool IsLastMonthInYear()
    {
        return IsLastMonthInYear(*this);
    }

    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date))
            {
                Date._Day = 1;
                Date._Month = 1;
                Date._Year++;
            }
            else
            {
                Date._Month++;
                Date._Day = 1;
            }
        }
        else
        {
            Date._Day++;
        }

        return Date;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    void AddDays(short Days)
    {
        short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
        short MonthDays = 0;

        _Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(_Month, _Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    static clsDate IncreaseDateByOneWeek(clsDate& Date)
    {
        for (short i = 0; i < 7; i++)
        {
            Date = AddOneDay(Date);
        }

        return Date;
    }

    void IncreaseDateByOneWeek()
    {
       IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(short Weeks ,clsDate& Date)
    {
        for (short i = 0; i < Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }

        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        IncreaseDateByXWeeks(Weeks, *this);
    }

    clsDate IncreaseDateByOneMonth(clsDate& Date)
    {

        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void IncreaseDateByOneMonth()
    {

        IncreaseDateByOneMonth(*this);

    }

    clsDate IncreaseDateByXDays(short Days, clsDate& Date)
    {

        for (short i = 1; i <= Days; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDays(short Days)
    {

        IncreaseDateByXDays(Days, *this);
    }

    clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
    {

        for (short i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        IncreaseDateByXMonths(Months, *this);
    }

    static clsDate IncreaseDateByOneYear(clsDate& Date)
    {
        Date.Year++;
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    clsDate IncreaseDateByXYears(short Years, clsDate& Date)
    {
        Date.Year += Years;
        return Date;

    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    clsDate IncreaseDateByOneDecade(clsDate& Date)
    {
        Date.Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    clsDate IncreaseDateByXDecades(short Decade, clsDate& Date)
    {
        Date.Year += Decade * 10;
        return Date;
    }

    void IncreaseDateByXDecades(short Decade)
    {
        IncreaseDateByXDecades(Decade, *this);
    }

    clsDate IncreaseDateByOneCentury(clsDate& Date)
    {
        Date.Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    clsDate IncreaseDateByOneMillennium(clsDate& Date)
    {
        Date.Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }
    
    static clsDate DecreaseDateByOneDay(clsDate& Date)
    {
        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Month = 12;
                Date.Day = 31;
                Date.Year--;
            }
            else
            {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else
        {
            Date.Day--;
        }

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
    {

        for (short i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate& Date)
    {

        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
    {

        for (short i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
    {

        for (short i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        DecreaseDateByXMonths(Months, *this);
    }

    static clsDate DecreaseDateByOneYear(clsDate& Date)
    {

        Date.Year--;
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
    {

        Date.Year -= Years;
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate& Date)
    {
        Date.Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
    {

        Date.Year -= Decades * 10;
        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        DecreaseDateByXDecades(Decades, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate& Date)
    {
        Date.Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate& Date)
    {
        Date.Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    static short IsEndOfWeek(clsDate Date)
    {
        return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
    }

    short IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
        return  (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd()
    {
        return  IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return  IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date)
    {
        clsDate EndOfMonthDate;

        EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
        EndOfMonthDate.Month = Date.Month;
        EndOfMonthDate.Year = Date.Year;

        return GetDifferenceInDays(Date, EndOfMonthDate, true);
    }

    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date)
    {
        clsDate EndOfYearDate;

        EndOfYearDate.Day = 31;
        EndOfYearDate.Month = 12;
        EndOfYearDate.Year = Date.Year;

        return GetDifferenceInDays(Date, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }

    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate;

        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = true)
    {
        int Days = 0;
        short SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Date1 = AddOneDay(Date1);
            Days++;
        }

        if (IncludeEndDay)
            Days++;

        return Days * SwapFlagValue;
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = true)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static int CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, GetSystemDate(), true);
    }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;

        return enDateCompare::After;

    }

    enDateCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }

    static short CalculateBusinessDays(clsDate FromDate, clsDate DateTo)
    {
        short DaysCount = 0;
        while (IsDate1BeforeDate2(FromDate, DateTo))
        {
            if (IsBusinessDay(FromDate))
            {
                DaysCount++;
            }

            FromDate = AddOneDay(FromDate);
        }

        return DaysCount;
    }

    static short CalculateVacationDays(clsDate FromDate, clsDate DateTo)
    {
        return CalculateBusinessDays(FromDate, DateTo);
    }

    short CalculateVacationDays(clsDate DateTo)
    {
        return CalculateVacationDays(*this, DateTo);
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        while (IsWeekEnd(DateFrom))
        {
            DateFrom = AddOneDay(DateFrom);
        }

        short Count = 0;

        while (Count < VacationDays)
        {
            DateFrom = AddOneDay(DateFrom);

            if (!IsWeekEnd(DateFrom))
                Count++;
        }

        return DateFrom;
    }
};