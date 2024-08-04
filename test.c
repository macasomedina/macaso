// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// identifiers
#define FILENAME "backup.bin"
#define TASK_LENGTH 32


// Structs
typedef struct {
    char name[TASK_LENGTH];
    int complete;
} TASK;

// function prototypes
void firstRun();



int main() {
    
    // main variables
    firstRun();

    
    return 0;

} // end main()

void firstRun() {
    FILE* file;
    file = fopen(FILENAME, "rb");
    if (file == NULL) {
        int taskCounter = 0;
        TASK* tasks = { 0 };
        tasks = (TASK*)malloc(1 * sizeof(TASK));
        file = fopen(FILENAME, "wb");
        fwrite(&taskCounter, sizeof(int), 1, file);
        fwrite(tasks, sizeof(TASK), 1, file);
        printf("Backup file created...\n");
        fclose(file);
        free(tasks);
    }
    else {
        printf("Found file...\n");
        fclose(file);
    }
}