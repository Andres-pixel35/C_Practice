#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h> // for bool, true, false

#include "helpers.h"

// checks if in the current directory has files with the extension pattern
bool has_files(const char *pattern) 
{
    DIR *d;
    struct dirent *dir;
    bool found = false;

    d = opendir(".");
    if (!d) 
    {
        perror("opendir");
        return false;
    }

    while ((dir = readdir(d)) != NULL) 
    {
        // Check if filename ends with the pattern
        size_t len_name = strlen(dir->d_name);
        size_t len_pat  = strlen(pattern);

        if (len_name >= len_pat &&
            strcmp(dir->d_name + len_name - len_pat, pattern) == 0) 
        {
            found = true;
            break; // stop after finding first match
        }
    }

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

// it checks out the input, return true is the input has at least two characters and they are numbers. false otherwise
bool only_numbers(int *variable, int size)
{
    char *buffer = read_input();
    size_t len = strlen(buffer);
    if (len > size) // I decided to check the size to ensure that it never overflow the atoi
    {
        printf("For this variable you must write only %d characters and you wrote %zu. Please try again:\n", size, len);
        return false;
    }
    else if (len < 1) // handles when the user press enter and they wrote nothing
    {
        printf("You must write at least 1 character and you wrote %zu. Please try again:\n", len);
        return false;
    }

    for (int i = 0; i < size; i++)
    {
        if (!isdigit(buffer[i]))
        {
            printf("You must write only digits and you write \'%s\', please try again:\n", buffer);
            return false;
        } 
    }

    *variable = atoi(buffer);
    return true;
}

// since I don´t really need to check the year, I decided to just check the month. Due to the year could be handle only
// with the previous function
bool check_month(int *variable)
{
    if (*variable <= 0)
    {
        printf("You must write a positive integer greater than 0 and you wrote %d, please try again:\n", *variable);
        return false;
    }
    else if (*variable > 12)
    {
        printf("You must write the number of a month (1-12) and you wrote '%d, please try again:\n", *variable);
        return false;
    }
    
    return true;
}
