#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "srtf.h"


void waitingTimeSrtf(int n, Process *processes){
  int i;
  int j = 0;
  int shortestProc;
  int procCompleted = 0;
  int minRT = INT_MAX;
  int isIdle = 1;
  int currTime = 0;
  int completionTime;
  int prevProc = -1;
  int *rt = (int*)malloc(sizeof(int) * n);

  for(i =0; i < n; i++){
    rt[i] = processes[i].bt;
    processes[i].nTimes = 0;
  }

  while(procCompleted != n){
    // Find shortest process
    for(i = 0; i < n; i++){
      if(rt[i] < minRT && processes[i].at <= currTime){
        if(rt[i] > 0){
          j = 0;
          shortestProc = i;
          minRT = rt[shortestProc];
          isIdle = 0;
        }
      }
    }

    // Check if CPU is idle
    if(isIdle == 1){
      currTime++;
      continue;
    }
    
    // Allocate memory space for start time and end time
    // Check if inital entry or recurring entry
    if(rt[shortestProc] == processes[shortestProc].bt){
      processes[shortestProc].nTimes = 1;
      processes[shortestProc].st = (int*)malloc(sizeof(int) * processes[shortestProc].nTimes);
      processes[shortestProc].et = (int*)malloc(sizeof(int) * processes[shortestProc].nTimes);
      processes[shortestProc].st[j] = currTime; 
    }else if(rt[shortestProc] < processes[shortestProc].bt && prevProc != shortestProc){
      j = processes[shortestProc].nTimes;
      processes[shortestProc].nTimes++;
      processes[shortestProc].st = (int*)realloc(processes[shortestProc].st, sizeof(int) * processes[shortestProc].nTimes);
      processes[shortestProc].et = (int*)realloc(processes[shortestProc].et, sizeof(int) * processes[shortestProc].nTimes);
      processes[shortestProc].st[j] = currTime; 
    }

    // Decrease remaining time of the Process
    minRT = --rt[shortestProc];

    // Compute for the waiting time
    if(rt[shortestProc] == 0){
      minRT = INT_MAX;
      procCompleted++;
      isIdle = 1;

      completionTime = currTime + 1;
      processes[shortestProc].wt = completionTime - processes[shortestProc].bt - processes[shortestProc].at;

      if(processes[shortestProc].wt < 0){
        processes[shortestProc].wt = 0;
      }
    }

    currTime++;
    processes[shortestProc].et[j] = currTime;
    prevProc = shortestProc;
  }  
}

void avgTimeSrtf(int n, Process * processes){
  int i, j;
  int totalWT = 0;
  Process tempProc;

  waitingTimeSrtf(n, processes);

  for (i = 0; i < n; i++) {
    for (j = i+1; j < n; j++) {
      if (processes[i].wt > processes[j].wt) {
          tempProc = processes[i];
          processes[i] = processes[j];
          processes[j] = tempProc;
      }
    }
  }

  for(i = 0; i < n; i++){
    printf("P[%d] ", processes[i].pid);
    for(j = 0; j < processes[i].nTimes; j++){
      if(processes[i].et[j] != 0){
        printf("Start Time: %d    End Time: %d    |   ", processes[i].st[j], processes[i].et[j]);
      }
    }
    printf(" Waiting Time: %d\n", processes[i].wt);
    totalWT += processes[i].wt;
  }

  printf("Average waiting time = %.1f\n", (float)totalWT / (float)n);
}


void srtf(int nProcess, Process *processes){
  int i;
  int *pId = (int*)malloc(sizeof(int) * nProcess);

  // Stores the processes ids to pId
  for(i = 0; i < nProcess; i++) {
      pId[i] = processes[i].pid;
  }

  int arrSize = (sizeof(*pId) * nProcess) / sizeof(pId[0]);
  avgTimeSrtf(arrSize, processes);
}