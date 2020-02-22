#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid), hertz_(sysconf(_SC_CLK_TCK)) { }
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
// Returns a value between 0 and 1.
float Process::CpuUtilization() { 
    // long systemUpTime = LinuxParser::UpTime();
    // float sysUpTimeSeconds = systemUpTime / hertz_;
    std::vector<long int> processInfo = LinuxParser::Cpu(pid_);
    enum processInfoElem {
        utime_ = 0, 
        stime_, 
        cutime_, 
        cstime_, 
        starttime_
    };
    long int total_time = processInfo[processInfoElem::utime_] + processInfo[processInfoElem::stime_];
    total_time += processInfo[processInfoElem::cutime_] + processInfo[processInfoElem::cstime_];
    // float seconds = sysUpTimeSeconds - (processInfo[processInfoElem::starttime_] / hertz_);
    // float processUpTimeSeconds = Process::UpTime();
    float seconds = (float) Process::UpTime();
    float cpu_usage = ((total_time / hertz_) / seconds);
    return cpu_usage; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
    if (command_.length() == 0)
        command_ = LinuxParser::Command(pid_);
    return command_; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    if (user_.length() == 0)
        user_ = LinuxParser::User(pid_);
    return user_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    auto uptime = LinuxParser::UpTime(pid_); 
    return uptime/hertz_;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }