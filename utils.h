#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
static inline void clearBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
static inline void pauseScreen()
{
    printf("\nPress any key to continue...");
    getch();
}
#endif