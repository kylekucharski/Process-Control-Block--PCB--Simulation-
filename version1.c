#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define N 1000 // Size of array
#define TEST_COUNT 500 // Testing Loop

// Linked List Node struct
typedef struct Node {
    int pcb_index; // PCB index of the child process
    struct Node *next; // Pointer to the next node in the linked list (LL)
} Node;


// PCB struct
typedef struct PCB {
    int parent; // PCB index of the parent process
    Node *children; // Pointer to the linked list of children
} PCB;


// PCB Array of size N = 1000
PCB PCB_TABLE[N];


// Creates a new process
void create(int p) {
    int q;
    // Iterate throught PCB Table and look for a free PCB index
    for (q = 1; q < N; q++) {
        if (PCB_TABLE[q].parent == -1) {
            break; // Break once a free PCB index is found
        }

    }
    if (q == N) return; // Return bc there's no available PCB

    PCB_TABLE[q].parent = p; // Records parents index(p) in PCB_TABLE[q]
    PCB_TABLE[q].children = NULL; // Initialize the new child process as empty

    // Create a new node for the child process
    Node *new_node = (Node *)malloc(sizeof(Node)); // Dynamically allocate memory for a new node
    if (!new_node) return; // If memory allocation failed, exit
    new_node -> pcb_index = q; // Set PCB index of the new node
    new_node -> next = NULL; // Initialize the next pointer as null

    // Append the new node to the end of the children
    Node *current = PCB_TABLE[p].children; // Get the head of the LL
    if (!current) {
        PCB_TABLE[p].children = new_node; // If the LL is empty, set the new node as the first child
    }
    else {
	// Iterate through the children list to find the last element/end of LL
        while (current -> next) {
            current = current->next;
        }
	current -> next = new_node; // Append the new node to the end of the LL
    }
}


// Destroys a process and its descendants
void destroy(int p) {
    Node *current = PCB_TABLE[p].children; // Get the head of the LL

    while (current) {
        destroy(current -> pcb_index); // Recursively destory all progenies
        Node *temp = current; // Store the current node to free memory later
        current = current -> next; // Move to the next node in the list
        free(temp); // Free memory allocated for the child node
    }

    PCB_TABLE[p].parent = -1; // Update the process to free
    PCB_TABLE[p].children = NULL; // Clear the LL
}


// Prints the list of children for a process
void printList(int p) {
    Node *current = PCB_TABLE[p].children; // Get the head of the childrens list
    printf("Children of process %d: ", p);

    if (!current) { // Check if LL is empty
        printf("None\n");
    }
    else {
	// Iterate through the LL and print each child's PCB index
        while (current) {
            printf("%d ", current -> pcb_index);
            current = current -> next;
        }
	printf("\n");
    }
}


int main() {
    double start, finish, elapsed;

    // Initialize PCB table
    for (int i = 0; i < N; i++) {
        PCB_TABLE[i].parent = -1; // Update all PCBS to free
        PCB_TABLE[i].children = NULL; // Initialize the children lists to null
    }

    PCB_TABLE[0].parent = 0; // Initialize the root

    GET_TIME(start); // Start timer

    // Execute the test program 500 times in a loop
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
    printf("List after destroy 0:\n");
    printList(0);
    printList(1);
    printList(2);
    printf("\nThis test was executed %d times and takes %e seconds\n\n", TEST_COUNT, elapsed);
    return 0;
}