# PCB Process Control Block - CS Project

## Overview
In operating systems, Process Control Blocks (PCBs) play a crucial role in managing processes and their states. This project simulates the creation and destruction of processes within a simplified operating system environment. Each process is represented by a PCB, which stores information about its parent process and children. The project demonstrates the relationship between processes through linked lists, and allows the addition and deletion of processes dynamically.

## Project Goals
The goal of this project is to explore the implementation of a process management system, specifically focusing on creating and destroying processes. Through this, we simulate how an operating system might handle process hierarchies, including parent-child relationships and sibling navigation within the process tree.

## Core Concepts Used
* **Process Control Blocks (PCBs)**: Used to manage and store the state and hierarchical relationships of processes in an operating system.
* **Linked Lists**: Used to represent the relationships between processes in terms of parent, child, and sibling relationships.
* **Timers**: A macro-based timer system is used to measure execution time of process creation and destruction.
* **Dynamic Memory Management**: Process creation dynamically allocates memory for new processes, while process destruction frees up memory used by terminated processes.

## Getting Started
To get the PCB project running on your local machine, follow the steps below.

### Installing Dependencies
The project requires a C compiler (such as GCC). Make sure you have it installed on your machine. You can install GCC by running the following command (for Linux/Unix-based systems):

```
sudo apt install build-essential
```
## Downloading The Files
Clone the repository and navigate into the project directory. The repository includes all the necessary files for the project:

* **Makefile**:: Contains the compilation instructions.
* **timer.h**:: Header file for the timer used in the program.
* **version1.c**:: First version of the process control block simulation.
* **version2.c**:: Improved version with potential optimizations.


## Compilation
The project can be compiled using the provided Makefile. Simply run the following command to compile both versions of the project:

```
make
```

This will generate two executable files: version1 and version2.

## Final Steps
```
./version1
./version2
```

Both versions will simulate the process management system and output the results of process creation, deletion, and timing.

## Usage
The project demonstrates the creation and deletion of processes within a simulated OS environment. Upon running either version, the program will:

* Create child processes for a root process (PCB[0]).
* Display the list of children for each process.
* Destroy processes and clean up memory.
* Measure the time taken for the process creation and destruction using the GET_TIME macro from timer.h.

## Example Commands
Running the program will output the list of children for each process, as shown in the sample below:


```
Children of process 0: 1 2 
Children of process 1: 3 
Children of process 2: 4 

```

After destruction:

```
List after destroy 0:
Process 0 has no children.
Process 1 has no children.
Process 2 has no children.

```

## Modifying the Test Count
By default, the program runs 500 iterations of process creation and destruction. You can adjust the number of iterations by modifying the TEST_COUNT constant in the source code:


```
#define TEST_COUNT 1000

```
