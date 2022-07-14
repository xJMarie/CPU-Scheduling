#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Process.h"
#include "fcfs.h"
#include "sjf.h"
#include "srtf.h"
#include "rr.h"

// function to the read text file
Process* txtRead(int* inputs) {
  char filename[20];

  printf("Enter filename of input text file: ");
  scanf("%s", filename);

  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("%s not found.", filename);
    exit(101);
  }
  
  int i = 0;

  fscanf(fp, "%d %d %d", &inputs[0], &inputs[1], &inputs[2]);
  
  Process* processes = (Process*)malloc(sizeof(Process)*inputs[1]);

  while(fscanf(fp, "%d %d %d", &processes[i].pid, &processes[i].at, &processes[i].bt) == 3){
    i++;
  }

  fclose(fp);     // close the file

  return processes;
}

// main function
int main() {

  int xyz[3];
  Process* processes = txtRead(xyz);     // get the user inputs

  switch (xyz[0]) {
  case 0: 
    printf("First-Come First-Serve (FCFS)\n");
    fcfs(xyz[1], processes);
    break;

  case 1: 
    printf("Shortest-Job First (SJF)\n");
    sjf(xyz[1], processes);
    break;

  case 2: 
    printf("Shortest-Remaining-Time-First (SRTF)\n");
    srtf(xyz[1], processes);
    break;

  case 3: 
    printf("Round-Robin (RR)\n");
    rr(xyz, processes);
    break;
  
  default:
    break;
  }

  return 0;
}

