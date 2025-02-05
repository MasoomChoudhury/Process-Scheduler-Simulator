// src/process_scheduler.cpp
#include "../include/process_scheduler.h"
#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

ProcessScheduler::ProcessScheduler(int numProcesses, int timeQuantum) : 
    numProcesses(numProcesses), 
    timeQuantum(timeQuantum) {}

void ProcessScheduler::generateProcesses() {
    srand(time(0)); // Seed random number generator
    for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime = rand() % 50; // Arrival time between 0 and 49
        int burstTime = rand() % 20 + 1; // Burst time between 1 and 20
        processes.emplace_back(i + 1, arrivalTime, burstTime);
    }
}

#include <iostream>
#include <vector>
#include <numeric> // for std::accumulate

void ProcessScheduler::runFCFS() {
    std::cout << "Running FCFS scheduling..." << std::endl;
    
    std::vector<Process> readyQueue = processes; // Initially all processes are ready
    std::sort(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime; 
    });

    int currentTime = 0;
    int totalWaitingTime = 0;
    std::vector<int> ganttChart; // Store process IDs for Gantt chart

    for (Process& process : readyQueue) {
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime; // Update current time if CPU is idle
        }
        process.waitingTime = currentTime - process.arrivalTime;
        totalWaitingTime += process.waitingTime;
        currentTime += process.burstTime;
        for (int i = 0; i < process.burstTime; ++i) { // Add process ID for burst time duration
            ganttChart.push_back(process.id); 
        }
    }

    avgWaitingTimeFCFS = static_cast<double>(totalWaitingTime) / numProcesses;
    ganttChartFCFS = ganttChart; 
    std::cout << "FCFS: Average Waiting Time = " << avgWaitingTimeFCFS << std::endl;
}

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <map> // Include map for process start times

void ProcessScheduler::runRoundRobin() {
    std::cout << "Running Round Robin scheduling..." << std::endl;

    std::vector<Process> readyQueue = processes; 
    std::sort(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime; 
    });

    std::queue<Process*> rrQueue; 
    int currentTime = 0;
    int totalWaitingTime = 0;
    int processIndex = 0;
    std::vector<int> ganttChart;
    std::map<Process*, int> processStartTime; // Map to track first start time

    while (processIndex < numProcesses || !rrQueue.empty()) {
        
        while (processIndex < numProcesses && readyQueue[processIndex].arrivalTime <= currentTime) {
            rrQueue.push(&readyQueue[processIndex]);
            processIndex++;
        }

        if (rrQueue.empty()) {
            currentTime++; 
            continue;
        }

        Process* currentProcess = rrQueue.front();
        rrQueue.pop();

        if (currentTime < currentProcess->arrivalTime) {
            currentTime = currentProcess->arrivalTime;
        }

        if (processStartTime.find(currentProcess) == processStartTime.end()) {
            processStartTime[currentProcess] = currentTime; // Record first start time
        }

        int executionTime = std::min(timeQuantum, currentProcess->remainingTime);
        currentProcess->remainingTime -= executionTime;


        currentTime += executionTime;
        ganttChart.push_back(currentProcess->id);

        if (currentProcess->remainingTime > 0) {
            rrQueue.push(currentProcess); 
        } else {
            int finishTime = currentTime;
            int waitingTime = finishTime - processStartTime[currentProcess] - currentProcess->burstTime;
            totalWaitingTime += waitingTime;
        }
    }

    avgWaitingTimeRR = static_cast<double>(totalWaitingTime) / numProcesses;
    ganttChartRR = ganttChart; 
    std::cout << "Round Robin: Average Waiting Time = " << avgWaitingTimeRR << std::endl;
}

#include <iostream>
#include <vector>
#include <numeric>

void ProcessScheduler::calculateMetrics() {
    std::cout << "Calculating performance metrics..." << std::endl;

    // CPU Utilization - Assuming 100% CPU utilization for simplicity in this simulation
    cpuUtilization = 100.0; 

    // Throughput - Number of processes completed per unit of time (assuming time unit is arbitrary here)
    // Approximating throughput as numProcesses / total simulation time (using FCFS end time as total time)
    int currentTimeFCFS = 0;
    for (int processId : ganttChartFCFS) {
        currentTimeFCFS += processes[processId - 1].burstTime; // Access process by ID
    }
    throughput = static_cast<double>(numProcesses) / currentTimeFCFS;


    // Process Starvation Reduction (RR vs FCFS)
    starvationReduction = ((avgWaitingTimeFCFS - avgWaitingTimeRR) / avgWaitingTimeFCFS) * 100.0;


    std::cout << "Metrics:" << std::endl;
    std::cout << "  CPU Utilization: " << cpuUtilization << "%" << std::endl;
    std::cout << "  FCFS Average Waiting Time: " << avgWaitingTimeFCFS << std::endl;
    std::cout << "  Round Robin Average Waiting Time: " << avgWaitingTimeRR << std::endl;
    std::cout << "  Throughput: " << throughput << " processes/time unit" << std::endl;
    std::cout << "  Starvation Reduction (RR vs FCFS): " << starvationReduction << "% (Approx)" << std::endl;

    // Metrics are now stored in class members
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> // for std::setprecision
#include "../include/cli_parser.h" // Include CLIArgs struct


void ProcessScheduler::outputResults(const std::string& filename) {
    std::cout << "Outputting results to " << filename << std::endl;

    // Get output format from CLI arguments (assuming CLIArgs is accessible here or passed to this function)
    CLIArgs args; // Placeholder - In actual implementation, access parsed CLI args
    std::string outputFormat = args.outputFormat; // Default to CSV if not parsed

    std::ofstream outputFile;
    if (outputFormat == "csv") {
        outputFile.open(filename + ".csv");
        if (!outputFile.is_open()) {
            std::cerr << "Error opening CSV file!" << std::endl;
            return;
        }
        outputFile << "Metric,FCFS,RoundRobin\n";
        outputFile << "CPU Utilization," << std::fixed << std::setprecision(2) << cpuUtilization << "," << std::fixed << std::setprecision(2) << cpuUtilization << "\n";
        outputFile << "Avg Waiting Time," << std::fixed << std::setprecision(2) << avgWaitingTimeFCFS << "," << std::fixed << std::setprecision(2) << avgWaitingTimeRR << "\n";
        outputFile << "Throughput," << std::fixed << std::setprecision(5) << throughput << "," << std::fixed << std::setprecision(5) << throughput << "\n";
        outputFile << "Starvation Reduction," << std::fixed << std::setprecision(2) << starvationReduction << ",0.0\n";

        outputFile << "\n";
        outputFile << "Gantt Chart (FCFS):,";
        for (int processId : ganttChartFCFS) {
            outputFile << "P" << processId << ",";
        }
        outputFile << "\n";

        outputFile << "Gantt Chart (RR):,";
        for (int processId : ganttChartRR) {
            outputFile << "P" << processId << ",";
        }
        outputFile << "\n";


        outputFile.close();
        std::cout << "Results saved to " << filename + ".csv" << std::endl;

    } else if (outputFormat == "json") {
        outputFile.open(filename + ".json");
        if (!outputFile.is_open()) {
            std::cerr << "Error opening JSON file!" << std::endl;
            return;
        }
        outputFile << "{\n";
        outputFile << "  \"metrics\": {\n";
        outputFile << "    \"cpuUtilization\": {\"FCFS\": " << std::fixed << std::setprecision(2) << cpuUtilization << ", \"RoundRobin\": " << std::fixed << std::setprecision(2) << cpuUtilization << "},\n";
        outputFile << "    \"avgWaitingTime\": {\"FCFS\": " << std::fixed << std::setprecision(2) << avgWaitingTimeFCFS << ", \"RoundRobin\": " << std::fixed << std::setprecision(2) << avgWaitingTimeRR << "},\n";
        outputFile << "    \"throughput\": {\"FCFS\": " << std::fixed << std::setprecision(5) << throughput << ", \"RoundRobin\": " << std::fixed << std::setprecision(5) << throughput << "},\n";
        outputFile << "    \"starvationReduction\": {\"FCFS\": " << std::fixed << std::setprecision(2) << starvationReduction << ", \"RoundRobin\": 0.0}\n";
        outputFile << "  },\n";
        outputFile << "  \"ganttCharts\": {\n";
        outputFile << "    \"FCFS\": [";
        for (size_t i = 0; i < ganttChartFCFS.size(); ++i) {
            outputFile << ganttChartFCFS[i];
            if (i < ganttChartFCFS.size() - 1) outputFile << ",";
        }
        outputFile << "],\n";
        outputFile << "    \"RR\": [";
        for (size_t i = 0; i < ganttChartRR.size(); ++i) {
            outputFile << ganttChartRR[i];
            if (i < ganttChartRR.size() - 1) outputFile << ",";
        }
        outputFile << "]\n";
        outputFile << "  }\n";
        outputFile << "}\n";
        outputFile.close();
        std::cout << "Results saved to " << filename + ".json" << std::endl;
    } else {
        std::cerr << "Error: Invalid output format specified." << std::endl;
    }
}
