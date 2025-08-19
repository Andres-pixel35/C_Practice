#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "helpers.h"
#include "errors.h"

int main(void)
{
    bool first_time = true;
    first_time = has_files(".txt"); 

    // a do while to ask for the month until the user writes the required input, aka a positive integer greater than 0 and smaller than 13
    int month = 0;
    do
    {
        do
        {
            printf("Month: ");
        } 
        while (!only_numbers(&month, 2)); // 2 to ensure than the user writes a small number (1-12)
    }
    while (!check_month(&month)); // ensures than the numbers is, actually, a month and not a random number

    printf("%d\n", month);

    return 0;

}