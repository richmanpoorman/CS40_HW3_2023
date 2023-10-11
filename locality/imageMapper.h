/**************************************************************
 *                     imageMapper.h
 *
 *     Assignment      : Locality
 *     Authors         : Matthew Wong, Andersen Prince
 *     Date            : 3 October 2023
 *
 *     Program Purpose : 
 * 
 *     Specify the interface for a function called imageMapper
 *     that takes an image, performs transformations, measure 
 *     the timing of it.
 ***************************************************************/
#include <pnm.h>
#include <a2methods.h>
#include <stdio.h>

#ifndef _IMAGE_MAPPER_H_
#define _IMAGE_MAPPER_H_
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

#endif