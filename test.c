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
void firstRun(int*);
void clearScreen();
int notification(int*);



int main() {
    
    // main variables
    int notificationId = 0;

    // first run
    firstRun(&notificationId);

    clearScreen();
    notification(&notificationId);

    
    return 0;

} // end main()

// directive to clear screen for OS
void clearScreen() {
#ifdef _WIN64
    system("cls"); // 'cls' for Windows 64
#elif __linux__
    system("clear"); // 'clear' for Linux
#endif
} // end clearScreen()


// notifications 
int notification(int* notificationId) {
    if (*notificationId == 1) {
        printf("\n [!] Backup file created...\n");
    }

    if (*notificationId == 2) {
        printf("\n [!] Backup file found...\n");
    }

    *notificationId = 0;

} // end notifications()


void firstRun(int* notificationId) {
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
        *notificationId = 1;
        fclose(file);
        free(tasks);
    }
    else {
        *notificationId = 2;
        fclose(file);
    }
}