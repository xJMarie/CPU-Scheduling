// Shortest Job First Scheduling (SJF)
#include <stdio.h>
#include <stdlib.h>
#include "sjf.h"
#include <limits.h>

// Function to find the waiting time
int waitingTimeSJF(int n, Process *processes) {
  int i;
  int shortestProc;
  int procCompleted = 0;
  int minBT = INT_MAX;
  int completionTime;
  int currTime = 0;
  int *done = (int*)malloc(sizeof(int) * n);
  int isIdle = 1;
  int totWT = 0;
  for(i = 0; i < n; i++){
    done[i] = 0;
  }

  while(procCompleted != n){
    // Find Next Shortest Process
    for(i = 0; i < n; i++){
      // Check if process is less than the current time and is not done 
      if(processes[i].at <= currTime && !done[i]){
        // Check if process burst time is less than the min burst time
        if(processes[i].bt < minBT){
          minBT = processes[i].bt;
          shortestProc = i;
          isIdle = 0;
        }
      }
    }

    if(!isIdle){
      // Compute for Current Time
      currTime += processes[shortestProc].bt;

      // Reset Minimum Burst Time
      minBT = INT_MAX;

      // Increment Process Completed
      procCompleted++;

      // Get Completion Time
      completionTime = currTime;
      // Compute for wait time
      processes[shortestProc].wt = completionTime - processes[shortestProc].bt - processes[shortestProc].at;

      if(processes[shortestProc].wt < 0){
        processes[shortestProc].wt = 0;
      }

      totWT += processes[shortestProc].wt;
      // Process Completed
      done[shortestProc] = 1;
      // Compute for start time and end time
      processes[shortestProc].st = (int*)malloc(sizeof(int));
      processes[shortestProc].et = (int*)malloc(sizeof(int));
      processes[shortestProc].st[0] = processes[shortestProc].wt + processes[shortestProc].at;
      processes[shortestProc].et[0] = processes[shortestProc].wt + processes[shortestProc].bt + processes[shortestProc].at;
      printf("P[%d] Start Time: %d    End Time: %d    |   Waiting Time: %d\n", processes[shortestProc].pid, processes[shortestProc].st[0], processes[shortestProc].et[0], processes[shortestProc].wt);
    }else{
      currTime++;
    }

  }
  return totWT;
}

// Function to calculate average time
void avgtimeSJF(int n, Process *processes) {
  int totalWT = 0, i, j;
  Process temp;

  // Sort Processes According to its Arrival Time
  for (i = 0; i < n; i++) {
    for (j = i+1; j < n; j++) {
      if (processes[i].at > processes[j].at) {
        temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }	
    }
  }

  totalWT = waitingTimeSJF(n, processes);       // Function to find waiting time of all processes
  
  printf("Average waiting time = %.1f\n", (float)totalWT / (float)n);
}

// SJF Function
void sjf(int nProcess, Process *processes) {
	int i = 0;
  int *pId = (int*)malloc(sizeof(int) * nProcess);

  // Stores the processes ids to pId
  for(i = 0; i < nProcess; i++) {
    pId[i] = processes[i].pid;
  }

  int arrSize = (sizeof(pId) * nProcess) / sizeof(pId[0]);
  
  avgtimeSJF(arrSize, processes);
}