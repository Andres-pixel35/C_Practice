#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_input(void);

int main(void)
{
    printf("Enter text: ");
    char *input = read_input();
    if (input == NULL)
    {
        fprintf(stderr, "Could not allocate memory.\n");
        return 1;
    }

    printf("Your text:\n%s\n", input);
    free(input);
    return 0;
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