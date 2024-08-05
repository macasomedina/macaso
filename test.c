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
void format(char*);

int main() {
    
    // main variables
    int notificationId = 0;
    int taskCounter = 0;
    TASK* tasks;
    FILE* file;

    // first run
    firstRun(&notificationId);

    clearScreen();
    notification(&notificationId);

    TASK tempTask;
    char tempDescription[TASK_LENGTH];
    printf("Enter task: ");
    fgets(tempDescription, TASK_LENGTH, stdin);
    format(tempDescription);
    strcpy(tempTask.name, tempDescription);
    tempTask.complete = 0;

    file = fopen(FILENAME, "rb");

    if (file == NULL) {
        printf("Could not open file");
    }

    fread(&taskCounter, sizeof(int), 1, file);
    tasks = (TASK *)calloc(taskCounter + 1, sizeof(TASK));
    fread(tasks, sizeof(TASK), taskCounter, file);
    fclose(file);

    strcpy(tasks[taskCounter].name, tempTask.name);
    tasks[taskCounter].complete = tempTask.complete;
    taskCounter++;

    file = fopen(FILENAME, "wb");

    if (file == NULL) {
        printf("Could not open file");
    }

    fwrite(&taskCounter, sizeof(int), 1, file);
    fwrite(tasks, sizeof(TASK), taskCounter, file);

    for (int i = 0; i < taskCounter; i++) {
        printf("%s (%s)\n", tasks[i].name, tasks[i].complete == 0 ? "Pending" : "Complete");
    }


    free(tasks);    
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

// format string sentence case and extra spaces
void format(char* string) {
    int i, j;
    int counter = strlen(string);
    string[counter - 1] = '\0';
    for (i = 0; i < counter; i++) {
        if (i == 0) {
            string[i] = toupper(string[i]); // uppercase first character
        }
        else if (isspace(string[i - 1])) {
            string[i] = toupper(string[i]); // uppercase first letter character
        }
        else if (string[i] == ' ') {
            while (string[i + 1] == ' ') {
                for (j = i; j < counter; j++) {
                    string[j] = string[j + 1]; // Shift characters to the left
                }
                counter--;
            }
        }
        else {
            string[i] = tolower(string[i]); // lowercase rest of word
        }
    }

} // end format()
