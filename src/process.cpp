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

// Constructor updates the CPU utilization of the process when it is created. 
// This is needed to display the processes in order of decreasing CPU utilization.
Process::Process(const int pid) : pid_(pid), cpuUsage_(CpuUtilization()) {}

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
// Returns a value between 0 and 1.
float Process::CpuUtilization() { 
    const std::vector<long int> processInfo = LinuxParser::Cpu(pid_);
    long int total_time = processInfo[processInfoElem::utime_] + processInfo[processInfoElem::stime_];
    total_time += processInfo[processInfoElem::cutime_] + processInfo[processInfoElem::cstime_];
    const float seconds = (float) Process::UpTime();
    const float cpuUsage = ((total_time / sysconf(_SC_CLK_TCK)) / seconds);
    return cpuUsage; 
}

// Return the command that generated this process
string Process::Command() { 
    if (command_.length() == 0)
        command_ = LinuxParser::Command(pid_);
    return command_; 
}

// Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(pid_);
}

// Return the user (name) that generated this process
string Process::User() { 
    if (user_.length() == 0)
        user_ = LinuxParser::User(pid_);
    return user_; 
}

// Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_); 
}

// Overload the "greater than" comparison operator for Process objects
bool Process::operator>(Process const& a) const { 
    return (cpuUsage_ > a.cpuUsage_);
}