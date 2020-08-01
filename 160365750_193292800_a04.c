int main(int argc, const char * argv[]) {
    
    int counter;
    if(argc < 3){ 
        //check if at least two arguments (multi-resources) state their available status
        printf("Input 2 Resource Available nums please...exiting with error code-1\n")
        return -1;
    }else{ 
        //parse and store them in avalible array.
        for(counter=0;counter<argc;counter++)
            available[counter]=(int)(argv[counter]-48);
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

//read off the txt file provided and store values in our maximum array.
int readFile(){ 
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