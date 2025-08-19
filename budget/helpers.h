#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h> // para bool, true, false

bool has_files(const char *pattern);
char *read_input(void);
bool only_numbers(int *variable, int size);
bool check_month(int *variable);

#endif