/**************************************************************
 *                     timing_test.c
 *
 *     Assignment      : Locality
 *     Authors         : Matthew Wong, Andersen Prince
 *     Date            : 4 October 2023
 *
 *     Program Purpose : 
 *
 *     The program is used to test and measure the execution
 *     duration of a loop, revealing information about the 
 *     program's performance 
 ***************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "cputiming.h"

/*********************************main***************************************
 * Purpose    :            
 *      Measures the execution time of the operations  
 * Parameters : 
 *      (int)        argc      : The amount of command-line arguments
 *      (char)       *argv[]   : An array of command line argument
 * Returns    : 
 *      (int)                  : The exit status
 * Expects    :
 *      None
 ****************************************************************************/

int
main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        int i;
        double sum;
        CPUTime_T timer;
        double time_used; 
        const int outerlooptimes = 8;
        int outerct;
        int innerlimit = 1;

        timer = CPUTime_New();


        for (outerct = 0; outerct < outerlooptimes; outerct++) {
                sum = 0.0;
                CPUTime_Start(timer);
                for (i = 0; i < innerlimit; i++) {
                        sum += i;
                }
                time_used = CPUTime_Stop(timer);
                printf ("Sum %.0f was computed in %.0f nanoseconds\n",
                        sum, time_used);
                innerlimit *= 10;
        }

        CPUTime_Free(&timer);

        return EXIT_SUCCESS;
}
