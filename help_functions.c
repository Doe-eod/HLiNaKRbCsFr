// help_functions.c

#include "HLiNaKRbCsFr.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>




void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void printWithDelay(const char *str, int delay, const char *color) {
    printf("%s", color);

    while (*str) {
        printf("%c", *str);
        fflush(stdout);
        Sleep(delay);
        str++;
    }
    printf("%s", ANSI_RESET);
}



//Write the sections to the file
void print_csv_header(FILE *csvFile) {
    fprintf(csvFile, "SubKey,ValueName,ValueType,ValueData\n");
}

// Write the CSV header to the file
void print_csv_header2(FILE *csvFile, const char *headline) {
    fprintf(csvFile, "\n\n\n%s\n", headline);
}


// Program exit
void handleExit() {
    printf(ANSI_LIGHT_STEEL_BLUE"\n   Servus\n\n"ANSI_RESET);
    exit(0);
}
