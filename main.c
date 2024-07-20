// main.c

#include "HLiNaKRbCsFr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


bool verbose = false;
bool search_in_current_user = false;
bool search_in_local_machine = false;
bool search_in_current_config = false;

char tmp[256];
char user_input[256];



const char *headline_csv[] = {
    "HKEY_CURRENT_USER",
    "HKEY_LOCAL_MACHINE",
    "HKEY_CURRENT_CONFIG"
};



const char *char_current_user[] = {
    "AppEvents",
    "Console",
    "Control Panel",
    "Cursors",
    "Environment",
    "EUDC",
    "Keyboard Layout",
    "Microsoft",
    "Network",
    "Printers",
    "Software",
    "System",
    "Uninstall",
    "Volatile Environment"
};

const char *char_local_machine[] = {
    "HARDWARE",
    "SAM",
    "SECURITY",
    "SOFTWARE",
    "SYSTEM",
    "DRIVERS",
    "BCD00000000",
    "WPA",
    "WPAEvents"
};

const char *char_current_config[] = {
    "Software",
    "System",
    "Enum",
    "HARDWARE",
    "Control",
    "Printers",
    "Services",
    "Network",
    "NetTrans",
    "Volatile Environment"
};














// Write the registry value to the CSV file
void print_registry_value(FILE *csvFile, const char *subKey, const char *valueName, DWORD type, const BYTE *data, DWORD dataSize) {
    fprintf(csvFile, "\"%s\",\"%s\",", subKey, valueName);

    switch (type) {
        case REG_SZ:
            fprintf(csvFile, "\"REG_SZ\",\"%s\"\n", (char *)data);
            break;
        case REG_DWORD:
            fprintf(csvFile, "\"REG_DWORD\",\"%u\"\n", *(DWORD *)data);
            break;
        case REG_BINARY:
            fprintf(csvFile, "\"REG_BINARY\",\"0x");
            for (DWORD i = 0; i < dataSize; i++) {
                fprintf(csvFile, "%02x", data[i]);
            }
            fprintf(csvFile, "\"\n");
            break;
        case REG_MULTI_SZ:
            {
                char *p = (char *)data;
                fprintf(csvFile, "\"REG_MULTI_SZ\",\"");
                while (*p) {
                    fprintf(csvFile, "%s ", p);
                    p += strlen(p) + 1;
                }
                fprintf(csvFile, "\"\n");
            }
            break;
        default:
            fprintf(csvFile, "\"Unknown type %u\"\n", type);
            break;
    }
}








// Search the registry for a specific term from the input-csv file
void search_registry(const char *searchTerm, HKEY hKeyRoot, const char *subKey, FILE *csvFile) {
    HKEY hKey;
    if (RegOpenKeyEx(hKeyRoot, subKey, 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) {
        return;
    }

    char valueName[256];
    BYTE data[256];
    DWORD valueNameSize = sizeof(valueName);
    DWORD dataSize = sizeof(data);
    DWORD type, index = 0;

    while (RegEnumValue(hKey, index, valueName, &valueNameSize, NULL, &type, data, &dataSize) == ERROR_SUCCESS) {
        if (strcmp(valueName, searchTerm) == 0) {
            print_registry_value(csvFile, subKey, valueName, type, data, dataSize);
        }
        valueNameSize = sizeof(valueName);
        dataSize = sizeof(data);
        index++;
    }

    char subKeyName[256];
    DWORD subKeyNameSize = sizeof(subKeyName);
    index = 0;

    while (RegEnumKeyEx(hKey, index, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
        char newSubKey[512];
        snprintf(newSubKey, sizeof(newSubKey), "%s\\%s", subKey, subKeyName);
        search_registry(searchTerm, hKeyRoot, newSubKey, csvFile);
        subKeyNameSize = sizeof(subKeyName);
        index++;
    }

    RegCloseKey(hKey);
}








// Read the input CSV file
void read_csv_and_search_registry_without_path(const char *filename) {

    FILE *file = fopen(filename, "r");
    snprintf(tmp, sizeof(tmp), "[*] Start open file: %s\n", filename);
    printWithDelay(tmp, 1, ANSI_DARK_ORANGE);

    if (!file) {
        snprintf(tmp, sizeof(tmp), "[--->] Unable to open file: %s\n\n", filename);
        printWithDelay(tmp, 1, ANSI_RED);
        return;
    }

    const char *txt = "[**] File opened successfully\n\n";
    printWithDelay(txt, 10, ANSI_GREEN);

    FILE *csvFile = fopen("search_result.csv", "w");
    const char *text2 = "[*] Start create file: search_result.csv\n";
    printWithDelay(text2, 1, ANSI_DARK_ORANGE);

    if (!csvFile) {
        snprintf(tmp, sizeof(tmp), "[--->] Unable to create/open file: search_result.csv\n\n");
        printWithDelay(tmp, 1, ANSI_RED);
        fclose(file);
        return;
    }

    const char *tmp = "[**] File created successfully\n\n";
    printWithDelay(tmp, 10, ANSI_GREEN);

    print_csv_header(csvFile);




    char line[256];
    fseek(file, 0, SEEK_SET);
    if (search_in_current_user) {
        const char *textUser1 = "[*] Start search values in HKEY_CURRENT_USER\n";
        printWithDelay(textUser1, 1, ANSI_DARK_ORANGE); 

        print_csv_header2(csvFile, headline_csv[0]);
        const char *text2 = "[**] Searching in HKEY_CURRENT_USER";
        printWithDelay(text2, 1, ANSI_GREEN);

        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = 0;
            printf("\n%s[***] Searching for: %s", ANSI_DEEP_PINK, line, ANSI_RESET);

            for (int i = 0; i < sizeof(char_current_user) / sizeof(char_current_user[0]); i++) {
                if (verbose) {
                    printf("\n%s[--->] Searching in folder: %s%s", ANSI_TEAL, char_current_user[i], ANSI_RESET);
                }
                search_registry(line, HKEY_CURRENT_USER, char_current_user[i], csvFile);
            }
        }
        const char *tmp = "\n[**] Finished search in HKEY_CURRENT_USER\n\n";
        printWithDelay(tmp, 10, ANSI_GREEN);
    }




    char line2[256];
    fseek(file, 0, SEEK_SET);
    if (search_in_local_machine) {
        const char *textMaschine1 = "[*] Start search values in HKEY_LOCAL_MACHINE\n";
        printWithDelay(textMaschine1, 1, ANSI_DARK_ORANGE);

        print_csv_header2(csvFile, headline_csv[1]);
        const char *text2 = "[**] Searching in HKEY_LOCAL_MACHINE";
        printWithDelay(text2, 1, ANSI_GREEN);

        while (fgets(line2, sizeof(line2), file)) {
            line2[strcspn(line2, "\r\n")] = 0;
            printf("\n%s[***] Searching for: %s", ANSI_DEEP_PINK, line2, ANSI_RESET);

            for (int i = 0; i < sizeof(char_local_machine) / sizeof(char_local_machine[0]); i++) {
                if (verbose) {
                    printf("\n%s[--->] Searching in folder: %s%s", ANSI_TEAL, char_local_machine[i], ANSI_RESET);
                }
                search_registry(line2, HKEY_LOCAL_MACHINE, char_local_machine[i], csvFile);
            }
        }
        const char *tmp = "\n[**] Finished search in HKEY_LOCAL_MACHINE\n\n";
        printWithDelay(tmp, 10, ANSI_GREEN);
    }




    char line3[256];
    fseek(file, 0, SEEK_SET);
    if (search_in_current_config) {
        const char *textConfig1 = "[*] Start search values in HKEY_CURRENT_CONFIG\n";
        printWithDelay(textConfig1, 1, ANSI_DARK_ORANGE);

        print_csv_header2(csvFile, headline_csv[2]);
        const char *text2 = "[**] Searching in HKEY_CURRENT_CONFIG";
        printWithDelay(text2, 1, ANSI_GREEN);

        while (fgets(line3, sizeof(line3), file)) {
            line3[strcspn(line3, "\r\n")] = 0;
            printf("\n%s[***] Searching for: %s\n", ANSI_DEEP_PINK, line3, ANSI_RESET);

            for (int i = 0; i < sizeof(char_current_config) / sizeof(char_current_config[0]); i++) {
                if (verbose) {
                    printf("\n%s[--->] Searching in folder: %s%s", ANSI_TEAL, char_current_config[i], ANSI_RESET);
                }
                search_registry(line3, HKEY_CURRENT_CONFIG, char_current_config[i], csvFile);
            }
        }
        const char *tmp = "\n[**] Finished search in HKEY_CURRENT_CONFIG\n\n";
        printWithDelay(tmp, 10, ANSI_GREEN);
    }
}










// Read the input CSV file
void read_csv_and_search_registry_with_path(const char *filename) {
    FILE *file = fopen(filename, "r");
    char tmp[256];

    snprintf(tmp, sizeof(tmp), "[*] Start open file: %s\n", filename);
    printWithDelay(tmp, 1, ANSI_DARK_ORANGE);

    if (!file) {
        snprintf(tmp, sizeof(tmp), "[--->] Unable to open file: %s\n\n", filename);
        printWithDelay(tmp, 1, ANSI_RED);
        return;
    }

    const char *txt = "[**] File opened successfully\n\n";
    printWithDelay(txt, 10, ANSI_GREEN);

    FILE *csvFile = fopen("search_result.csv", "w");
    const char *text2 = "[*] Start create file: search_result.csv\n";
    printWithDelay(text2, 1, ANSI_DARK_ORANGE);

    if (!csvFile) {
        snprintf(tmp, sizeof(tmp), "[--->] Unable to create/open file: search_result.csv\n\n");
        printWithDelay(tmp, 1, ANSI_RED);
        fclose(file);
        return;
    }

    const char *tmp2 = "[**] File created successfully\n\n";
    printWithDelay(tmp2, 10, ANSI_GREEN);

    print_csv_header(csvFile);

    char line[256];

    // Search in HKEY_CURRENT_USER
    if (search_in_current_user) {
        const char *textUser1 = "[*] Start search values in HKEY_CURRENT_USER\n";
        printWithDelay(textUser1, 1, ANSI_DARK_ORANGE);

        print_csv_header2(csvFile, headline_csv[0]);
        const char *text2 = "[**] Searching in HKEY_CURRENT_USER\n";
        printWithDelay(text2, 1, ANSI_GREEN);

        fseek(file, 0, SEEK_SET);
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = 0;
            char *path = strtok(line, ";");
            char *value = strtok(NULL, ";");

            if (path && value) {
                printf("\n%s[***] Searching in path: %s for value: %s%s\n", ANSI_DEEP_PINK, path, value, ANSI_RESET);

                if (verbose) {
                    printf("\n%s[--->] Searching in folder: %s%s\n", ANSI_TEAL, path, ANSI_RESET);
                }
                search_registry(value, HKEY_CURRENT_USER, path, csvFile);
            } else {
                printf("\n%s[--->] Invalid line format: %s%s\n", ANSI_RED, line, ANSI_RESET);
            }
        }

        const char *tmp = "\n[**] Finished search in HKEY_CURRENT_USER\n\n";
        printWithDelay(tmp, 10, ANSI_GREEN);
    }

    // Search in HKEY_LOCAL_MACHINE
    if (search_in_local_machine) {
        const char *textMachine1 = "[*] Start search values in HKEY_LOCAL_MACHINE\n";
        printWithDelay(textMachine1, 1, ANSI_DARK_ORANGE);

        print_csv_header2(csvFile, headline_csv[1]);
        const char *text2 = "[**] Searching in HKEY_LOCAL_MACHINE\n";
        printWithDelay(text2, 1, ANSI_GREEN);

        fseek(file, 0, SEEK_SET);
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = 0;
            char *path = strtok(line, ";");
            char *value = strtok(NULL, ";");

            if (path && value) {
                printf("\n%s[***] Searching in path: %s for value: %s%s\n", ANSI_DEEP_PINK, path, value, ANSI_RESET);

                if (verbose) {
                    printf("\n%s[--->] Searching in folder: %s%s\n", ANSI_TEAL, path, ANSI_RESET);
                }
                search_registry(value, HKEY_LOCAL_MACHINE, path, csvFile);
            } else {
                printf("\n%s[--->] Invalid line format: %s%s\n", ANSI_RED, line, ANSI_RESET);
            }
        }

        const char *tmp = "\n[**] Finished search in HKEY_LOCAL_MACHINE\n\n";
        printWithDelay(tmp, 10, ANSI_GREEN);
    }

    // Search in HKEY_CURRENT_CONFIG
    if (search_in_current_config) {
        const char *textConfig1 = "[*] Start search values in HKEY_CURRENT_CONFIG\n";
        printWithDelay(textConfig1, 1, ANSI_DARK_ORANGE);

        print_csv_header2(csvFile, headline_csv[2]);
        const char *text2 = "[**] Searching in HKEY_CURRENT_CONFIG\n";
        printWithDelay(text2, 1, ANSI_GREEN);

        fseek(file, 0, SEEK_SET);
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = 0;
            char *path = strtok(line, ";");
            char *value = strtok(NULL, ";");

            if (path && value) {
                printf("\n%s[***] Searching in path: %s for value: %s%s\n", ANSI_DEEP_PINK, path, value, ANSI_RESET);

                if (verbose) {
                    printf("\n%s[--->] Searching in folder: %s%s\n", ANSI_TEAL, path, ANSI_RESET);
                }
                search_registry(value, HKEY_CURRENT_CONFIG, path, csvFile);
            } else {
                printf("\n%s[--->] Invalid line format: %s%s\n", ANSI_RED, line, ANSI_RESET);
            }
        }

        const char *tmp = "\n[**] Finished search in HKEY_CURRENT_CONFIG\n\n";
        printWithDelay(tmp, 10, ANSI_GREEN);
    }

    fclose(file);
    fclose(csvFile);
}
















int main(int argc, char *argv[]) {
    printf("\n");
    clearScreen();
    banner();

    // Check settings
    if (argc <= 1) {
        const char *text = "\nSyntax: .\\HLiNaKRbCsFr.exe <options>\n\nOptions\n---------------------\n-h (show help)\n-v (verbose mode)\n-a (search in all HKEYs)\n-u (search in HKEY_CURRENT_USER)\n-m (search in HKEY_LOCAL_MACHINE)\n-c (search in HKEY_CURRENT_CONFIG)\n";
        printWithDelay(text, 10, ANSI_TEAL);
        printf("\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            search_in_current_user = true;
            search_in_local_machine = true;
            search_in_current_config = true;

        } else if (strcmp(argv[i], "-u") == 0) {
            search_in_current_user = true;

        } else if (strcmp(argv[i], "-m") == 0) {
            search_in_local_machine = true;

        } else if (strcmp(argv[i], "-c") == 0) {
            search_in_current_config = true;

        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = true;

        } else if (strcmp(argv[i], "-h") == 0) {
            const char *text = "\nSyntax: .\\HLiNaKRbCsFr.exe <options>\n\nOptions\n---------------------\n-h (show help)\n-v (verbose mode)\n-a (search in all HKEYs)\n-u (search in HKEY_CURRENT_USER)\n-m (search in HKEY_LOCAL_MACHINE)\n-c (search in HKEY_CURRENT_CONFIG)\n";
            printWithDelay(text, 10, ANSI_TEAL);
            printf("\n");
            return 1;
        } else {
            snprintf(tmp, sizeof(tmp), "Sorry but [%s] is not a valid option!\n", argv[i]);
            printWithDelay(tmp, 10, ANSI_RED);
            const char *text = "\nSyntax: .\\HLiNaKRbCsFr.exe <options>\n\nOptions\n---------------------\n-h (show help)\n-v (verbose mode)\n-a (search in all HKEYs)\n-u (search in HKEY_CURRENT_USER)\n-m (search in HKEY_LOCAL_MACHINE)\n-c (search in HKEY_CURRENT_CONFIG)\n";
            printWithDelay(text, 10, ANSI_TEAL);
            printf("\n");
            return 1;
        }
    }


    // Show selected options
    if (verbose) {
        const char *verbose = "[X] Verbose mode is enabled";
        printWithDelay(verbose, 10, ANSI_GREEN);
        printf("\n");
    } else {
        const char *verbose = "[-] Verbose mode is disabled";
        printWithDelay(verbose, 10, ANSI_RED);
        printf("\n");
    } if (search_in_current_user) {
        const char *c_user = "[X] Searching in HKEY_CURRENT_USER";
        printWithDelay(c_user, 10, ANSI_GREEN);
        printf("\n");
    } else {
        const char *c_user = "[-] Do not searching in HKEY_CURRENT_USER";
        printWithDelay(c_user, 10, ANSI_RED);
        printf("\n");
    } if (search_in_local_machine) {
        const char *l_maschine = "[X] Searching in HKEY_LOCAL_MACHINE";
        printWithDelay(l_maschine, 10, ANSI_GREEN);
        printf("\n");
    } else {
        const char *l_maschine = "[-] Do not searching in HKEY_LOCAL_MACHINE";
        printWithDelay(l_maschine, 10, ANSI_RED);
        printf("\n");
    } if (search_in_current_config) {
        const char *c_config = "[X] Searching in HKEY_CURRENT_CONFIG";
        printWithDelay(c_config, 10, ANSI_GREEN);
        printf("\n\n");
    } else {
        const char *c_config = "[-] Do not searching in HKEY_CURRENT_CONFIG";
        printWithDelay(c_config, 10, ANSI_RED);
        printf("\n\n");
    }



    const char *user_input1 = "[*] How should the registry be searched?\n\n";
    printWithDelay(user_input1, 10, ANSI_DARK_ORANGE);

    const char *user_input2 = "[1] Search only for values without taking paths into account (hit list can be long)\n[--->] The values are read from the first column of the inputfile.csv file.\n\n";
    printWithDelay(user_input2, 10, ANSI_TEAL);

    const char *user_input4 = "[2] Consider values and paths in the search (exact matches only)\n[--->] The paths are taken from the first column and the values from the second.\n\n";
    printWithDelay(user_input4, 10, ANSI_TEAL);

    const char *user_input5 = "[q] Exit\n\n";
    printWithDelay(user_input5, 10, ANSI_TEAL);

    const char *user_input6 = "[*] Enter the option:\n[--->] ";
    printWithDelay(user_input6, 10, ANSI_DARK_ORANGE);


    scanf("%s", user_input);

    printf("\n\n");


    if (user_input[0] == 'q') {
        handleExit();
    } 

    if (user_input[0] == '1') {
        read_csv_and_search_registry_without_path("inputfile.csv");
    } else if (user_input[0] == '2') {
        read_csv_and_search_registry_with_path("inputfile.csv");
    } else {
        const char *text = "Sorry but this is not a valid option!\n";
        printWithDelay(text, 10, ANSI_RED);
        printf("\n");
        return 1;
    }

    printf("\n\n");
    return 0;
}
