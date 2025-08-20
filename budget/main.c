#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "helpers.h"
#include "errors.h"

#define FILE_FOUND 2
#define FILE_NOT_FOUND 1
#define MAX_LEN_MONTH 2
#define MAX_LEN_YEAR 4

int main(void)
{
    printf("=== BEFORE EXECUTING THIS PROGRAM, MAKE SURE YOU HAVE READ THE README FILE.===\n\n");
    bool first_time = true;
    int result = has_files_wildcard("??_????.txt");
    if (result == ERR_DIC)
    {
        fprintf(stderr, "Error: Cannot open current directory\n");
        return ERR_DIC;
    } 
    else if (result == FILE_FOUND)
    {
        first_time = false;
        printf("A file has been found, therefore the program will use the month before the one you add afterwards to make your budget.\n");
    }
    else if (result == FILE_NOT_FOUND)
    {
        first_time = true;
        printf("No file has been found, therefore this program will work assuming this is your first time\n");
    }

    int month = 0;
    int year= 0;
    // a do while to ask for the month until the user writes the required input, aka a positive integer greater than 0 and smaller than 13
    do
    {
        do
        {
            printf("\nMonth (2 digits, e.g; 01-12): ");
        } 
        while (!only_numbers(&month, MAX_LEN_MONTH)); // 2 to ensure than the user writes a small number (1-12)
    }
    while (!check_month(&month)); // ensures that the numbers is, actually, a month and not a random number

    do
    {
        printf("\nYear (4 digits, e.g; 2023): ");
    }
    while(!only_numbers(&year, MAX_LEN_YEAR));

    return 0;
}