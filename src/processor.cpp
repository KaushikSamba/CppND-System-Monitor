#include "processor.h"
#include "linux_parser.h"

#include <vector>
#include <string>
#include <algorithm>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> cpu_elements_string = LinuxParser::CpuUtilization();
    std::vector<float> cpu_elements_float(cpu_elements_string.size());
    std::transform(cpu_elements_string.begin(), cpu_elements_string.end(), cpu_elements_float.begin(), [](const std::string &str){
        return std::stod(str);
    });

    float idle = IdleTime(cpu_elements_float);
    float non_idle = NonIdleTime(cpu_elements_float);
    float total = idle + non_idle;

    // If there is no previous information, compute the long-term value for utilization and update previous information.  
    if (previous_cpu_elements.size() == 0 ){
        previous_cpu_elements = cpu_elements_float;
        return non_idle/total; 
    }
    // Otherwise, you can use deltas. 
    float prev_idle = IdleTime(previous_cpu_elements);
    float prev_non_idle = NonIdleTime(previous_cpu_elements);
    float prev_total = prev_idle + prev_non_idle;

    float total_delta = total - prev_total;
    float non_idle_delta = non_idle - prev_non_idle;

    previous_cpu_elements = cpu_elements_float;
    return non_idle_delta/total_delta;
}

float Processor::IdleTime(std::vector<float> v){
    float idle = v[LinuxParser::CPUStates::kIdle_] + v[LinuxParser::CPUStates::kIOwait_];
    return idle;
}

float Processor::NonIdleTime(std::vector<float> v){
    float non_idle =    v[LinuxParser::CPUStates::kUser_] 
                        + v[LinuxParser::CPUStates::kNice_] 
                        + v[LinuxParser::CPUStates::kSystem_]
                        + v[LinuxParser::CPUStates::kIRQ_]
                        + v[LinuxParser::CPUStates::kSoftIRQ_]
                        + v[LinuxParser::CPUStates::kSteal_];
    return non_idle;
}