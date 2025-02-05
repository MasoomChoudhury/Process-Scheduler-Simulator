// src/main.cpp
#include <iostream>
#include "../include/cli_parser.h"
#include "../include/process_scheduler.h"

int main(int argc, char* argv[]) {
    CLIArgs args = parseCLIArgs(argc, argv);

    ProcessScheduler scheduler(args.numProcesses, args.timeQuantum);
    scheduler.generateProcesses();
    scheduler.runFCFS();
    scheduler.runRoundRobin();
    scheduler.calculateMetrics();
    scheduler.outputResults("simulation_results");

    std::cout << "Process Scheduler Simulator completed." << std::endl;
    return 0;
}
