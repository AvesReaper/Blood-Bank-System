#pragma once
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

class Date
{
public:
    int day, month, year;

    /// Returns date object for the current date
    Date()
    {
        std::time_t globalTime = std::time(0);
        std::tm *localTime = std::localtime(&globalTime);
        day = localTime->tm_mday;
        month = localTime->tm_mon + 1;
        year = localTime->tm_year + 1900;
    }

    /// Date object for specified date
    Date(int day, int month, int year)
    {
        day = day;
        month = month;
        year = year;
    }

    Date(std::string s)
    {
        this->day = std::stoi(s.substr(0, s.find("/")));
        s.erase(0, s.find("/") + 1);

        this->month = std::stoi(s.substr(0, s.find("/")));
        s.erase(0, s.find("/") + 1);

        this->year = std::stoi(s.substr(0, s.find("/")));
        s.erase(0, s.find("/") + 1);
    }
    
    friend ostream &operator<<(ostream &, Date);

    operator std::string()
    {
        std::string s = to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);
        return s;
    }
};

ostream &operator<<(ostream &out, Date date)
{
    out << date.day << "/" << date.month << "/" << date.year;
    return out;
}

int getInterval(Date d)
{
    Date currentDate;
    return (currentDate.year - d.year) * 365 + (currentDate.month - d.month) * 30 + (currentDate.day - d.day);
}
