#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"

#define N 1000 // Size of array
#define TEST_COUNT 500 // Testing loop

// PCB struct
typedef struct PCB {
    int parent;
    int first_child;
    int younger_sibling;
    int older_sibling;
} PCB;


// Array of PCBS
PCB PCB_TABLE[N];


// Creates a new process
void create(int p) {
    int q = -1;
    int i, last_sibling;

    // Iterates through PCB
    for (i = 1; i < N; i++) {
        if (PCB_TABLE[i].parent == -1) { // Check if the PCB is free
            q = i; // Update q
            break; // Exit code if a free PCB is found
        }
    }
    if (q == -1) {
        printf("There's no available PCB.\n");
        return; // Exit bc there's no free PCB
    }

    // Initialize new PCB
    PCB_TABLE[q].parent = p;
    PCB_TABLE[q].first_child = -1;
    PCB_TABLE[q].younger_sibling = -1;
    PCB_TABLE[q].older_sibling = -1;

    // If the parent has no children, set the first child to the new process
    if (PCB_TABLE[p].first_child == -1) {
        PCB_TABLE[p].first_child = q;
    }
    else {
	// Find the last sibling in the children list
        last_sibling = PCB_TABLE[p].first_child;
        while (PCB_TABLE[last_sibling].younger_sibling != -1) {
            last_sibling = PCB_TABLE[last_sibling].younger_sibling;
        }
	PCB_TABLE[last_sibling].younger_sibling = q; // Set process as the younger sibling
        PCB_TABLE[q].older_sibling = last_sibling; // Set the previous last sibling as the older sibling
    }
}


// Destorys a process and it's descendants
void destroy(int p) {
    int child, next_sibling;
    child = PCB_TABLE[p].first_child; // Get the first child

    // Recursively destory all children an dtheir descendants
    while (child != -1) {
        next_sibling = PCB_TABLE[child].younger_sibling;    // Store the next sibling
        destroy(child);     // Recursively destroy
        child = next_sibling;   // Move to the next sibling
    }

    // Update siblings pointers
    if (PCB_TABLE[p].older_sibling != -1) {
        PCB_TABLE[PCB_TABLE[p].older_sibling].younger_sibling = PCB_TABLE[p].younger_sibling;
    }
    if (PCB_TABLE[p].younger_sibling != -1) {
        PCB_TABLE[PCB_TABLE[p].younger_sibling].older_sibling = PCB_TABLE[p].older_sibling;
    }

    // Update the parents first child
    if (PCB_TABLE[p].parent != -1 && PCB_TABLE[PCB_TABLE[p].parent].first_child == p) {
        PCB_TABLE[PCB_TABLE[p].parent].first_child = PCB_TABLE[p].younger_sibling;
    }

    // Reset PCB
    PCB_TABLE[p].parent = -1;
    PCB_TABLE[p].first_child = -1;
    PCB_TABLE[p].younger_sibling = -1;
    PCB_TABLE[p].older_sibling = -1;

}


// Prints the list of children for a process
void printList(int p) {
    int child = PCB_TABLE[p].first_child; // Get the first child of the process

    if (child == -1) { // Check if child is empty
        printf("Process %d has no children.\n", p);
    }
    else {
	printf("Children of process %d: ", p);
        // Iterate through and print the list of children
        while (child != -1) {
            printf("%d ", child);
            child = PCB_TABLE[child].younger_sibling;
        }
	printf("\n");
    }
}


int main() {
    double start, finish, elapsed;

    // Initialize PCB table
    for (int i = 0; i < N; i++) {
        PCB_TABLE[i].parent = -1;
        PCB_TABLE[i].first_child = -1;
        PCB_TABLE[i].younger_sibling = -1;
        PCB_TABLE[i].older_sibling = -1;
    }

    PCB_TABLE[0].parent = 0; // Initialize the root

    GET_TIME(start); // Start timer

    // Run the test program in a loop
    for (int i = 0; i < TEST_COUNT; i++) {
        create(0); // creates 1st child of PCB[0] at PCB[1]
        create(0); // creates 2nd child of PCB[0] at PCB[2]
        create(1); // creates 1st child of PCB[1] at PCB[3]
        create(2); // creates 1st child of PCB[2] at PCB[4]
        destroy(0); // destroys all descendants of PCB[0], which includes processes PCB[1] through PCB[4]
    }

    GET_TIME(finish); // Stop timer
    elapsed = finish - start; // Calculate elapsed time


    // Print the result of one test iteration
    create(0);
    create(0);
    create(1);
    create(2);
    printList(0);
    printList(1);
    printList(2);
    printf("\n");
    destroy(0);
    printf("\nList after destroy 0:\n");
    printList(0);
    printList(1);
    printList(2);
    printf("\nThis test was executed %d times and takes %e seconds\n\n", TEST_COUNT, elapsed);
    return 0;
}