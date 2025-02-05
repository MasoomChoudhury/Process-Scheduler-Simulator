// src/process.cpp
#include "../include/process.h"

Process::Process(int id, int arrivalTime, int burstTime) : 
    id(id), 
    arrivalTime(arrivalTime), 
    burstTime(burstTime),
    waitingTime(0),
    remainingTime(burstTime) {}
