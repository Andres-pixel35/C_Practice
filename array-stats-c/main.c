#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int totalSum(int a[], int b);
int highestNumber(int a[], int b);
int lowestNumber(int a[], int b);
int primeNumbers(int a[], int b);
#define MAX_NUMBERS 100 // this program will only allow max 100 differents numbers
int evenNumbers(int a[], int b);
#define MAX_NUMBERS 100 // this program will only alow max 100 differents numbers

int main(void)
{
    int user_input = 0;

    // do-while will ask to the user over and over until they give a positive integer
    do 
    {
        printf("How many numbers would you like to enter? (MAX 100) ");
        if(scanf("%d", &user_input) != 1)
        {
            printf("You must enter a digit\n");
            while ((getchar()) != '\n'); //frees the buffer to avoid odd behavior
            continue;
        }

        if (user_input > MAX_NUMBERS)
        {
            printf("You can only enter a maximum of 100 numbers, please choose another numbers\n");
        }
        else if (user_input <= 0)
        {
            printf("You must enter a positive integer bigger than 0\n");
        }
    }
    while (user_input > MAX_NUMBERS || user_input <= 0);

    int numbers[user_input];

    // here the program will ask to the user n times the number they want to enter, if they enter a char or a string it will ask again until a valid 
    // value is enter
    for (int i = 0; i < user_input; i++)
    {
        bool is_digit;
        do
        {
            is_digit = true;
            printf("Please enter number %d: ", i + 1);
            if(scanf("%d", &numbers[i]) != 1)
            {
                printf("You must enter a digit\n");
                is_digit = false;
                while ((getchar()) != '\n');
                continue;
            }
        } 
        while (is_digit == false);
        
    }
    
    float sum = totalSum(numbers, user_input);
    float average = sum / user_input;
    int highest_number = highestNumber(numbers, user_input);
    int lowest_number = lowestNumber(numbers, user_input);
    int even_numbers = evenNumbers(numbers, user_input);
    int odd_numbers = user_input - even_numbers;

    printf("=== RESULTS ===\nTotal sum: %.0f\nAverage: %.2f\nHighest number: %d\nLowest number: %d\nEven numbers: %d\nOdd numbers: %d\n",
           sum, average, highest_number, lowest_number, even_numbers, odd_numbers);

    return 0;
}

// from here forth int a[] is the array of numbers and int b is the initial input
int totalSum(int a[], int b)
{
    int sum = 0;

    for (int i = 0; i < b; i++)
    {
        sum = sum + a[i];
    }

    return sum;
}

int highestNumber(int a[], int b)
{
    int highest_number = a[0];

    for (int i = 1; i < b; i++)
    {
        if (a[i] > highest_number)
        {
            highest_number = a[i];
        }
    }

    return highest_number;
}

int lowestNumber(int a[], int b)
{
    int lowest_number = a[0];

    for (int i = 1; i < b; i++)
    {
        if (a[i] < lowest_number)
        {
            lowest_number = a[i];
        }
    }

    return lowest_number;
}

int evenNumbers(int a[], int b)
{
    int track = 0;

    for (int i = 0; i < b; i++)
    {
        if (a[i] % 2 == 0)
        {
            track++;
        }
    }
    
    return track;
}
