#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
    int h = seconds/3600;
    int m = (seconds - h*3600)/60;
    int s = seconds - h*3600 - m*60;
    std::string elapsedTime = PadZeroInts(h) + ":" + PadZeroInts(m) + ":" + PadZeroInts(s);
    return elapsedTime; 
}

std::string Format::PadZeroInts(int x) {
    std::string str = std::to_string(x);
    while(str.length() < 2) {
        str = "0" + str;
    }
    return str;
}