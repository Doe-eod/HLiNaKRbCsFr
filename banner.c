// banner.c

#include "HLiNaKRbCsFr.h"
#include <stdio.h>


const char *bannerLines[] = {
    "",
    "         _   _ _     _ _   _       _  ______  _      ____     _____ \n",  
    "        | | | | |   (_) \\ | | __ _| |/ /  _ \\| |__  / ___|___|  ___|___ \n",
    "        | |_| | |   | |  \\| |/ _` | ' /| |_) | '_ \\| |   / __| |_ | '__|\n",
    "        |  _  | |___| | |\\  | (_| | . \\|  _ <| |_) | |___\\__ \\  _|| |\n",
    "        |_| |_|_____|_|_| \\_|\\__,_|_|\\_\\_| \\_\\_.__/ \\____|___/_|  |_|\n",
    "\n",
    "                                        developed by Sven Herz\n",
    "",
    "\n\n\n"
};



int banner() {
    
    int numberOfLines = sizeof(bannerLines) / sizeof(bannerLines[0]);
    for (int i = 0; i < numberOfLines; i++) {
        printWithDelay(bannerLines[i], 0, ANSI_DARK_ORANGE);
    }

    printf("\n\n\n");
    return 0;
}

