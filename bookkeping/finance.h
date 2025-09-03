#ifndef FINANCE_H
#define FINANCE_H

#include "struct.h"

int get_previous_savings(FILE *file, PreviousSavings *savings, double *previous_balance);
int get_previous_investments(FILE *file, PreviousInvestment *investment); 
double get_values_double(size_t size);
void build_file_name(char *file_name, size_t size ,int month, int year);
void build_personal_report(char *file_name, size_t size, int month, int year);
double update_savings(const char *message, double *value, double *total_value ,size_t size);
void print_savings(const PreviousSavings *ps);

#endif