#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector> 

class Processor {
    public:
        float Utilization();  // TODO: See src/processor.cpp

    // TODO: Declare any necessary private members
    private:
        std::vector<float> previous_cpu_elements = {};
        float IdleTime(std::vector<float>);
        float NonIdleTime(std::vector<float>);
};

#endif