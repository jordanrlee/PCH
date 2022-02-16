#include <stdio.h>
#include <stdlib.h>
#include "process_control_block.h"
#define N 50

void create2(struct pcb2 PCBArray[], int numberPCBs, int p);
void destroy2(struct pcb2 PCBArray[], int numberPCBs, int p);
void print2(struct pcb2 PCBArray[], int numberPCBs, int p);
void destroyHelper(struct pcb2 *PCBArray, int p); // added for the recursive destroy function

int main(void)
{
    // an array to store N number of pcb structures
    struct pcb2 PCB[N];

    // initialize pcb structures
    for (int i = 0; i < N; i++)
    {
        PCB[i].parent = -1;             // -1 for parent means the spot is marked as free (green)
        PCB[i].first_child = -1;        // -1 means this attribute has not been assigned
        PCB[i].younger_sibling = -1;    // -1 means this attribute has not been assigned
        PCB[i].older_sibling = -1;      // -1 means this attribute has not been assigned
    }

    // assuming that PCB[0] is the only currently existing process, its parent is unknown (-2)
    PCB[0].parent = -2;

    // process 0 creates process 1, 2, 3, and 4
    create2(PCB, N, 0);
    create2(PCB, N, 0);
    create2(PCB, N, 0);
    create2(PCB, N, 0);
    print2(PCB, N, 0);

    // process 3 creates process 5, 6
    create2(PCB, N, 3);
    create2(PCB, N, 3);
    print2(PCB, N, 3);

    // process 5 creates process 7, 8, 9
    create2(PCB, N, 5);
    create2(PCB, N, 5);
    create2(PCB, N, 5);
    print2(PCB, N, 5);

    destroy2(PCB, N, 3);
    print2(PCB, N, 3);
    print2(PCB, N, 5);

    return 0;
}

void create2(struct pcb2 PCBArray[], int numberPCBs, int p)
{
    //TODO: create process p's child processes
    // found valid p and PCBArray is valid
    // search for valid index (-1), we can use the child of this process now
    // determine if the passed value needs a parent and what the parent is
    // numberPCBs is currently running processes

    int freeSpot = -1;
    
    for (int i = 0; i < N; i++) // find the freeSpot
    {
        if (PCBArray[i].parent == -1) // if PCBArray.size()
        {
             freeSpot = i;
             PCBArray[i].parent = p; // index is set to process p // added the .parent to it
             i = N; // exit loop
        }
    }
    // second loop search for parent and create parent/child relationship
    // recreate the tree (linked list)
    int possibleParent = 0;
    for (int i = 0; i < N; i++) 
    {
        if (PCBArray[i].first_child != -1 ) // free 
        {
            i = possibleParent; // index
            PCBArray[i].first_child = freeSpot; // set the parent to the child
            PCBArray[freeSpot].parent = possibleParent; // set the child to the parent
            i = N; // exit loop
        } 
    }

}

void destroy2(struct pcb2 PCBArray[], int numberPCBs, int p)
{
    //TODO: destroy all process p's children processes, no need to destroy process p itself

    // search through each level of the tree to destroy children
    // first_child, older, younger, not parent

    // three scenarios
    // p1 has no children, nothing to do
    // only p2 exists, p2 has no children, kill p2
    // p2 and p3 exist, p3 has no children, kill p3, does p2 have no children? kill p2

    destroyHelper(PCBArray, p);    

}
// the recursive function to destroy the children of p
void destroyHelper(struct pcb2 *PCBArray, int p)
{
    
    // recursive call, if children exist, call destroyHelper again
    if (PCBArray[p].first_child == -1)
    {
        return;
        //PCBArray[p] = -1;
    }
    // if a child exists
    destroyHelper(PCBArray, PCBArray[p].first_child); // keep searching until the bottom
    // lastly, set everything to -1
    PCBArray[p].first_child = -1; // set the child to -1
    PCBArray[p].older_sibling = -1; // set the older sibling to -1
    PCBArray[p].younger_sibling = -1; // set the younger sibling to -1
    

}

void print2(struct pcb2 PCBArray[], int numberPCBs, int p)
{

    printf("PCB Index %d: ", p);
    if (PCBArray[p].parent != -1)
    {
        printf("Status: allocated; Parent PCB Index %d; ", PCBArray[p].parent);
        printf("Children Index(es):");
        int current = PCBArray[p].first_child;
        while ( current != -1)
        {
            printf(" %d", current);
            current = PCBArray[current].younger_sibling;
        }
        printf("\n");
    }
    else
    {
        printf("Status: free.\n");
    }
}

