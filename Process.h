#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process
{
  int pid;
  int at;
  int bt;
  int wt;
  int *st;
  int *et;
  int nTimes;
  int rTimes;
} Process;

#endif
