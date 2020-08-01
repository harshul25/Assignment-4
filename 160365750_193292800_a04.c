//
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


int readFile(){ //read off the txt file provided and store values in our maximum array.
    int c;
    FILE *file;
    int row = 0;
    int col = 0;
    file = fopen("sample4_in.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF){ //iterate through every character in the txt file
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

int readInput(){ //reads each process request given by the user and stores it in the allocation array.
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
        }else if((*(test+2)-48)>=limit.row){ //if you try to allocate resources for threads that arent used.
            printf("Out of bounds!\n");
        
        }else if(*(test+1) == 'Q'){ //Adding resources.
            int row = *(test+2)-48;
            for(int i = 3; i<limit.col+3; i++){
                allocation[row][i-3] += *(test+i)-48;
            }
            printf("Request Completed!\n");
        }else if(*(test+1) == 'L'){ //Removing resources.
            int row = *(test+2)-48;
            for(int i = 3; i<limit.col+3; i++){
                allocation[row][i-3] -= *(test+i)-48;
            }
            printf("Request Completed!\n");
        }
        
    }
    return 0;
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
