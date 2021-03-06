
//
//  GitHub Link: https://github.com/harshul25/Assignment-4
//  160365750_193292800_a04.c
//  Assignment #4
//
//  Created by Harshul Mehta and Jiachun Xiang on 2020-07-26.
//  Copyright © 2020 Harshul Mehta. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdbool.h>

#define Len 10 //Note: hardcoded, this program handles a maximum of ten rosources and ten processes.
pthread_mutex_t lock; //to ensure only one process is in the critical section.
int maximum[Len][Len]; //stores the maximum allocated resources per process.
int available[Len]; //stores the available resources after allocation is done.
int allocation[Len][Len]; // stores resources that are allocated per process.
int need[Len][Len]; //stores the resources needed per process.
int used[Len];
int work[Len]; //stores availible resources for bankers algorthim.
bool Finish[Len]; //ensures all processes have been processed.
struct dimentions{ //used to stores the dimentions of each matrix.
    int row;
    int col;
}limit;
typedef struct thread// used to represent a single thread.
{
    int tid;
    int state;
    pthread_t handle;
    int retVal;
} Thread;
//-----
int readInput(void);//reads the input for each request the user makes.
int readFile(void);//reads the txt file and stores maximum values for each resource of each process.
int isSafe(void);// checks for safe state.
void printMatrix(void); //prints allocated and available matrix.
int computation(void); //executes bankers algorithm and finds the safe sequence.
void* threadRun(void* t);//the thread funtion, the code executed by each thread.

int main(int argc, const char * argv[]) {
    
    int counter;
    if(argc < 3){ 
        //check if at least two arguments (multi-resources) state their available status
        printf("Input 2 Resource Available nums please...exiting with error code-1\n")
        return -1;
    }else{ 
        //parse and store them in avalible array.
        for(counter=0;counter<argc-1;counter++)
            available[counter] = atoi(argv[counter+1]);
    }
    
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        //initializes the mutex lock.
        printf("\n mutex init has failed\n");
        return 1;
    }
    
    printf("The number of customers is: %d \n", counter);
    //read text file
    readFile(); 
    printf("Maximum Resources:\n");
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("Available Resources:\n");
    for (int j = 0; j < limit.col; j++) {
        printf("%d ", available[j]);
    }
    printf("\n");
    //read input file
    readInput(); 
     //if not safe then we stop.
    if(isSafe() == 1){
        return 0;
    }
    //run bankers algorithm.
    computation(); 
    // clears the mutex lock
    pthread_mutex_destroy(&lock);
    return 0;
}

int readFile(){ //read off the txt file provided and store values in our maximum array.
    int c;
    FILE *file;
    int row = 0;
    int col = 0;
    file = fopen("sample4_in.txt", "r");
    if (file) {
          //iterate through every character in the txt file
        while ((c = getc(file)) != EOF){
            if(row == 0 && c==','){
                col++;
            }
            if(c=='\n'){
                row++;
            }
        }
        row++;
        col++;
        limit.row = row;
        limit.col = col;
        fseek(file, 0, SEEK_SET);
        int i=0;//row
        int j=0;//col
        while ((c = getc(file)) != EOF){
            if(c>='0' && c<='9'){
                 maximum[i][j] = c-48;
            }else if( c==','){
                j++;
            }else if(c=='\n'){
                i++;
                j=0;
            }
        }
        fclose(file);
    }
    return 0;
}
//reads each process request given by the user and stores it in the allocation array
int readInput(){ 
    for (int i = 0; i < Len; i++) {
        for (int j = 0; j < Len; j++) {
            allocation[i][j] = 0;
        }
    }
    bool check = true;
    while(check){
    char string[Len+3];
    char *test = string;
    printf("Enter a Command: ");
    scanf("%s",test);
        if(*test == '*'){
            check = false;
            printMatrix();
            //if you try to allocate resources for threads that arent used.
        }else if((*(test+2)-48)>=limit.row){ 
            printf("Out of bounds!\n");
        //Adding resources
        }else if(*(test+1) == 'Q'){ 
            int row = *(test+2)-48;
            for(int i = 3; i<limit.col+3; i++){
                allocation[row][i-3] += *(test+i)-48;
            }
            printf("Request Completed!\n");
            //Removing resources
        }else if(*(test+1) == 'L'){ 
            int row = *(test+2)-48;
            for(int i = 3; i<limit.col+3; i++){
                allocation[row][i-3] -= *(test+i)-48;
            }
            printf("Request Completed!\n");
        }
        
    }
    return 0;
}
//calculates the need matrix and then checks for safe state
int isSafe(){
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            need[i][j] = maximum[i][j]-allocation[i][j];
        }
    }
    
    printf("Needed Resources:\n");
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            if(need[i][j]<0){
                printf("Not Safe!");
                return 1;
            }
        }
    }
    
    printf("Available Resources:\n");
        for (int j = 0; j < limit.col; j++) {
            work[j] = available[j];
             printf("%d ", work[j]);
        }
        for (int j = 0; j < limit.col; j++) {
            Finish[j] = false;
        }
    return 0;
}
void printMatrix(){ //prints allocated resource matrix and maximum resource matrix.
    printf("Allocated Resources:\n");
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("Maximum Resources:\n");
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
}

int isSafe(){ //calculates the need matrix and then checks for safe state.
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            need[i][j] = maximum[i][j]-allocation[i][j];
        }
    }
    
    printf("Needed Resources:\n");
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < limit.row; i++) {
        for (int j = 0; j < limit.col; j++) {
            if(need[i][j]<0){
                printf("Not Safe!");
                return 1;
            }
        }
    }
    
    printf("Available Resources:\n");
        for (int j = 0; j < limit.col; j++) {
            work[j] = available[j];
             printf("%d ", work[j]);
        }
        for (int j = 0; j < limit.col; j++) {
            Finish[j] = false;
        }
    return 0;
}


int computation(void){//runs bankers algorithm and finds safe sequence.
    printf("\nEnter a Command: Run\n");
    int count = 0;//counter variable.
    bool safe; //counter variable.
    while(count < limit.row){ //ensure all processes have been run.
        for (int i = 0; i < limit.row; i++) {
            safe = true;
            int j;
            for (j = 0; j < limit.col && safe; j++) {
                if(!Finish[i]){
                    if(need[i][j] > work[j]){
                        safe = false;
                    }
                }else{
                    safe = false;
                    break;
                }
            }
            if(safe){
                Thread *thread = NULL;
                thread = (Thread*)malloc(sizeof(Thread));//allocate space for thread.
                thread->tid = i;
                thread->state = 1;
                thread->retVal = pthread_create(&(thread->handle),NULL,threadRun,thread);//run thread.
                sleep(1); //gives the dramatic feel of threadding
                Finish[i] = true;
                count++;
                
            }
        }
    }
    printf("\nEnter Command: Exit\n");
    return 0;
}
void logStart(int tID)
{
    printf("\n\t New Thread with ID %d is started.", tID);
}

void logFinish(int tID)
{
    printf("\n\t Thread with ID %d is finished.", tID);
}

void* threadRun(void* t)//Thread function.
{
    pthread_mutex_lock(&lock); //mutex lock so that only one thread is in the CS
    
    int i = ((Thread*)t)->tid;
    printf("-->  Customer %d :\n",i);
    printf("\t Allocated Resources: ");
    for (int j = 0; j < limit.col; j++) {
        printf("%d ",allocation[i][j]);
    }
    printf("\n");
    
    printf("\t Needed Resources: ");
    for (int j = 0; j < limit.col; j++) {
        printf("%d ",need[i][j]);
    }
    printf("\n");
    
    printf("\t Availible Resources: ");
    for (int j = 0; j < limit.col; j++) {
        printf("%d ",work[j]);
    }
    logStart(((Thread*)t)->tid);
    logFinish(((Thread*)t)->tid);
    printf("\n");
    printf("\t Thread is releasing resources...\n");
    //increment the free space to work with:
    for (int j = 0; j < limit.col; j++) {
        work[j] += allocation[i][j];
    }
    printf("\t New Availible Resources: ");
    for (int j = 0; j < limit.col; j++) {
        printf("%d ",work[j]);
    }
    printf("\n");
    
    pthread_mutex_unlock(&lock); //release the CS so that another thread can enter.
    pthread_exit(0);
}
