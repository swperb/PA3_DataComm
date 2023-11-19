#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>


int linearBackoff(int N) {
    
    int i;
    int j;
    int k;
    int* W;
    int slots = 2;
    int success = 0;
    int selection;
    

    srand(time(NULL));

    while(N > 0) {
        W = (int*)calloc(slots, sizeof(int));

        for (i = 0; i < N; i++) {

            selection = rand() % slots;

            W[selection] += 1;

            // for (j = 0; j < slots; j++) {

            //     if(selection == j) {
            //         W[j] += 1;
            
            //     }

            // } 



        }

        for (k = 0; k < slots; k++) {

            if(W[k] == 1) {
                success++;
            }
        }
    

        N -= success;
        slots += 1;

    }
    return slots;
}

int binaryExponentialBackoff(int N) {

    int i;
    int j;
    int k;
    int* W;
    int slots = 2;
    int success = 0;
    int selection;

    srand(time(NULL));

    while(N > 0) {
        W = (int*)calloc(slots, sizeof(int));

        for (i = 0; i < N; i++) {

            selection = rand() % slots;

            W[selection] += 1;

            // for (j = 0; j < slots; j++) {

            //     if(selection == j) {
            //         W[j] += 1;
            //     }
            // } 

        }  



        for (k = 0; k < slots; k++) {

            if(W[k] == 1) {
                success++;
            }
        }                  

        N -= success;
        slots *= 2;
    }

    return slots;
}

int loglogBackoff(int N) {

    int i;
    int j;
    int k;
    int* W;
    int slots = 4;
    int success = 0;
    int selection;

    srand(time(NULL));

    while(N > 0) {
        W = (int*)calloc(slots, sizeof(int));


        for (i = 0; i < N; i++) {

            selection = rand() % slots;

            W[selection] += 1;

            // for (j = 0; j < slots; j++) {

            //     if(selection == j) {
            //         W[j] += 1;
            //     }
            // }


        }        

        for (k = 0; k < slots; k++) {

            if(W[k] == 1) {
                success++;
            }
        }


        N -= success; 
        slots = floor((1 + 1/log2(log2(slots))) * slots);
    
    }

    return slots;
}


int main() {

    int i;
    int j;

    FILE *linearFile = fopen("linearLatency.txt", "w");
    FILE *binaryFile = fopen("binaryLatency.txt", "w");
    FILE *logFile = fopen("loglogLatency.txt", "w");

    for (i = 100; i <= 6000; i+=100) {
        int linearSum = 0;
        int binarySum = 0;
        int logSum = 0;
        int linearAvg;
        int binaryAvg;
        int logAvg;
    
        for(j = 0; j < 10; j++) {
            linearSum += linearBackoff(i);
            binarySum += binaryExponentialBackoff(i);
            logSum += loglogBackoff(i);


        }

        linearAvg = linearSum / 10;
        binaryAvg = binarySum / 10;
        logAvg = logSum / 10;

        fprintf(linearFile, "%d\n", linearAvg);
        fprintf(binaryFile, "%d\n", binaryAvg);
        fprintf(logFile, "%d\n", logAvg);


    }

    fclose(linearFile);
    fclose(binaryFile);
    fclose(logFile);

    return 0;
}



