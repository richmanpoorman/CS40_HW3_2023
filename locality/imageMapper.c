#include <pnm.h>
#include <a2methods.h>
#include <stdio.h>
#include "cputiming.h"


void imageMapper(Pnm_ppm ppm, A2Methods_mapfun map,
                 void (*transform)(Pnm_ppm, A2Methods_mapfun),
                 FILE *timerFile);

void imageMapper(Pnm_ppm ppm, A2Methods_mapfun map, 
                 void (*transform)(Pnm_ppm, A2Methods_mapfun),
                 FILE *timerFile) 
{
        /* Start the Timer */
        CPUTime_T timer = NULL;
        if (timerFile != NULL) {
                timer = CPUTime_New();
                CPUTime_Start(timer);
        }

        /* Run the operation */
        transform(ppm, map);       

        /* Stop the timer */
        if (timerFile != NULL) {
                double time = CPUTime_Stop(timer);
                CPUTime_Free(&timer);
                double      numPixels = ppm -> width * 
                                        ppm -> height;
                
                fprintf(timerFile, "Total Time: %.0fns\n", time);
                fprintf(timerFile, "Time per pixel: %.0fns/px\n", 
                        time / numPixels);
                fprintf(timerFile, "\n");
        }
}