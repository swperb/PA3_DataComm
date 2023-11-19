/*
    Name(s): Stephen Proctor, Brandon Ladner           Date: 11/20/23
    NetID(s): swp116, bjl298                           Due Date: 11/20/23  

*/


//include files for file i/o, RNG, math functions
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//linear backoff function, takes in N devices
int linearBackoff(int N) {
    
    //iteration variables
    int i;
    int j;
    int k;
    //Window size array
    int* W;
    //initialize number of slots
    int slots = 2;
    //initialize number of succesful devices
    int success = 0;
    //initialize selected slot
    int selection;
    

    //seed RNG
    srand(time(NULL));


    //Loop until every device succeeds
    while(N > 0) {
        //initialze contiguous int array to record device selections
        //this is reinitialized each iteration
        W = (int*)calloc(slots, sizeof(int));


        //loop for every device
        for (i = 0; i < N; i++) {

            //device selects random slot
            selection = rand() % slots;

            //increment the corresponding slot array with selection
            W[selection] += 1;

        }


        //loop through each slot
        for (k = 0; k < slots; k++) {

            //if one device picked a slot, that device succeeded
            if(W[k] == 1) {
                //increment success counter
                success++;
            }
        }
    
        //decrement successful devices
        N -= success;

        //increase slots by factor of 1 (linear)
        slots += 1;

    }
    //return number of slots required for every device to succeed
    return slots;
}




//binary exponential backoff function, takes in N devices
int binaryExponentialBackoff(int N) {

    //iteration variables
    int i;
    int j;
    int k;
    //window size array
    int* W;
    //initialize number of slots
    int slots = 2;
    //initialize number of successful devices
    int success = 0;
    //initialize selected slot
    int selection;


    //seed RNG
    srand(time(NULL));


    //loop until every device succeeds
    while(N > 0) {

        //initialze contiguous int array to record device selections
        //this is reinitialized each iteration
        W = (int*)calloc(slots, sizeof(int));


        //loop for every device
        for (i = 0; i < N; i++) {

            //device selects random slot
            selection = rand() % slots;

            //increment the corresponding slot array with selection
            W[selection] += 1;

        }  


        //loop through each slot
        for (k = 0; k < slots; k++) {

            //if one device picked a slot, that device succeeded
            if(W[k] == 1) {
                //increment success counter                
                success++;
            }
        }                  

        //decrement successful devices
        N -= success;

        //increase slots by factor of 2 (binary exponential)
        slots *= 2;
    }

    //return number of slots required for every device to succeed
    return slots;
}





//loglog backoff function, takes in N devices
int loglogBackoff(int N) {

    //iteration variables
    int i;
    int j;
    int k;
    //window size array
    int* W;
    //initialize number of slots
    int slots = 4;
    //initialize number of successful devices
    int success = 0;
    //initialize selected slot
    int selection;


    //seed RNG
    srand(time(NULL));


    //loop until every device succeeds    
    while(N > 0) {

        //initialze contiguous int array to record device selections
        //this is reinitialized each iteration
        W = (int*)calloc(slots, sizeof(int));


        //loop for every device
        for (i = 0; i < N; i++) {

            //device selects random slot
            selection = rand() % slots;

            //increment the corresponding slot array with selection
            W[selection] += 1;

        }        


        //loop through each slot
        for (k = 0; k < slots; k++) {

            //if one device picked a slot, that device succeeded
            if(W[k] == 1) {

                //increment success counter        
                success++;
            }
        }


        //decrement successful devices
        N -= success; 

        //increase slots using formula (loglog)
        slots = floor((1 + 1/log2(log2(slots))) * slots);
    
    }

    //return number of slots required for every device to succeed
    return slots;
}




int main() {

    //iteration variables
    int i;
    int j;

    //open 3 files with writing priveleges into file descriptor variables
    FILE *linearFile = fopen("linearLatency.txt", "w");
    FILE *binaryFile = fopen("binaryLatency.txt", "w");
    FILE *logFile = fopen("loglogLatency.txt", "w");


    //simulation loop, increases devices by a factor of 100, up to 6000 devices
    for (i = 100; i <= 6000; i+=100) {

        //initialize latency sum variables
        int linearSum = 0;
        int binarySum = 0;
        int logSum = 0;

        //intialize average latency variables
        int linearAvg;
        int binaryAvg;
        int logAvg;
    
        //loop through 10 trials
        for(j = 0; j < 10; j++) {
            //add latency of each run to sum variable, calling each simulation with i number of devices
            linearSum += linearBackoff(i);
            binarySum += binaryExponentialBackoff(i);
            logSum += loglogBackoff(i);


        }

        //divide each sum by 10 to find average latency
        linearAvg = linearSum / 10;
        binaryAvg = binarySum / 10;
        logAvg = logSum / 10;


        //print each latency to a new line in each file using fprintf
        fprintf(linearFile, "%d\n", linearAvg);
        fprintf(binaryFile, "%d\n", binaryAvg);
        fprintf(logFile, "%d\n", logAvg);


    }


    //close each file
    fclose(linearFile);
    fclose(binaryFile);
    fclose(logFile);


    return 0;
}



