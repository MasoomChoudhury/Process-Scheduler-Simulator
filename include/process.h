// include/process.h
#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int remainingTime;

    Process(int id, int arrivalTime, int burstTime);
};

#endif // PROCESS_H
