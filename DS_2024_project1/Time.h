#ifndef TIME_H
#define TIME_H
#include <sstream>
#include <string.h>
#include <exception>

// class to format time XX:XX:XX and compare
class Time {
private:
    short hours;
    short minutes;
    short seconds;
public:
    //manager function; initializes fields (0 if values are not given)
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}

    //output function
    short getHours() const;
    short getMinutes() const;
    short getSeconds() const;

    //return false if the string type was invalid
    bool parseTime(const std::string& timeStr);

    //operator overloading
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator==(const Time& other) const;

    //parses string format "HH:MM:SS" to each field. (0 <= HH < 100, 0 <= MM < 60, 0 <= SS <60)
    friend std::istream& operator>>(std::istream& is, Time& time);
    //print Time with "HH:MM:SS" format
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif TIME_H
