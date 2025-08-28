#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#include "helpers.h"
#include "errors.h"

/**
 * Matches a string against a wildcard pattern
 * '?' (matches any single character)
 * 
 * param pattern The wildcard pattern to match against
 * param str The string to be matched
 * return true if the string matches the pattern, false otherwise
 */

bool match_wildcard(const char *pattern, const char *str)
{
    // Base case: if pattern is exhausted, string must also be exhausted for a match
    if (*pattern == '\0')
        return *str == '\0';
   
    // Handle question mark wildcard - matches exactly one character
    if (*pattern == '?')
    {
        // Question mark cannot match end of string
        if (*str == '\0')
            return false;
       
        // Move both pattern and string forward by one character
        return match_wildcard(pattern + 1, str + 1);
    }
   
    // Handle literal character matching
    if (*str != '\0' && *pattern == *str)
        return match_wildcard(pattern + 1, str + 1);
   
    // No match found
    return false;
}

/**
 * Searches for files in the current directory that match a wildcard pattern
 * Uses the match_wildcard function to compare filenames against the pattern
 * 
 * param pattern The wildcard pattern to search for
 */
int has_files_wildcard(const char *pattern)
{
    DIR *d;
    struct dirent *dir;
    int found = 1;  // int: 1 = not found, 2 = found, ERR_DIC = error
    
    // Open the current directory
    d = opendir(".");
    if (!d)
    {
        return ERR_DIC;  
    }
   
    // Iterate through all directory entries
    while ((dir = readdir(d)) != NULL)
    {
        // Skip current directory ('.') and parent directory ('..') entries
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue;
           
        // Check if current filename matches the wildcard pattern
        if (match_wildcard(pattern, dir->d_name))
        {
            found = 2;  // Set to 2 when match is found
            break; // Exit early once we find a match
        }
    }
    
    // Clean up: close the directory handle
    closedir(d);
    return found;
}

// stores dynamically the input from the user
char *read_input(void)
{
    char *buffer = NULL;
    int size = 0;
    int capacity = 10;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL)
    {
        return NULL;
    }

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (size + 1 >= capacity)
        {
            capacity *= 2;

            char *tmp = realloc(buffer, capacity);
            if (tmp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[size++] = (char)ch;
    }

    buffer[size] = '\0';
    return buffer;
}

// it checks out the input, return true is the input has at least 1 characters, less than size and they all are numbers. false otherwise
bool only_numbers(int *variable, int size)
{
    char *buffer = read_input();
    if (buffer == NULL)
    {
        printf("A memory issue has been detected, we suggest you to stop the program and try again.\n(\"ctrl c\" to stop the program.)\n");
        return false;
    }
    size_t len = strlen(buffer);
    bool result = true;

    if (len > size) // I decided to check the size to ensure that it never overflows the atoi
    {
        printf("For this variable you must write only %d characters and you wrote %zu. Please try again:\n", size, len);
        result = false;
    }
    else if (len < 1) // handles when the user press enter and they wrote nothing
    {
        printf("You must write at least 1 character and you wrote 0. Please try again:\n");
        result = false;
    }
    else
    {
        for (int i = 0; i < len; i++)
        {

            if (!isdigit(buffer[i]))
            {
                printf("You must write only digits and you write \'%s\', please try again:\n", buffer);
                result = false;
                break;
            } 
        }
    }

    if (result)
    {
        *variable = atoi(buffer);
    }

    free(buffer);
    return result;
}

bool check_month(int *variable)
{
    bool result = true;

    if (*variable <= 0)
    {
        printf("You must write a positive integer greater than 0 and you wrote %d, please try again:\n", *variable);
        result = false;
    }
    else if (*variable > 12)
    {
        printf("You must write the number of a month (1-12) and you wrote %d, please try again:\n", *variable);
        result = false;
    }
    
    return result;
}

int get_previous_month(int month)
{
    int previous_month = 0;
    
    if (month == 1)
    {
        previous_month = 12; // if the current month is 1 (january) then I set the previous month to 12 (december)
    }
    else
    {
        previous_month = month - 1;
    }

    return previous_month;
}

int get_previous_year(int year)
{
    int previous_year = 0;

    if (year == 0)
    {
        previous_year = ERR_YEAR;
    }
    else
    {
        previous_year = year - 1;
    }

    return previous_year;
}

int check_choose(char *choose)
{
    int len = strlen(choose);
    if (len > 1)
    {
        return ERR_CHOOSE;
    }

    choose[0] = tolower(choose[0]);

    if (choose[0] != 'y' && choose[0] != 'n')
    {
        return ERR_CHOOSE;
    }
    return 0;
}

char *ask_choose(void) 
{
    char *choose = NULL;

    while (1) 
    {
        printf("(y/n): ");
        choose = read_input();
        if (choose == NULL) 
        {
            memory_error();
            return NULL; // only memory error breaks
        }

        if (check_choose(choose) == ERR_CHOOSE) 
        {
            wrong_chose(choose);
            free(choose);
            continue; // ask again
        }

        return choose; // valid answer
    }
}


