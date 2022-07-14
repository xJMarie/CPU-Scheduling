#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "rr.h"
#define N 100

int queue[N];
int start = 0, end = 0;

// Function to add an item to stack
void push(int pid) {
  queue[end] = pid;
  end = (end + 1) % N;
}

// Function to remove an item from stack
int pop() {
	if(start == end)
		return -1;

	int retPosition = queue[start];
	start = (start +1)%N;

	return retPosition;
}

// Caclulates the waiting time of each processes
void waitingTimeRR(int n, Process *processes, int tQuantum) {
  int i, j, index = 0, clock = 0;
  int time = 0, pLeft = n, pos = -1, lTime = processes[0].at;
  int prevPos;

  for (i = 0; i < n; i++) {
    if(processes[i].at == time) {
        push(i);
    }
  }

	while(pLeft) {
		if (lTime == 0) {
			if(pos != -1)
				push(pos);
        
        pos = pop();
        prevPos = pos;

        index = processes[pos].nTimes;

        if(index == 0 && pos != -1) {
            processes[pos].nTimes = 1;
            processes[pos].st = (int*)malloc(sizeof(int) * processes[pos].nTimes);
            processes[pos].et = (int*)malloc(sizeof(int) * processes[pos].nTimes);
            processes[pos].st[index] = clock;
            processes[pos].et[index] = 0;
        } else if (pos != -1) {
            processes[pos].nTimes++;
            processes[pos].st = (int*)realloc(processes[pos].st, sizeof(int) * processes[pos].nTimes);
            processes[pos].et = (int*)realloc(processes[pos].et, sizeof(int) * processes[pos].nTimes);
            processes[pos].st[index] = clock;
            processes[pos].et[index] = 0;
        }
		}

    if (clock >= 0 && pos != -1)
      processes[prevPos].et[index] = clock+1;

    clock++;

		for (j = 0; j < n; j++) {
			if(processes[j].at > time)
				continue;
			if(j == pos)
				continue;
			if(processes[j].rTimes == 0)
				continue;

			processes[j].wt++;
		}

		if (pos != -1) {
			processes[pos].rTimes--;
			if(processes[pos].rTimes == 0) {
				pLeft--;
				lTime = -1;
				pos = -1;
			}
		}
		else
			lTime = -1; 

		time++;
		lTime = (lTime +1) % tQuantum;
	
		for(i = 0; i < n; i++)
			if(processes[i].at == time)	
				push(i);
	}
}

void avgTimeRR(int *xyz, Process *processes){
  int i, j, n = xyz[1], tQuantum = xyz[2];
  float totalWT = 0;
  Process temp;

  for(i = 0; i < n; i++) {
    processes[i].rTimes = processes[i].bt;
    processes[i].wt = 0;
    processes[i].nTimes = 0;
	}

  waitingTimeRR(n, processes, tQuantum);       // Function to find waiting time of all processes

  // Sorts the processes by waiting time
  for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if (processes[i].wt > processes[j].wt) {
				temp = processes[i];
				processes[i] = processes[j];
				processes[j] = temp;
			}
		}
	}

  for(i = 0; i < n; i++){
    printf("P[%d]   ", processes[i].pid);
    for(j = 0; j < processes[i].nTimes; j++){
      if(processes[i].et[j] >= 0){
        printf("Start Time: %d    End Time: %d    |   ", processes[i].st[j], processes[i].et[j]);
      }
    }
    printf(" Waiting Time: %d\n", processes[i].wt);
    totalWT += processes[i].wt;
  }
  printf("Average waiting time = %.1f\n", totalWT / (float)n);
}

// RR Function
void rr(int *xyz, Process *processes) {
	int nProcess = xyz[1], i = 0, j = 0;
  Process temp;

  // Sort processes according to its arrival time
  for (i = 0; i < nProcess; i++) {
    for (j = i+1; j < nProcess; j++) {
      if (processes[i].at > processes[j].at) {
          temp = processes[i];
          processes[i] = processes[j];
          processes[j] = temp;
      }	    
    }
  }
  avgTimeRR(xyz, processes);
}
