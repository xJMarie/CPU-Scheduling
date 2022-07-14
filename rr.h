// Round Robin (RR)
#include "Process.h"

// Function to add an item to stack
void push(int pid);

// Function to remove an item from stack
int pop();

// Function to calculate the waiting time of each processes
void waitingTimeRR(int n, Process *processes, int tQuantum);

// Function to calculate average time
void avgTimeRR(int *xyz, Process *processes);

// Main function of RR
void rr(int *xyz, Process *processes);