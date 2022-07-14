# CPU Scheduling

CSOPESY • Introduction to Operating Systems | Junior • AY 2020-2021

### Author/s:

- AGULTO, Juliana Marie
- MONEDA, Heinze Kristian

A student-project that implements the basic CPU scheduling algorithms using the C Programming Language.

### Instructions:

Using Windows CMD

1. Compile the following c files using the command.

```
gcc -Wall -Wextra -c rr.c srtf.c sjf.c fcfs.c main.c
```

2. Once compiled the following files will be created.

- rr.o
- srtf.o
- sjf.o
- fcfs.o
- main.o

3. Create an executable file by using the command:

```
gcc rr.o srtf.o sjf.o fcfs.o main.o
```

by default the file name of the executable will be `a.exe` but you can use a custom file name by using the command.

```
gcc rr.o srtf.o sjf.o fcfs.o main.o -o <custom file name>
```

4. Run the program by using the command.
