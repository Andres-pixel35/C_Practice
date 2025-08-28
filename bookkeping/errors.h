#ifndef ERRORS_H
#define ERRORS_H

#define ERR_MEMORY 51
#define ERR_FILE 52
#define ERR_DIC 53
#define ERR_YEAR 54
#define ERR_CHOOSE 55

void dic_not_open(void);
void err_year(void);
void previous_file_not_open(char *previous_file_name, int month, int year);
void file_empty(char *previous_file_name, int month, int year);
void missing_values(char *previous_file_name);
void wrong_chose(char *choose);
void memory_error(void);

#endif