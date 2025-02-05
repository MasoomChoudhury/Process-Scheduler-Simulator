// include/process_scheduler.h
#ifndef PROCESS_SCHEDULER_H
#define PROCESS_SCHEDULER_H

#include <vector>
#include <string>
#include <map>

#include "process.h"

class ProcessScheduler {
public:
    ProcessScheduler(int numProcesses, int timeQuantum);
    void generateProcesses();
    void runFCFS();
    void runRoundRobin();
    void calculateMetrics();
    void outputResults(const std::string& filename);

private:
    int numProcesses;
    int timeQuantum;
    std::vector<Process> processes;
    std::vector<int> ganttChartFCFS;
    std::vector<int> ganttChartRR;
    double avgWaitingTimeFCFS;
    double avgWaitingTimeRR;
    double cpuUtilization;
    double throughput;
    double starvationReduction;
};

#endif // PROCESS_SCHEDULER_H
