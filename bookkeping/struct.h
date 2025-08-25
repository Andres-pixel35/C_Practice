#ifndef STRUCT_H
#define STRUCT_H

typedef struct PreviousSavings
{
    float previous_total_saving;
    float previous_travels;
    float previous_purchase;
    float previous_emergencies;
}
PreviousSavings;

typedef struct PreviousInvestment
{
    float previous_total_investment;
    float previous_real_estate;
    float previous_currencies;
    float previous_commodities;
    float previous_stocks;
}
PreviousInvestment;

typedef struct Savings
{
    float total_saving;
    float travels;
    float purchase;
    float emergencies;
}
Savings;

typedef struct Investment
{
    float investment;
    float real_estate;
    float currencies;
    float commodities;
    float stocks;
}
Investment;
#endif