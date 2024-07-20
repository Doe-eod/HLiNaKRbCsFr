// HLiNaCRbCsFr.h

#ifndef HLiNaKRbCsFr_H
#define HLiNaKRbCsFr_H

#include <stdbool.h>
#include <stdio.h>


extern bool verbose;
extern bool search_in_current_user;
extern bool search_in_local_machine;
extern bool search_in_current_config;

extern const char *char_current_user[];
extern const char *char_local_machine[];
extern const char *char_current_config[];
extern const char *headline_csv[];




// -------------------------------------- DEFINE BOLD --------------------------------------

#define ANSI_BOLD "\033[1m"
#define ANSI_RESET_BOLD "\033[0m"





// -------------------------------------- DEFINE Colors --------------------------------------

// Farbcodes ANSI
#define ANSI_RESET          "\033[0m"
#define ANSI_BLACK          "\033[0;30m"
#define ANSI_RED            "\033[0;31m"
#define ANSI_GREEN          "\033[0;32m"
#define ANSI_YELLOW         "\033[0;33m"
#define ANSI_BLUE           "\033[0;34m"
#define ANSI_MAGENTA        "\033[0;35m"
#define ANSI_CYAN           "\033[0;36m"
#define ANSI_WHITE          "\033[0;37m"

#define ANSI_ORANGE         "\033[0;38;2;255;165;0m"
#define ANSI_DARK_ORANGE    "\033[0;38;2;255;140;0m"
#define ANSI_LIGHT_ORANGE   "\033[0;38;2;255;190;0m"
#define ANSI_GOLD           "\033[0;38;2;255;215;0m"
#define ANSI_TOMATO_RED     "\033[0;38;2;255;69;0m"
#define ANSI_CORAL_RED      "\033[0;38;2;255;99;71m"
#define ANSI_DEEP_PINK      "\033[0;38;2;255;105;180m"
#define ANSI_LIGHT_PINK     "\033[0;38;2;255;182;193m"
#define ANSI_VIOLET         "\033[0;38;2;238;130;238m"
#define ANSI_ORCHID         "\033[0;38;2;218;112;214m"

#define ANSI_LIME           "\033[0;38;2;0;255;0m"
#define ANSI_FOREST_GREEN   "\033[0;38;2;34;139;34m"
#define ANSI_TEAL           "\033[0;38;2;0;128;128m"
#define ANSI_AQUA           "\033[0;38;2;0;255;255m"
#define ANSI_NAVY           "\033[0;38;2;0;0;128m"
#define ANSI_PURPLE         "\033[0;38;2;128;0;128m"
#define ANSI_INDIGO         "\033[0;38;2;75;0;130m"
#define ANSI_MAROON         "\033[0;38;2;128;0;0m"
#define ANSI_SALMON         "\033[0;38;2;250;128;114m"
#define ANSI_SIENNA         "\033[0;38;2;160;82;45m"
#define ANSI_CORNFLOWER     "\033[0;38;2;100;149;237m"
#define ANSI_SKY_BLUE       "\033[0;38;2;135;206;235m"
#define ANSI_MEDIUM_BLUE    "\033[0;38;2;0;0;205m"
#define ANSI_DARK_TURQUOISE "\033[0;38;2;0;206;209m"
#define ANSI_SLATE_BLUE     "\033[0;38;2;106;90;205m"
#define ANSI_ROYAL_BLUE     "\033[0;38;2;65;105;225m"
#define ANSI_MEDIUM_PURPLE  "\033[0;38;2;147;112;219m"
#define ANSI_DARK_OLIVE     "\033[0;38;2;85;107;47m"
#define ANSI_LIGHT_SKY_BLUE "\033[0;38;2;135;206;250m"
#define ANSI_MIDNIGHT_BLUE  "\033[0;38;2;25;25;112m"
#define ANSI_DARK_MAGENTA   "\033[0;38;2;139;0;139m"
#define ANSI_CHOCOLATE      "\033[0;38;2;210;105;30m"
#define ANSI_MEDIUM_SEA_GREEN "\033[0;38;2;60;179;113m"
#define ANSI_SLATE_GRAY     "\033[0;38;2;112;128;144m"
#define ANSI_DIM_GRAY       "\033[0;38;2;105;105;105m"
#define ANSI_LIGHT_SLATE_GRAY "\033[0;38;2;119;136;153m"
#define ANSI_LIGHT_STEEL_BLUE "\033[0;38;2;176;196;222m"
#define ANSI_LIGHT_GRAY     "\033[0;38;2;211;211;211m"
#define ANSI_GAINSBORO      "\033[0;38;2;220;220;220m"






// -------------------------------------- main.c --------------------------------------

int main();






// -------------------------------------- banner.c --------------------------------------

int banner();





// -------------------------------------- help_functions.c --------------------------------------

void clearScreen();
void printWithDelay(const char *str, int delay, const char *color);
void print_csv_header(FILE *csvFile);
void print_csv_header2(FILE *csvFile, const char *headline);
extern void handleExit();


#endif