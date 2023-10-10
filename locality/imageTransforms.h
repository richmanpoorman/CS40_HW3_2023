#include <pnm.h>
#include <a2methods.h>


#ifndef _IMAGE_TRANSFORMS_H_
#define _IMAGE_TRANSFORMS_H_

/*********************************rotate0************************************
 * Purpose   :
 *      Rotates the image by 0 degrees, using the mapping function
 *      to look at the image
 * Parameter : 
 *      (Pnm_ppm)          ppm : The image to perform a transformation
 *      (A2Methods_mapfun) map : The mapping function to read the image with
 * Returns   : 
 *      (None)
 * Expects   :
 *      The ppm and map function are not NULL, and that the ppm is in the 
 *      valid format with the correct data (aka not a null image)
 * Checks    :  
 *      Checks that the ppm and map are not null
 * Notes     :    
 *      Does nothing, as no rotation is needed to be performed
 ****************************************************************************/
void rotate0(Pnm_ppm ppm, A2Methods_mapfun map);

 /*********************************rotate90***********************************
 * Purpose   :
 *      Rotates the image by 90 degrees clockwise, using the mapping 
 *      function to look at the image
 * Parameter : 
 *      (Pnm_ppm)          ppm : The image to perform a transformation
 *      (A2Methods_mapfun) map : The mapping function to read the image with
 * Returns   : 
 *      (None)
 * Expects   :
 *      The ppm and map function are not NULL, and that the ppm is in the 
 *      valid format with the correct data (aka not a null image)
 * Checks    :  
 *      Checks that the ppm and map are not null
 *      Checks if memory can be allocated to create the new rotated image
 * Notes     :    
 *      Rotates the image in place, so the ppm will be altered
 *      Allocates new memory to rotate the image by copying it into 
 *      a new UArray2, and will update the other values to match
 ****************************************************************************/
void rotate90(Pnm_ppm ppm, A2Methods_mapfun map);

 /*********************************rotate180**********************************
 * Purpose   :
 *      Rotates the image by 180 degrees, using the mapping 
 *      function to look at the image
 * Parameter : 
 *      (Pnm_ppm)          ppm : The image to perform a transformation
 *      (A2Methods_mapfun) map : The mapping function to read the image with
 * Returns   : 
 *      (None)
 * Expects   :
 *      The ppm and map function are not NULL, and that the ppm is in the 
 *      valid format with the correct data (aka not a null image)
 * Checks    :  
 *      Checks that the ppm and map are not null
 *      Checks if memory can be allocated to create the new rotated image
 * Notes     :    
 *      Rotates the image in place, so the ppm will be altered
 *      Allocates new memory to rotate the image by copying it into 
 *      a new UArray2, and will update the other values to match  
 ****************************************************************************/
void rotate180(Pnm_ppm ppm, A2Methods_mapfun map);

 /*********************************rotate270**********************************
 * Purpose   :
 *      Rotates the image by 270 degrees clockwise, using the mapping 
 *      function to look at the image
 * Parameter : 
 *      (Pnm_ppm)          ppm : The image to perform a transformation
 *      (A2Methods_mapfun) map : The mapping function to read the image with
 * Returns   : 
 *      (None)
 * Expects   :
 *      The ppm and map function are not NULL, and that the ppm is in the 
 *      valid format with the correct data (aka not a null image)
 * Checks    :  
 *      Checks that the ppm and map are not null
 *      Checks if memory can be allocated to create the new rotated image
 * Notes     :    
 *      Rotates the image in place, so the ppm will be altered
 *      Allocates new memory to rotate the image by copying it into 
 *      a new UArray2, and will update the other values to match  
 ****************************************************************************/
void rotate270(Pnm_ppm ppm, A2Methods_mapfun map);

 /*****************************flipHorizontal*********************************
 * Purpose   :
 *      Flips the image horizontally (left-to-right)
 * Parameter : 
 *      (Pnm_ppm)          ppm : The image to perform a transformation
 *      (A2Methods_mapfun) map : The mapping function to read the image with
 * Returns   : 
 *      (None)
 * Expects   :
 *      The ppm and map function are not NULL, and that the ppm is in the 
 *      valid format with the correct data (aka not a null image)
 * Checks    :  
 *      Checks that the ppm and map are not null
 *      Checks if memory can be allocated to create the new flipped image
 * Notes     :    
 *      Flips the image in place, so the ppm will be altered
 *      Allocates new memory to flip the image by copying it into 
 *      a new UArray2, and will update the other values to match
 ****************************************************************************/
void flipHorizontal(Pnm_ppm ppm, A2Methods_mapfun map);

 /*****************************flipVertical*********************************
 * Purpose   :
 *      Flips the image vertically (top-to-bottom)
 * Parameter : 
 *      (Pnm_ppm)          ppm : The image to perform a transformation
 *      (A2Methods_mapfun) map : The mapping function to read the image with
 * Returns   : 
 *      (None)
 * Expects   :
 *      The ppm and map function are not NULL, and that the ppm is in the 
 *      valid format with the correct data (aka not a null image)
 * Checks    :  
 *      Checks that the ppm and map are not null
 *      Checks if memory can be allocated to create the new flipped image
 * Notes     :    
 *      Flips the image in place, so the ppm will be altered
 *      Allocates new memory to flip the image by copying it into 
 *      a new UArray2, and will update the other values to match
 ****************************************************************************/
void flipVertical(Pnm_ppm ppm, A2Methods_mapfun map);

 /*********************************transpose**********************************
 * Purpose   :
 *      Transposes the image, making (col, row) -> (row, col)
 * Parameter : 
 *      (Pnm_ppm)          ppm : The image to perform a transformation
 *      (A2Methods_mapfun) map : The mapping function to read the image with
 * Returns   : 
 *      (None)
 * Expects   :
 *      The ppm and map function are not NULL, and that the ppm is in the 
 *      valid format with the correct data (aka not a null image)
 * Checks    :  
 *      Checks that the ppm and map are not null
 *      Checks if memory can be allocated to create the new transposed image
 * Notes     :    
 *      Transposes the image in place, so the ppm will be altered
 *      Allocates new memory to flip the image by copying it into 
 *      a new UArray2, and will update the other values to match
 ****************************************************************************/
void transpose(Pnm_ppm ppm, A2Methods_mapfun map);

#endif