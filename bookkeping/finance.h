#ifndef FINANCE_H
#define FINANCE_H

#include "struct.h"

int get_previous_savings(FILE *file, PreviousSavings *savings, float *previous_balance);
int get_previous_investments(FILE *file, PreviousInvestment *investment); 

#endif