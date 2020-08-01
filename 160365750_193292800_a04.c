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