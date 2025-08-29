#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "finance.h"
#include "errors.h"
#include "struct.h"
#include "helpers.h"

int get_previous_savings(FILE *file, PreviousSavings *savings, double *previous_balance) 
{
    char line[256];
    double value;
    int total; int travels; int purchase; int emergencies; int final_balance;
    
    // Go back to the beginning of the file.
    rewind(file);
    
    // Read line by line
    while (fgets(line, sizeof(line), file)) 
    {
        // Search "- Savings"
        if (strstr(line, "- Savings") != NULL) {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) // it ignores all characters until it finds '$', when it does it stores the float value at the variable &value
            {
                savings->previous_total_saving = value;
                total = 1;
            }
        }
        // Search "Travels"
        else if (strstr(line, "Travels") != NULL) 
        {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                savings->previous_travels = value;
                travels = 1;
            }
        }
        // Search "Planned purchases"
        else if (strstr(line, "Planned purchases") != NULL) 
        {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                savings->previous_purchase = value;
                purchase = 1;
            }
        }
        // Search "Emergencies"
        else if (strstr(line, "Emergencies") != NULL) 
        {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                savings->previous_emergencies = value;
                emergencies = 1;
            }
        }

        else if (strstr(line, "- Final balance") != NULL) //so, this is not part of previous savings, but it is an information the program need for the
        {                                                 // previous month, and I'm not going to make another function for this value only.
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                *previous_balance = value;
                final_balance = 1;
            }
        }
    }

    // it's neccessary to check that all the values were found because if one of them are missing the program won't work as expected
    if (total != 1 || travels != 1 || purchase != 1 || emergencies != 1 || final_balance != 1) 
    {
        return ERR_FILE;
    }
}

// same function, but I wasn't able to figure out a way to generalize it so here we go
int get_previous_investments(FILE *file, PreviousInvestment *investment) 
{
    char line[256];
    double value;
    int total = 0; int real_estate = 0; int currencies = 0; int commodities = 0; int stocks = 0;
    
    rewind(file);
    
    while (fgets(line, sizeof(line), file)) 
    {
        if (strstr(line, "- Investment") != NULL) {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1)
            {
                investment->previous_total_investment = value;
                total = 1;
            }
        }

        else if (strstr(line, "Real estate") != NULL) 
        {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                investment->previous_real_estate = value;
                real_estate = 1;
            }
        }

        else if (strstr(line, "Currencies") != NULL) 
        {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                investment->previous_currencies = value;
                currencies = 1;
            }
        }

        else if (strstr(line, "Commodities") != NULL) 
        {
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                investment->previous_commodities = value;
                commodities = 1;
            }
        }

        else if (strstr(line, "Stocks") != NULL) 
        {                                                 
            if (sscanf(line, "%*[^$]$%lf", &value) == 1) 
            {
                investment->previous_stocks = value;
                stocks = 1;
            }
        }
    }

    if (total != 1 || real_estate != 1 || currencies != 1 || commodities != 1 || stocks != 1) 
    {
        return ERR_FILE;
    }
}

// it checks whether the input is a number and a float, so it keep track of the dots. It if find more than one dot it continues asking until a valid 
// input in entered.
double get_values_double(int size)
{
    while (1)
    {
        int dots = 0;
        bool valid = true;
        printf("\nYou may enter decimal numbers if you need to.\n");
        printf("How much: ");
        char *buffer = read_input();
        if (buffer == NULL)
        {
            memory_error();
            return ERR_MEMORY;
        }

        size_t len = strlen(buffer);
        if (len > size)
        {
            printf("You can only enter a maximun of %d characters and you entered: %zu. Please try again\n"
                    "(With this amount of money, I don't know why are you here. Thanks though.)\n", size, len);

            free(buffer);
            continue;
        }

        for (int i = 0; i < len; i++)
        {
            if (buffer[i] == '.')
            {
                dots = dots + 1;
                
                if (dots > 1)
                {
                    printf("No decimal number uses more than one dot, expected input: \"??.??\". Input received \"%s\"\nPlease try again.\n", buffer);
                    free(buffer);
                    valid = false;
                    break; // stops the for loop
                }
            }
            else if (!isdigit(buffer[i]))
            {
                printf("You must enter only digits and at maximum one dot, but you entered: \"%s\"\n", buffer);
                free(buffer);
                valid = false; 
                break;
            }
        }
        
        if (!valid)
        {
            continue;
        }
        
        double value = atof(buffer);
        free(buffer);
        return value;
    }
}