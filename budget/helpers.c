#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h> // for bool, true, false

bool has_txt_files(const char *pattern) 
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
        // Check if filename ends with the pattern (e.g., ".txt")
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

char *read_input(void)
{
    char *buffer = NULL;
    int size = 0;
    int capacity = 10;
    char ch;

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