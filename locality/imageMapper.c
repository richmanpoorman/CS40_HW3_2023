/**************************************************************
 *                     imageMapper.c
 *
 *     Assignment      : Locality
 *     Authors         : Matthew Wong, Andersen Prince
 *     Date            : 3 October 2023
 *
 *     Program Purpose : 
 *     
 *     Specifies a function called imageMapper that performs
 *     image transformations while measuring the timing of the 
 *     transformation.     
 ***************************************************************/

#include <pnm.h>
#include <a2methods.h>
#include <stdio.h>
#include "cputiming.h"

/*********************************imageMapper*********************************
 * Purpose    :
 *      Takes the image and performs a transformation, measuring 
 *      the timing of the transformation as well
 * Parameters :    
 *      (Pnm_ppm)          ppm       : The image to transform
 *      (A2Methods_mapfun) map       : The mapping function that allows us 
 *                                     to read the image
 *      (function)         transform : The transformation that will be done
 *                                     onto the image
 *      (FILE *)           timerFile : The file to record the total 
 *                                     timing and the time taken per pixel
 * Returns    : 
 *      (None) 
 * Expects    : 
 *      Expects the ppm to be a valid image, with the correctly set variables 
 *      inside, as well as the map function and transform function to be valid. 
 *      The timerFile is expected to be NULL if the file is not to be written 
 *      to, and we are assuming the file is already opened to be written to. 
 *      The transform function is as follows:
 *              
 *      void transform(Pnm_ppm ppm, A2Methdods_mapfun map);             
 * 
 * Checks     : 
 *      Checks that map, ppm, and transform are not NULL.
 *      Checks also if it can't allocate the correct amount of 
 *      memory in order to change the values
 * Notes      : 
 *      Changes the ppm in place, and also times the transformation if possible
 ****************************************************************************/
void imageMapper(Pnm_ppm ppm, A2Methods_mapfun map,
                 void (*transform)(Pnm_ppm, A2Methods_mapfun),
                 FILE *timerFile);

/* Implementation */
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