#include <string>
#include "format.h"

using std::string;

// Return string with elapsed time
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long time) { 
    int hours, minutes, seconds;
    string hh, mm, ss;
    hours = time/3600;
    minutes = (time%3600)/60;
    seconds = (time%3600)%60;
    hh = (hours < 10)? "0"+ std::to_string(hours): std::to_string(hours);
    mm = (minutes < 10)? "0"+ std::to_string(minutes): std::to_string(minutes);
    ss =  (seconds < 10)? "0" +std::to_string(seconds): std::to_string(seconds);
    return string(hh + "::" + mm + "::" +ss); 
}