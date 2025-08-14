#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h> // para bool, true, false

bool has_txt_files(const char *pattern);
char *read_input(void);

#endif