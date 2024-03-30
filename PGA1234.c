// include classes needed to run the c program
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function prototypes
int firstcomefirstserved();
int roundrobin();
int multilevel();

// main function
int main() {

    // Create integer variable choice
    char choice;

    // While true, ask user to select an operation
    while (1) {
        printf("Select an operation:\n");
        printf("1. First Come First Serve\n");
        printf("2. Round Robin\n");
        printf("3. Multilevel\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", &choice);

        switch (choice) {

            // If 1, go to FCFS algorithm
            case '1':
                firstcomefirstserved();
                break;

                // If 2, go to RR algorithm
            case '2':
                roundrobin();
                break;

                // If 3, go to Multi-Level Feedback Queue
            case '3':
                multilevel();
                break;

                // If 4, exit the program
            case '4':
                printf("Exiting the program.\n");
                return 0;

                // Else, display invalid
            default:
                printf("\nInvalid choice. Please select a valid option.\n");
        }

    }

    return 0;
}


/* --------------------------------------------1. First Come First Served(FCFS) Algorithm----------------------------------- */

// define a structure for FCFS process id, burst time and arrival time
// create a linked list to store all the process
struct FCFS{
    int id,bt,at;
    struct FCFS* next_node;
};

typedef struct FCFS FCFS;

// main program to run fsfc algorithm
int firstcomefirstserved() {
    int n, i;
    float tp=0,nop=0,completiontime=0;

    // define the head and current_node as empty before any process is stored
    FCFS* head=0;
    FCFS* current_node=0;

    // prompt for the number of process
    printf("Enter the number of process: ");
    scanf("%d",&n);

    //take the number of process as float to calculate throughput;
    nop=n;

    // for loop to prompt for burst time and arrival time
    // save the process details in linked list
    for (i=1;i<=n;i++) {
        FCFS* new_process=(FCFS*)malloc(sizeof(FCFS));

        // save process id
        new_process->id=i;

        // let user enter processes burst and arrival time
        printf("Enter process P%d burst time: ",i);
        // save processes burst time
        scanf("%d",&new_process->bt);
        // save processes arrival time
        printf("Enter process P%d arrival time: ",i);
        scanf("%d",&new_process->at);

        // Initialize the next_node pointer to 0
        new_process->next_node=0;

        if (head==0) {
            // if the list is empty then insert to head
            head=new_process;
            current_node=new_process;
        } else {
            // else insert to the next node
            current_node->next_node=new_process;
            current_node=new_process;
        }
    }

    // sort the processes based on arrival time using Bubble Sort
    for(i=0;i<n-1;i++){

        // set current node as head
        current_node=head;

        for(int j=0;j<n-i-1;j++){
            if(current_node->at>current_node->next_node->at){
                // swap the data in the linked list nodes
                // create temp variable to store the id, bt and at
                int temp_id=current_node->id;
                int temp_bt=current_node->bt;
                int temp_at=current_node->at;

                // set current value of id, bt and at to the value of next node
                current_node->id=current_node->next_node->id;
                current_node->bt=current_node->next_node->bt;
                current_node->at=current_node->next_node->at;

                // set the value of id,bt and at of next node to the value of current node
                current_node->next_node->id=temp_id;
                current_node->next_node->bt=temp_bt;
                current_node->next_node->at=temp_at;
            }
            // go to the next node
            current_node=current_node->next_node;
        }
    }

    // initialize variable for waiting time, turnaround time, and completion time
    int wt=0,tat=0,ct=0;

    // initialize variable for average waiting and turnaround time
    float awt=0,atat=0;

    // Display header
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    // Initialize current_node pointer to beginning of linked list
    current_node=head;

    // while current node != null, continue looping
   while(current_node!=0){

        // if previous process completion time < current process arrival time
        if((ct<current_node->at)){
            // set waiting time as 0
            wt=0;
        }
        else{
            // if previous process completion time > current process arrival time
            // waiting time = previous process completion time - current process arrival time
            wt=ct-current_node->at;
        }

        // calculate each process turnaround time
        tat=wt+current_node->bt;

        // calculate each process completion time
        ct=current_node->at+tat;

        // calculate the total waiting time
        awt+=wt;

        // calculate the total turnaround time
        atat+=tat;

        // display process id, burst time, arrival time, waiting time, turnaround time and completion time of each process
        printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\t\t%dms\n",current_node->id,current_node->bt,current_node->at,wt,tat,ct);

        // move to the next process in linked list
        current_node=current_node->next_node;

        //take the completion time as float to calculate throughput;
        completiontime=ct;
    }

    // gantt Chart to display the whole process timeline
    printf("\n\nGantt Chart\n\n");

    // Initialize the current_node pointer to the beginning
    current_node=head;

    // Initialize variable time to 0
    int time=0;

    // If arrival time of first process is not 0, display idle
    if (current_node->at!=0 ){
        printf("|Idle\t");

        // Set variable time = current_node arrival time
        time=current_node->at;
    }

    // While current_node not equal to null
    while(current_node!=0){

        //Display current node Process id
        printf("|P%d \t",current_node->id);

        // Calculate time
        time+=current_node->bt;

        // if next process not equal to null and current process completion time < next process arrival time
        if(current_node->next_node!=0 && time<current_node->next_node->at){
            printf("|Idle\t");

            // set time = next process arrival time
            time=current_node->next_node->at;
        }
        // move to next process
        current_node=current_node->next_node;
    }

    // print the completion line
    printf("|\n");

    // print the time from 0 if first process arrival time is not 0
    current_node = head;
    if (current_node->at != 0 ){
        printf("0\t");

    }

    // set time as current node arrival time
    time = current_node->at;

    // while current node is not 0, display time
    while (current_node != 0) {
        printf("%d\t", time);

        // Time increase by burst time
        time += current_node->bt;

        // if next process not equal to 0 and time < next process arrival time
        if (current_node->next_node != 0 && time < current_node->next_node->at) {
            printf("%d\t",time);
            // set variable time to next process arrival time
            time = current_node->next_node->at;
        }
        // move to next node
        current_node = current_node->next_node;
    }

    // print the completion time at the end of the gantt chart
    printf("%d\n\n",time);


    current_node=head;
    // free the memory for the linked list at the end of program
    while (current_node!=0) {
        FCFS* temp=current_node;
        current_node=current_node->next_node;
        free(temp);
    }

    // display total waiting and total turnaround time
    printf("\nTotal Waiting time: %.2fms",awt);
    printf("\nTotal Turnaround time: %.2fms\n",atat);

    // calculate average waiting and turnaround time
    awt /= n;
    atat /= n;
    tp= nop/completiontime;

    // display average waiting and turnaround time
    printf("\nAverage waiting time: %.2fms",awt);
    printf("\nAverage turnaround time: %.2fms",atat);
    printf("\nThroughput: %.2f process per ms\n\n",tp);

    // First Come First Served algorithm ended
    return 0;
}


/* ------------------------------------------------2. Round Robin(RR) algorithm--------------------------------------------- */


// define a structure for RR process id, burst time and arrival time
// create a pointer to the next process in linked list
struct RR {
    int id;
    int burstTime;
    int arrivalTime;
    bool firstuse;
    struct RR* next;
};

typedef struct RR RR;

// define a structure for all the process id, start and end time, waiting and turnaround time
// create a pointer to the next process in linked list for later use in constructing gantt chart
struct GanttEntry {
    int id;
    int startTime;
    int endTime;
    int waitingTime;
    int turnaroundTime;
    struct GanttEntry* next;
};

typedef struct GanttEntry GanttEntry;

// function to remove the process when it finished running from the list
void removeProcessesWithZeroBurstTime(RR** head) {

    // set current node to head
    RR* current = *head;

    // set previous node of current node as null
    RR* prev = NULL;

    // while current node is not null
    while (current != NULL) {
        // if current bursttime is 0
        if (current->burstTime == 0) {

            // remove process if it is first process
            if (prev == NULL) {
                // set head to next node
                *head = current->next;
            } else {
                // store next node in prev -> next
                prev->next = current->next;
            }
            // remove current process
            free(current);
            // if first process is deleted, set current node as head
            // if not first process deleted, set current node to prev -> next
            current = (prev == NULL) ? *head : prev->next;
        } else {
            // set prev as current node
            prev = current;
            // move to next node
            current = current->next;
        }
    }
}

// receive the original unsorted linked list and sort the linked list based on arrival times
RR* sortProcessesByArrivalTime(RR* head) {
    RR* current = head;

    while (current != NULL) {
        // set nextProcess as the next process of current process to be compare
        RR* nextProcess = current->next;

        while (nextProcess != NULL) {
            // if current arrivale time larger than next process arrival time, swap
            if (current->arrivalTime > nextProcess->arrivalTime) {
                // Swap the arrival times, burst times, and process IDs
                int tempArrivalTime = current->arrivalTime;
                current->arrivalTime = nextProcess->arrivalTime;
                nextProcess->arrivalTime = tempArrivalTime;

                int tempbursttime = current->burstTime;
                current->burstTime = nextProcess->burstTime;
                nextProcess->burstTime = tempbursttime;

                int tempProcessID = current->id;
                current->id = nextProcess->id;
                nextProcess->id = tempProcessID;

                // swap the boolean of firstuse
                bool tempfirstuse = current->firstuse;
                current->firstuse = nextProcess->firstuse;
                nextProcess->firstuse = tempfirstuse;
            }

            // set nextProcess to next process of current next process
            nextProcess = nextProcess->next;
        }
        // set current to next process
        current = current->next;
    }
    return head;
}

// only sort the first two node in the linked list
RR* sortFirstTwoProcessesByArrivalTime(RR* head) {
    if (head == NULL || head->next == NULL) {
        // if not enough nodes to sort or the list is empty, skip this method
        return head;
    }

    RR* current = head;
    RR* nextProcess = current->next;

    // if current process arrival time equal to next process arrival time
    if (current->arrivalTime == nextProcess->arrivalTime) {
        // swap the arrival times, burst times, process IDs and the flag for first use
        int tempArrivalTime = current->arrivalTime;
        current->arrivalTime = nextProcess->arrivalTime;
        nextProcess->arrivalTime = tempArrivalTime;

        int tempBurstTime = current->burstTime;
        current->burstTime = nextProcess->burstTime;
        nextProcess->burstTime = tempBurstTime;

        int tempProcessID = current->id;
        current->id = nextProcess->id;
        nextProcess->id = tempProcessID;

        bool tempfirstuse = current->firstuse;
        current->firstuse = nextProcess->firstuse;
        nextProcess->firstuse = tempfirstuse;
    }
    return head;  //return the updated head
}

// append a Gantt chart entry to the Gantt chart list
GanttEntry* appendToGanttChart(GanttEntry* head, int id, int startTime, int endTime, int waitingTime, int turnaroundTime) {
    GanttEntry* newEntry = (GanttEntry*)malloc(sizeof(GanttEntry));
    newEntry->id = id;
    newEntry->startTime = startTime;
    newEntry->endTime = endTime;
    newEntry->waitingTime = waitingTime;
    newEntry->turnaroundTime = turnaroundTime;
    newEntry->next = NULL;

    if (head == NULL) {
        // if head is null, save to head
        head = newEntry;
    } else {

        GanttEntry* current = head;
        // continue looping to save the details for gantt chart
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEntry;
    }
    return head;
}

// function to do the round robin algorithm
void rr(struct RR* head, int quantum, int n) {

    // sort the arrival times using the function above
    head = sortProcessesByArrivalTime(head);

    // define the gantt chart as empty before any node is stored
    GanttEntry* ganttChart = NULL;

    // define end time and process id for the first process
    int endTime = head->arrivalTime;

    // display the headings of the result
    printf("\n\nRound Robin Scheduling with Quantum %d:\n\n", quantum);
    printf("Process\tStart time\tEnd time\tWaiting time\tTurnaround time\n");

    // when the first process arrival time is not 0 means the cpu is idle
    if (head->arrivalTime != 0) {
        printf("\n------------------------CPU Idle from 0ms to %dms-----------------------\n\n", head->arrivalTime);
        // save the information to gantt chart linked list for later use
        ganttChart = appendToGanttChart(ganttChart, -1, 0, head->arrivalTime,0,0);
    }

    // initialize waiting time, turnaround time, and sum of process
    int wt, tat, sum = 0;
    // initialize variables for average waiting time and average turnaround time
    float awt = 0.0, atat = 0.0;
    // initialize 'current' to point to the head of the linked list
    struct RR* current = head;
    // initialize completed process as 0
    int completedProcesses = 0;

    // loop which only exit when completed process is equal to the total number of process
    while(1){
            // if the process burst time is >0 and arrival time is <= end time then the process will be run
            if (current->burstTime > 0 && current->arrivalTime <= endTime) {

                // set the boolean firstuse as true for later condition checking
                current->firstuse=true;

                // if the burst time is bigger than the quantum then quantum amount of time will be run
                if (current->burstTime > quantum) {
                    // completion time = endTime + quantum
                    endTime += quantum;
                    // remaining burst time will be deducted by quantum
                    current->burstTime -= quantum;

                    // calculate the waiting time, turnaround time, and sum up all the waiting time and turnaround time for further use
                    if ((endTime - quantum - current->arrivalTime) < 0) {
                        sum += 1;
                        wt = 0;
                        tat = wt + quantum;
                        current->arrivalTime = endTime;
                        awt += wt;
                        atat += tat;
                    } else {
                        sum += 1;
                        wt = endTime - quantum - current->arrivalTime;
                        tat = wt + quantum;
                        current->arrivalTime = endTime;
                        awt += wt;
                        atat += tat;
                    }
                    // display the result and save the process id, start and end time in gantt chart linked list
                    printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\n\n", current->id, endTime - quantum, endTime, wt, tat);
                    ganttChart = appendToGanttChart(ganttChart, current->id, endTime - quantum, endTime, wt, tat);
                // if the burst time is smaller than the quantum then the whole burst time will be run
                // the completion time will be previous completion time + remaining burst time
                } else {
                    endTime += current->burstTime;

                    // calculate the waiting time, turnaround time, and sum up all the waiting time and turnaround time for further use
                    if ((endTime - current->burstTime - current->arrivalTime) < 0) {
                        sum += 1;
                        wt = 0;
                        tat = wt + current->burstTime;
                        current->arrivalTime = endTime;
                        awt += wt;
                        atat += tat;
                    } else {
                        sum += 1;
                        wt = endTime - current->burstTime - current->arrivalTime;
                        tat = wt + current->burstTime;
                        current->arrivalTime = endTime;
                        awt += wt;
                        atat += tat;
                    }
                    // display the result and save the process id, start and end time in gantt chart linked list
                    printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\n", current->id, endTime - current->burstTime, endTime, wt, tat);
                    ganttChart = appendToGanttChart(ganttChart, current->id, endTime - current->burstTime, endTime, wt, tat);
                    // the burst time will be equal to zero as all the burst time has been run
                    current->burstTime = 0;
                    // display that the process has been completed
                    if (current->burstTime == 0) {
                        printf("\n-------------------------Process %d completed!--------------------------\n\n", current->id);
                        completedProcesses+=1;
                        // if all the process has been completed then exit the while loop
                        if (completedProcesses == n) {
                        goto exit;
                        }
                    }

                    // if current process is not the last process
                    if (current->next != NULL){
                        // if next process arrival time larger than previous process completion time, display cpu idle
                        if (current->next->arrivalTime > endTime) {
                            printf("\n------------------------CPU Idle from %dms to %dms-----------------------\n\n", endTime, current->next->arrivalTime);
                            // save the idle time in gantt chart linked list
                            ganttChart = appendToGanttChart(ganttChart, -1, endTime, current->next->arrivalTime,0,0);
                            // next process arrival time will be stored in the end time variable to continue with next process execution
                            endTime = current->next->arrivalTime;
                        }
                    }
                }
            }
            // call function to remove completed process
            removeProcessesWithZeroBurstTime(&head);
            current= sortProcessesByArrivalTime(head);
            // if one of the process arrival time is same as another process completion time and the process did not run the algorithm before
            if(current->firstuse == true){
                current= sortFirstTwoProcessesByArrivalTime(head);
            }
    }

    // when all process has been completed will exit to here
    exit:
    // calculate the average waiting and turnaround time
    awt = awt / n;
    atat = atat / n;

    // print Gantt Chart
    GanttEntry* ganttCurrent = ganttChart;
    printf("Gantt Chart:\n\n");
    // print the process id with idle time
    while (ganttCurrent != NULL) {
        // if the id is -1 means it is idle
        if (ganttCurrent->id == -1) {
            printf("|Idle\t");
        // else print the process id
        } else {
            printf("|P%d\t", ganttCurrent->id);
        }
        // move to next node
        ganttCurrent = ganttCurrent->next;
    }

    // print the completion line
    printf("|\n");

    // move back to the head to print the start time
    ganttCurrent = ganttChart;
    while (ganttCurrent != NULL) {
            // print all the start time of each process
            printf("%d\t", ganttCurrent->startTime);
        // move to next node
        ganttCurrent = ganttCurrent->next;
    }

    // move back to the head to print completion time
    ganttCurrent = ganttChart;
    while (ganttCurrent->next != NULL) {
        // continuously move until the last node is reached
        ganttCurrent = ganttCurrent->next;
    }
    // print the completion time
    printf("%d",ganttCurrent->endTime);

    // Calculate throughput
    float nop = n;
    float tp = nop / ganttCurrent -> endTime;

    printf("\n\n\n");

    // create array  list with number of user input
    int totalWaitingTime[n];
    int totalTurnaroundTime[n];

    // initialize the array with value 0
    for (int i = 1; i <= n; i++) {
        totalWaitingTime[i] = 0;
        totalTurnaroundTime[i] = 0;
    }

    for (ganttCurrent = ganttChart; ganttCurrent != NULL; ganttCurrent = ganttCurrent->next) {
        if(ganttCurrent->id != -1){
            // accumulate waiting time and turnaround time for the process
            totalWaitingTime[ganttCurrent->id] += ganttCurrent->waitingTime;
            totalTurnaroundTime[ganttCurrent->id] += ganttCurrent->turnaroundTime;
        }
    }

    printf("Process\tTotal Waiting Time\tTotal Turnaround Time\n");
    // print the calculated total waiting time and turnaround time for each process
    for (int i = 1; i <= n; i++) {
        printf("P%d\t", i);
        printf("%d\t\t\t", totalWaitingTime[i]);
        printf("%d\n", totalTurnaroundTime[i]);
    }

    // free Gantt chart memory
    GanttEntry* ganttTemp;
    ganttCurrent = ganttChart;
    while (ganttCurrent != NULL) {
        ganttTemp = ganttCurrent;
        ganttCurrent = ganttCurrent->next;
        free(ganttTemp);
    }



    // display the average waiting and turnaround time calculated
    printf("\n\nAverage waiting time: %.2fms", awt);
    printf("\nAverage turnaround time: %.2fms\n",atat);
    printf("\nThroughput: %.2f process per ms\n\n", tp);

}

// main function to run the round robin algorithm
int roundrobin() {
    // initialize quantum and number of process
    int quantum;
    int n;

    // prompt for user input
    printf("Enter the quantum of the system: ");
    scanf("%d", &quantum);
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("\n");
    // declare and initialize the 'head' pointer, indicating an empty linked list
    struct RR* head = NULL;

    // declare and initialize the 'current' pointer, which will be used for traversal
    struct RR* current = NULL;

    // loop to create and initialize new nodes for the linked list
    for (int j = 0; j < n; j++) {
        // create a new process node and allocate memory for it
        struct RR* new_process = (struct RR*)malloc(sizeof(struct RR));

        // assign a unique ID and boolean firstuse to the process node (j + 1)
        new_process->id = j + 1;
        new_process->firstuse = false;

        // prompt the user to enter burst time for the process
        printf("Enter the burstTime for process %d: ", j + 1);
        scanf("%d", &new_process->burstTime);

        // prompt the user to enter arrival time for the process
        printf("Enter the arrival time for process %d: ", j + 1);
        scanf("%d", &new_process->arrivalTime);
        printf("\n");

        // check if the linked list is empty
        if (head == NULL) {
            // if it's empty, set the 'head' and 'current' pointers to the new node
            head = new_process;
            current = new_process;
            current->next=NULL;
        } else {
            current->next = new_process;
            current = new_process;
            new_process->next=NULL;
        }
    }

    // pass the arguments to function rr to do the round robin scheduling
    rr(head, quantum,n);
}

/* ---------------------------------3. Multi-Level Feedback Queue(MLFQ) with two queues------------------------------- */

// define a structure for multi-level process id, burst time, arrival time, total turnaroudn time, completion time, temp completion time and waiting time
struct MLFQ
{
    int processno;
    int bt;
    int at;
    int tat;
    int ct;
    int tempct;
    int wt;
};

// Function to swap two MLFQ structures
void swap(struct MLFQ *xp, struct MLFQ *yp)
{
    struct MLFQ temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// bubble sort algorithm to swap the processes based on arrival time
void bubblesort(struct MLFQ arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].at > arr[j + 1].at)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Sort processes based on process id
void procsort(struct MLFQ arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].processno > arr[j + 1].processno)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


int multilevel()
{
    // create array and variables needed
    struct MLFQ proc[20], remaining[20],gantt[20];
    int n, qt;
    float awt,atat;
    float nop=0,ct=0,tp=0;

    // Ask the user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    //take the number of process as float to calculate throughput
    nop = n;

    // ask user for processes waiting time and arrival time
    for (int i = 0; i < n; i++)
    {
        // store process no into array proc[]
        proc[i].processno = i + 1;

        printf("Enter arrival time of process %d (ms): ", i + 1);
        scanf("%d", &proc[i].at);

        printf("Enter burst time of process %d(ms): ", i + 1);
        scanf("%d", &proc[i].bt);

        remaining[i] = proc[i];
    }

    // let user enter the quantum of round robin queue
    printf("Enter quantum time for first queue(ms):");
    scanf("%d", &qt);

    // call function bubble sort
    bubblesort(proc, n);
    bubblesort(remaining, n);

    //initialize average waiting time and average turnaround time as 0
    awt=0.0;
    atat=0.0;

    // Display heading of Round Robin queue
    printf("\nProcess\tStart Time\tTurnaround Time\tWaiting Time\tCompletion Time\n");
    printf("\n------------------------Round robin queue---------------------------\n\n");

    // round robin (queue 1)
    // display CPU idle if first process arrival time is not 0
     if (proc[0].at!=0)
    {

        printf("\n......................CPU Idle from 0ms to %dms......................\n\n", proc[0].at);
    }
    int currenttime = proc[0].at;
    int done = 0;
    int count = 0;
    int fcfscount =0;
    int endrr[n];
    bool haveidle = false;
    int currenttime_fcfs =0;

    // while value of variable done < n, continue looping
    while (done < n)
    {
        int currenttime_fcfs = currenttime;
        for (int i = 0; i < n; i++)
        {
            // if there is idle, run fcfs process

            if (currenttime < proc[i].at && fcfscount > 0)
            {
                haveidle = true;

                printf("\n-------------------First come first serve queue----------------------\n\n");
                // FCFS (queue 2)
                currenttime_fcfs = currenttime;
                for (int i=0; i<n ; i++)
                {
                    //printf("xxx%d",remaining[i].bt);
                    // if remaining burst time larger than 0, increase current time by remaining burst time
                    if (remaining[i].bt > 0)
                    {
                        int temp=currenttime;
                        currenttime_fcfs += remaining[i].bt;
                        remaining[i].ct = currenttime_fcfs;

                        // calculate waiting time
                        int wt=temp-proc[remaining[i].processno].tempct;
                        remaining[i].tat = currenttime_fcfs - remaining[i].at;
                        remaining[i].wt = remaining[i].tat - remaining[i].bt - qt;
                        printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\t\t\n", remaining[i].processno, temp, remaining[i].ct-currenttime + wt, currenttime-proc[remaining[i].processno].tempct,remaining[i].ct);
                        //Display completed in first come first served queue if process is completed in this queue
                        printf("\n--------Process %d completed in first come first serve queue!---------\n\n", remaining[i].processno);

                        proc[i].ct = remaining[i].ct;
                        proc[i].wt = remaining[i].wt;
                        proc[i].tat = remaining[i].tat;

                        currenttime = remaining[i].ct;
                        awt = awt + remaining[i].wt;
                        atat = atat + remaining[i].tat;
                        gantt[count].wt = remaining[i].ct;
                        gantt[count].at = remaining[i].at;
                        gantt[count].processno = remaining[i].processno;
                        gantt[count].ct = temp;
                        gantt[count].bt = remaining[i].bt;
                        gantt[count].tempct = 1;
                        count++;
                        fcfscount --;
                        remaining[i].bt = 0;

                        if ( haveidle == true)
                        {
                            if (fcfscount == 0 || currenttime >= proc[i+2].at )
                            {
                            haveidle = false;
                            break;
                            }


                        }


                    }
                    // set waiting time to zero if it is smaller than 0
                    if (proc[i].wt < 0 )
                    {
                        proc[i].wt = 0;
                    }
                }
                if (currenttime < proc[i].at && fcfscount == 0)
                {
                    int temp4=currenttime;
                    printf("\n......................CPU Idle from %dms to %dms......................\n\n",temp4, proc[i].at);
                    // set current time as process arrival time
                    currenttime = proc[i].at;

                    gantt[count-1].tempct = 0;
                }


            }

            if (remaining[i].bt > 0)
            {
                printf("\n------------------------Round robin queue---------------------------\n\n");
                // if remaining burst time > 0 and <= quantum,
                if (remaining[i].bt <= qt)
                {
                    // calculate currenttime, completion time, turnaround time, waiting time, burst time, average turnaround time and average waiting time
                    int temp = currenttime;
                    currenttime = currenttime + proc[i].bt;
                    proc[i].ct= currenttime;
                    proc[i].tat = currenttime - proc[i].at;
                    proc[i].wt = proc[i].tat - proc[i].bt;
                    awt = awt + proc[i].wt;
                    atat = atat + proc[i].tat;
                    // save remaining burst time as 0
                    remaining[i].bt = 0;
                    proc[proc[i].processno].tempct=currenttime;
                    // increas the value of done by 1
                    done++;

                    printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\t\t\n", proc[i].processno, temp, proc[i].tat, proc[i].wt,proc[i].ct);
                    // Display completed if process completely runs its burst time
                    printf("\n-------------Process %d completed in round robin queue!--------------\n\n", proc[i].processno);
                    // save process no, arrival time, temp, burst time and completion time for gantt chart use
                    gantt[count].at = proc[i].at;
                    gantt[count].processno = proc[i].processno;
                    gantt[count].ct = temp;
                    gantt[count].bt = proc[i].bt;
                    gantt[count].wt = proc[i].ct;

                    // increas value of count by 1
                    count++;

                }
                else
                {
                    fcfscount++;
                    // if remaining burst time >quantum
                    int temp=currenttime;

                    // increase currenttime value by quantum
                    currenttime = currenttime + qt;

                    // calculate remaining burst time, turnaround time, waiting time and completion time
                    remaining[i].bt = remaining[i].bt - qt;
                    proc[i].tat = currenttime - proc[i].at;
                    proc[i].wt = proc[i].tat - proc[i].bt;
                    proc[i].ct= currenttime;

                    // set waiting time to 0 if waiting time < 0 is get from calculation
                    if (proc[i].wt < 0)
                    {
                        proc[i].wt = 0;
                    }

                    printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\t\t\n", proc[i].processno, temp,proc[i].tat, temp-proc[i].at,currenttime);
                    printf("\n----Process %d not completed in round robin, passed to fcfs queue----\n\n", proc[i].processno);
                    done++;
                    proc[proc[i].processno].tempct=currenttime;
                    gantt[count].wt = proc[i].ct;
                    gantt[count].at = proc[i].at;
                    gantt[count].processno = proc[i].processno;
                    gantt[count].ct = temp;
                    gantt[count].bt = proc[i].bt;
                    count ++;
                    //printf("*%d*%d*",i,count);

                }
            }
        }
    }

    printf("\n-------------------First come first serve queue----------------------\n\n");

    // FCFS (queue 2)
    currenttime_fcfs = currenttime;
    for (int i=0; i<n ; i++)
    {
        // if remaining burst time larger than 0, increase current time by remaining burst time
        if (remaining[i].bt > 0)
        {
            int temp=currenttime;
            currenttime_fcfs += remaining[i].bt;
            remaining[i].ct = currenttime_fcfs;

            // calculate waiting time
            int wt=temp-proc[remaining[i].processno].tempct;
            remaining[i].tat = currenttime_fcfs - remaining[i].at;
            remaining[i].wt = remaining[i].tat - remaining[i].bt - qt;
            printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\t\t\n", remaining[i].processno, temp, remaining[i].ct-currenttime + wt, currenttime-proc[remaining[i].processno].tempct,remaining[i].ct);
            //Display completed in first come first served queue if process is completed in this queue
            printf("\n--------Process %d completed in first come first serve queue!---------\n\n", remaining[i].processno);
            //take the completion time as float to calculate throughput
            ct=remaining[i].ct;

            currenttime = remaining[i].ct;
            awt = awt + remaining[i].wt;
            atat = atat + remaining[i].tat;
            gantt[count].wt = remaining[i].ct;
            gantt[count].at = remaining[i].at;
            gantt[count].processno = remaining[i].processno;
            gantt[count].ct = temp;
            gantt[count].bt = remaining[i].bt;
            count++;

        }
        // set waiting time to zero if it is smaller than 0
        if (proc[i].wt < 0 )
        {
            proc[i].wt = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (remaining[i].bt!=0)
        {
            for (int j = 0; j < n; j++)
                {
                    if (remaining[i].processno==proc[j].processno)
                    {
                        proc[j]=remaining[i];
                        proc[j].bt=remaining[i].bt+qt;
                    }
                }
        }
    }

    procsort(proc,n);

// displayed gantt chart
    printf ("\nGantt Chart\n");
    if (proc[0].at != 0)
    {
        // if arrival time no start from 0, displayed idle
        printf("|idle\t");
    }
    for (int i=0; i<count ; i++)
    {
        // display process no on gantt chart
        printf("|P%d\t",gantt[i].processno);

        // if i + 1 == count, end the loop
        if (i+1 == count)
        {
            break;
        }

        // if current waiting time != gantt chart completion time
        if (gantt[i+1].ct != gantt[i].wt)
        {
            if (gantt[i].tempct == 1)
            {
            printf("|P%d\t",gantt[i].processno);
            }
            else if (gantt[i].tempct == 0)
            {
                printf("|idle\t");
            }
        }

    }
    printf("|");
    if (proc[0].at != 0)
    {
        // display 0 if proc[0].at is not 0
        printf("\n0\t");
    } else {
        printf("\n");
    }
    for (int j=0; j<count ; j++)
    {
        printf("%d\t",gantt[j].ct);

        // if value j + 1 == count, break
        if (j+1 == count)
        {
            break;
        }

        if (gantt[j+1].ct != gantt[j].wt)
        {
            printf("%d\t",gantt[j].wt);
        }

    }

    // display current time for fcfs queue
    printf("%d\n",currenttime_fcfs);

    // display heading
    printf("\nProcess\tBurst Time\tArrival Time\tTurnaround Time\tWaiting Time\tCompletion Time\n");
    for (int i = 0; i < n; i++)
    {
        // display value of the process
        printf("P%d\t%dms\t\t%dms\t\t%dms\t\t%dms\t\t%dms\t\t\n", proc[i].processno, proc[i].bt, proc[i].at, proc[i].tat, proc[i].wt,proc[i].ct);
    }

    // calculate average waiting and turnaround time
    awt = awt/n;
    atat= atat/n;
    tp  = nop/ct;

    // displaye average waiting and turnaround time;
    printf("\nAverage waiting time: %.2fms\n",awt);
    printf("Average turnaround time: %.2fms",atat);
    printf("\nThroughput: %.2f process per ms\n\n",tp);

    // multi-level feedback queue ended
    return 0;
}
