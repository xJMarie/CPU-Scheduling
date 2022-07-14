// First Come, First Served (FCFS)
#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"

// Function to find the waiting time
void waitingTimeFCFS(int n, Process *processes) {
  int i;

  // Waiting time for first process is 0
  processes[0].wt = 0;         

  // Calculating waiting time
  for(i = 1; i < n ; i++){
    processes[i].wt = processes[i-1].at + processes[i-1].bt + processes[i-1].wt - processes[i].at;
  }   

  // Get Start Time and End Time
  for(i = 0; i < n; i++){
    processes[i].st = (int*)malloc(sizeof(int));
    processes[i].et = (int*)malloc(sizeof(int));
    processes[i].st[0] = processes[i].wt + processes[i].at;
    processes[i].et[0] = processes[i].wt + processes[i].bt + processes[i].at;
  } 
}

// Function to calculate average time
void avgtimeFCFS(int n, Process *processes) {
  int totalWT = 0, i, j;
  Process temp;

  // Sort Processes According to its Arival Time
  for (i = 0; i < n; i++) {
    for (j = i+1; j < n; j++) {
      if (processes[i].at > processes[j].at) {
        temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }
  
  waitingTimeFCFS(n, processes);       // Function to find waiting time of all processes
  
  for (i = 0; i < n; i++) {           
    printf("P[%d] Start Time: %d    End Time: %d    |   Waiting Time: %d\n", processes[i].pid, processes[i].st[0], processes[i].et[0], processes[i].wt);
    totalWT += processes[i].wt;     // Calculate total waiting time and total turn around time
  }

  printf("Average waiting time = %.1f\n", (float)totalWT / (float)n);
}

// Main function of FCFS
void fcfs(int nProcess, Process *processes) {
  int i = 0;
  int *pId = (int*)malloc(sizeof(int) * nProcess);

  // Stores the processes ids to pId
  for(i = 0; i < nProcess; i++) {
    pId[i] = processes[i].pid;
  }

  int arrSize = (sizeof(pId) * nProcess) / sizeof(pId[0]);
  avgtimeFCFS(arrSize, processes);
}