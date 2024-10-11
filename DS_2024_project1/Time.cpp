#include "Time.h"

bool Time::parseTime(const string& timeStr) {
    // Check if the length of the string is exactly 8 (XX:XX:XX)
        if (timeStr.length() != 8) {
            return false;
        }

    // Check if ':' are in the correct positions
    if (timeStr[2] != ':' || timeStr[5] != ':') {
        return false;
    }

    // Extract hours, minutes, and seconds parts
    stringstream ss(timeStr);      //used stringstream to separate strings by ';'
    string hoursStr, minutesStr, secondsStr;

    getline(ss, hoursStr, ':');   // Get hours
    getline(ss, minutesStr, ':'); // Get minutes
    getline(ss, secondsStr);      // Get seconds

    // Check if each part is exactly 2 characters long
    if (hoursStr.length() != 2 || minutesStr.length() != 2 || secondsStr.length() != 2) {
        return false;
    }

    // Convert each part to an integer and check if they are within valid ranges
    hours = stoi(hoursStr);
    minutes = stoi(minutesStr);
    seconds = stoi(secondsStr);

    // Check hours >= 0, minutes and seconds should be between 0 and 59
    if (hours < 0 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
        return false;
    }

    return true;
}

bool Time::operator<(const Time& other) const {
    if (hours < other.hours) return true;   //compare hour
    if (hours == other.hours && minutes < other.minutes) return true; //compare min 
    if (hours == other.hours && minutes == other.minutes && seconds < other.seconds) return true; //compare sec
    return false;
}

bool Time::operator>(const Time& other) const {
    return other < *this;
}

bool Time::operator==(const Time& other) const {
    return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
}

bool Time::operator>=(const Time& other) const {
    return (*this > other) || (*this == other);
}
bool Time::operator<=(const Time& other) const {
    return (*this < other) || (*this == other);
}
std::istream& operator>>(std::istream& is, Time& time)
{
    string timeStr; //saves the string 
    is >> timeStr;  //get string until the first whitespace

    // Check if the length of the string is exactly 8 (XX:XX:XX)
    if (timeStr.length() != 8) {
        time = Time(-1, 0, 0);
        is.setstate(ios::failbit);
        return is;
    }

    // Check if ':' are in the correct positions
    if (timeStr[2] != ':' || timeStr[5] != ':') {
        time = Time(-1, 0, 0);
        is.setstate(ios::failbit);
        return is;
    }

    // Extract hours, minutes, and seconds parts
    stringstream ss(timeStr);      //used stringstream to separate strings by ';'
    string hoursStr, minutesStr, secondsStr;

    getline(ss, hoursStr, ':');   // Get hours
    getline(ss, minutesStr, ':'); // Get minutes
    getline(ss, secondsStr);      // Get seconds

    // Check if each part is exactly 2 characters long (plus check if hours < 100)
    if (hoursStr.length() != 2 || minutesStr.length() != 2 || secondsStr.length() != 2) {
        time = Time(-1, 0, 0);
        is.setstate(ios::failbit);
        return is;
    }

    // Try to convert each part to an integer and check if they are within valid ranges
    try {   //function stoi() can fail because given value is not an integer
        //convert each part to integer, convert to short
        Time temp(stoi(hoursStr), stoi(minutesStr), stoi(secondsStr));

        // Check hours >= 0, minutes and seconds should be between 0 and 59
        if (temp.hours < 0 || temp.minutes < 0 || temp.minutes >= 60 || temp.seconds < 0 || temp.seconds >= 60) {
            time = Time(-1, 0, 0);
            is.setstate(ios::failbit);
            return is;
        }

        //No issues checked, copy
        time = temp;
        return is;
    } 
    catch (const invalid_argument& e) { //stoi error; not a number
        time = Time(-1, 0, 0);
        is.setstate(ios::failbit);
        return is;
    }
}
std::ostream& operator<<(std::ostream& os, const Time& time)
{
    //if the time had error
    if (time.hours < 0)
    {
        os << "ERRTIME"; return os;
    }
    os << (time.hours < 10 ? "0" : "") << time.hours << ":"
        << (time.minutes < 10 ? "0" : "") << time.minutes << ":"
        << (time.seconds < 10 ? "0" : "") << time.seconds;
    return os;
}
//io function
short Time::getHours() const {
    return hours;
}
short Time::getMinutes() const {
    return minutes;
}
short Time::getSeconds() const {
    return seconds;
}