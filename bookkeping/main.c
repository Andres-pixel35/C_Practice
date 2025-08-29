#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "helpers.h"
#include "struct.h"
#include "errors.h"
#include "finance.h"

#define FILE_FOUND 2
#define FILE_NOT_FOUND 1
#define MAX_LEN_MONTH 2 // this is the check the length of the input, if it has more than 2 characters it's obviously not a month
#define MAX_LEN_YEAR 4 // here the same, and it also works to avoid and overflow with atoi in helpers.c
#define SIZE_FILE_NAME 12 // so, 12 characters due to the restrictions for the name 'MM_YYYY.txt' + '\0' = 12
#define FIRST_MONTH 1 // i need to check if the current month is 12, if so then I have to set it to 12 and reduce the year by 1
#define MAX_LEN_DOUBLE 15 // if you realy have this amount of money, I don't know what are you doing here

int main(void)
{
    printf("=== BEFORE EXECUTING THIS PROGRAM, MAKE SURE YOU HAVE READ THE README FILE.===\n\n");
    //here i will define several local functions for main
    bool first_time = true;
    int month = 0;
    int year= 0;
    double previous_balance = 0;
    double new_balance = 0;
    double income = 0; 
    PreviousInvestment previous_investment = {0};
    PreviousSavings previous_savings = {0};
    Investment new_investment = {0};
    Savings new_savings = {0};
    
    int result = has_files_wildcard("??_????.txt");
    if (result == ERR_DIC)
    {
        dic_not_open();
        return ERR_DIC;
    } 
    else if (result == FILE_FOUND)
    {
        first_time = false;
        printf("A file has been found, therefore the program will use the month before the one you add afterwards to make your bookkeping.\n");
    }
    else if (result == FILE_NOT_FOUND)
    {
        first_time = true;
        printf("No file has been found, therefore this program will work assuming this is your first time\n");
    }

    // a do while to ask for the month until the user writes the required input, aka a positive integer greater than 0 and smaller than 13
    do
    {
        do
        {
            printf("\nMonth (2 digits, e.g; 01-12): ");
        } 
        while (!only_numbers(&month, MAX_LEN_MONTH));
    }
    while (!check_month(&month));

    do
    {
        printf("\nYear (4 digits, e.g; 2023): ");
    }
    while(!only_numbers(&year, MAX_LEN_YEAR));

    // The program will only search for the information in the previous month if it exists, aka it's there at least one file that fulfil the requirements
    if (!first_time)
    {
        int previous_month = get_previous_month(month);
        int previous_year = year;
        char previous_file_name[SIZE_FILE_NAME];

        if (month == FIRST_MONTH) // if the user enters january, then the year is set to the previous year
        {
            previous_year = get_previous_year(year);
            if (previous_year == ERR_YEAR)
            {
                // except if the current year is 0000, the program won't work with years Before the Common Era
                err_year();
                return ERR_YEAR;
            }
        }

        snprintf(previous_file_name, sizeof(previous_file_name), "%02d_%04d.txt", previous_month, previous_year); 

        FILE *previous_bookkeping = fopen(previous_file_name, "r");
        if (!previous_bookkeping)
        {
            previous_file_not_open(previous_file_name, month, year);
            return ERR_FILE;
        }

        bool is_empty = (fgetc(previous_bookkeping) == EOF);

        if (is_empty)
        {
            file_empty(previous_file_name, month, year);
            return ERR_FILE;
        }

        int is_modified = get_previous_savings(previous_bookkeping, &previous_savings, &previous_balance);

        if (is_modified == ERR_FILE) // if get previous savings does not find one value, it returns ERR_FILE and stops the program since it can't continue
        {                            // if those values are missing
            missing_values(previous_file_name);
            return ERR_FILE;
        }

        is_modified = get_previous_investments(previous_bookkeping, &previous_investment);

        if (is_modified == ERR_FILE)
        {                            
            missing_values(previous_file_name);
            return ERR_FILE;
        }
    
        fclose(previous_bookkeping);
    }
    else
    {
        printf("\n=== Welcome to the interface for new users ===\nDo you have any previous balance that you would like to add?\n"
                "Remeber that is money besides savings and investments and it's from the previous month ");
        char *choose = ask_choose();
        if (choose == NULL)
        {
            return ERR_MEMORY;
        }

        switch (choose[0])
        {
            case 'y':
                previous_balance = get_values_double(MAX_LEN_DOUBLE);
                if (previous_balance == ERR_MEMORY)
                {
                    free(choose);
                    memory_error();
                    return ERR_MEMORY;
                }
                break;
            
            case 'n':
                break;
        }
        free(choose);

        printf("\nNice, now, do you have any previous savings that you would like to add?\n"
                "Remember, savings not including what you've added this month: ");
        choose = ask_choose();
        if (choose == NULL)
        {
            return ERR_MEMORY;
        }

        switch (choose[0])
        {
        case 'y':
            printf("\nIf you have nothing in any of the following items you may enter \"0\" or just press \"enter\".\n");
            printf("\n=== Savings for future travels ===\n");
            previous_savings.previous_travels = get_values_double(MAX_LEN_DOUBLE);
            if (previous_savings.previous_travels == ERR_MEMORY)
            {
                free(choose);
                return ERR_MEMORY;
            }

            printf("\n=== Savings for future purchases ===\n");
            previous_savings.previous_purchase = get_values_double(MAX_LEN_DOUBLE);
            if (previous_savings.previous_purchase == ERR_MEMORY)
            {
                free(choose);
                return ERR_MEMORY;
            }

            printf("\n=== Savings for emergencies ===\n");
            previous_savings.previous_emergencies = get_values_double(MAX_LEN_DOUBLE);
            if (previous_savings.previous_emergencies == ERR_MEMORY)
            {
                free(choose);
                return ERR_MEMORY;
            }

            previous_savings.previous_total_saving = previous_savings.previous_travels + previous_savings.previous_purchase + previous_savings.previous_emergencies;
            break;
        
        case 'n':
            break;
       } 
       free(choose);
    }
    return 0;
}