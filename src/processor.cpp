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

    float idle = cpu_elements_float[LinuxParser::CPUStates::kIdle_] + cpu_elements_float[LinuxParser::CPUStates::kIOwait_];
    float non_idle =    cpu_elements_float[LinuxParser::CPUStates::kUser_] 
                        + cpu_elements_float[LinuxParser::CPUStates::kNice_] 
                        + cpu_elements_float[LinuxParser::CPUStates::kSystem_]
                        + cpu_elements_float[LinuxParser::CPUStates::kIRQ_]
                        + cpu_elements_float[LinuxParser::CPUStates::kSoftIRQ_]
                        + cpu_elements_float[LinuxParser::CPUStates::kSteal_];
    float total = idle + non_idle;

    return non_idle/total; 
}