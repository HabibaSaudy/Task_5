/*
 * File: Task 2.c
 * Author: Habiba Saudy
 * Description: project for counting down to the launch
 * Date: [13/8/2023]
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions

/* Macros */


/* Function Declarations */
/**
 * @brief counts down from an input number
 * @param start , it is the number to start counting down from
 * @return void
 */
void count_down(int start);


/* Main Function */
int main()
{
    int start ;
    printf("Enter the number to start counting down from: ");   // getting input from the user
    scanf("%d",&start);
    if (start <=0)
    {
        printf("not valid please enter another number: ");       //making sure the number is positive
        scanf("%d",&start);
    }
    count_down(start);          //calling the count_down function
    return 0;
}

/* Function Definitions */
/**
 * @brief counts down from an input number
 * @param start , it is the number to start counting down from
 * @return void
 */
void count_down(int start)
{
    // Function logic
    for ( int i=start; i>0; i--)
    {
        printf("%d\n",i);
    }
    printf("Blast off to the moon!");

     // Example return value
}


