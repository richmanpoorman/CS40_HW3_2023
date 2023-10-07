#include <pnm.h>
#include <a2methods.h>
#include <stdbool.h>
#include "assert.h"

/* 
 *  TRANSFORMATION FUNCTIONS
 */
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


/* 
 *  LOCATION MAPPER FUNCTIONS
 */
 /*************************locationMapRotate90*****************************
 * Purpose   :
 *      Finds the location of the pixel in the new image after applying
 *      a 90 degree rotation clockwise, so it finds 
 *      (start col, start row) -> (end col, end row)
 * Parameter : 
 *      (int)   col    : The starting column of the pixel
 *      (int)   row    : The starting row of the pixel
 *      (int)   width  : The width of the image
 *      (int)   height : The height of the image
 *      (int *) newCol : The reference pointer to the column of the pixel 
 *                       after transforming
 *      (int *) newRow : The reference pointer to the row of the pixel 
 *                       after transforming
 * Returns   : 
 *      (None)
 * Expects   :
 *      The column and row to be valid (it doesn't check)
 *      The write locations of (newCol, newRow) are not null (it doesn't check)
 * Checks    :  
 *      (None)
 * Notes     :
 *      It is used as a helper function to make it easy to generalize,
 *      so it should not be used outside of using it for mapToNewImage.
 *      It writes the output through the reference of newCol and newRow
 ****************************************************************************/
void locationMapRotate90(int col, int row, int width, int height, 
                         int *newCol, int *newRow);

/*************************locationMapRotate180*****************************
 * Purpose   :
 *      Finds the location of the pixel in the new image after applying
 *      a 180 degree rotation, so it finds 
 *      (start col, start row) -> (end col, end row)
 * Parameter : 
 *      (int)   col    : The starting column of the pixel
 *      (int)   row    : The starting row of the pixel
 *      (int)   width  : The width of the image
 *      (int)   height : The height of the image
 *      (int *) newCol : The reference pointer to the column of the pixel 
 *                       after transforming
 *      (int *) newRow : The reference pointer to the row of the pixel 
 *                       after transforming
 * Returns   : 
 *      (None)
 * Expects   :
 *      The column and row to be valid (it doesn't check)
 *      The write locations of (newCol, newRow) are not null (it doesn't check)
 * Checks    :  
 *      (None)
 * Notes     :
 *      It is used as a helper function to make it easy to generalize,
 *      so it should not be used outside of using it for mapToNewImage.
 *      It writes the output through the reference of newCol and newRow
 ****************************************************************************/
void locationMapRotate180(int col, int row, int width, int height, 
                         int *newCol, int *newRow);

/*************************locationMapRotate270*****************************
 * Purpose   :
 *      Finds the location of the pixel in the new image after applying
 *      a 270 degree rotation clockwise, so it finds 
 *      (start col, start row) -> (end col, end row)
 * Parameter : 
 *      (int)   col    : The starting column of the pixel
 *      (int)   row    : The starting row of the pixel
 *      (int)   width  : The width of the image
 *      (int)   height : The height of the image
 *      (int *) newCol : The reference pointer to the column of the pixel 
 *                       after transforming
 *      (int *) newRow : The reference pointer to the row of the pixel 
 *                       after transforming
 * Returns   : 
 *      (None)
 * Expects   :
 *      The column and row to be valid (it doesn't check)
 *      The write locations of (newCol, newRow) are not null (it doesn't check)
 * Checks    :  
 *      (None)
 * Notes     :
 *      It is used as a helper function to make it easy to generalize,
 *      so it should not be used outside of using it for mapToNewImage.
 *      It writes the output through the reference of newCol and newRow
 ****************************************************************************/
void locationMapRotate270(int col, int row, int width, int height, 
                          int *newCol, int *newRow);

/*************************locationMapFlipHorizontal***************************
 * Purpose   :
 *      Finds the location of the pixel in the new image after applying
 *      a flip horizontally, so it finds 
 *      (start col, start row) -> (end col, end row)
 * Parameter : 
 *      (int)   col    : The starting column of the pixel
 *      (int)   row    : The starting row of the pixel
 *      (int)   width  : The width of the image
 *      (int)   height : The height of the image
 *      (int *) newCol : The reference pointer to the column of the pixel 
 *                       after transforming
 *      (int *) newRow : The reference pointer to the row of the pixel 
 *                       after transforming
 * Returns   : 
 *      (None)
 * Expects   :
 *      The column and row to be valid (it doesn't check)
 *      The write locations of (newCol, newRow) are not null (it doesn't check)
 * Checks    :  
 *      (None)
 * Notes     :
 *      It is used as a helper function to make it easy to generalize,
 *      so it should not be used outside of using it for mapToNewImage.
 *      It writes the output through the reference of newCol and newRow
 ****************************************************************************/
void locationMapFlipHorizontal(int col, int row, int width, int height, 
                               int *newCol, int *newRow);

/*************************locationMapFlipVertical***************************
 * Purpose   :
 *      Finds the location of the pixel in the new image after applying
 *      a flip vertically, so it finds 
 *      (start col, start row) -> (end col, end row)
 * Parameter : 
 *      (int)   col    : The starting column of the pixel
 *      (int)   row    : The starting row of the pixel
 *      (int)   width  : The width of the image
 *      (int)   height : The height of the image
 *      (int *) newCol : The reference pointer to the column of the pixel 
 *                       after transforming
 *      (int *) newRow : The reference pointer to the row of the pixel 
 *                       after transforming
 * Returns   : 
 *      (None)
 * Expects   :
 *      The column and row to be valid (it doesn't check)
 *      The write locations of (newCol, newRow) are not null (it doesn't check)
 * Checks    :  
 *      (None)
 * Notes     :
 *      It is used as a helper function to make it easy to generalize,
 *      so it should not be used outside of using it for mapToNewImage.
 *      It writes the output through the reference of newCol and newRow
 ****************************************************************************/
void locationMapFlipVertical(int col, int row, int width, int height, 
                             int *newCol, int *newRow);

/*************************locationMapFlipHorizontal***************************
 * Purpose   :
 *      Finds the location of the pixel in the new image after applying
 *      a transpose, so it finds 
 *      (start col, start row) -> (end col, end row)
 * Parameter : 
 *      (int)   col    : The starting column of the pixel
 *      (int)   row    : The starting row of the pixel
 *      (int)   width  : The width of the image
 *      (int)   height : The height of the image
 *      (int *) newCol : The reference pointer to the column of the pixel 
 *                       after transforming
 *      (int *) newRow : The reference pointer to the row of the pixel 
 *                       after transforming
 * Returns   : 
 *      (None)
 * Expects   :
 *      The column and row to be valid (it doesn't check)
 *      The write locations of (newCol, newRow) are not null (it doesn't check)
 * Checks    :  
 *      (None)
 * Notes     :
 *      It is used as a helper function to make it easy to generalize,
 *      so it should not be used outside of using it for mapToNewImage.
 *      It writes the output through the reference of newCol and newRow
 ****************************************************************************/
void locationMapTranspose(int col, int row, int width, int height, 
                          int *newCol, int *newRow);

/* 
 *  MAP TO IMAGE FUNCTIONS
 */
 /****************************mapToNewImage********************************
 * Purpose   :
 *      Opens up the ppm and makes a new UArray2 to hold the data,
 *      and does the transformation by creating a copy in the correct
 *      dimensions, then uses a function to send the points from 
 *      the current image to the new image (aka function that takes
 *      a point before transformation and returns a point after transformation)
 * Parameter : 
 *      (Pnm_ppm)          ppm                 : The image to transform
 *      (A2Methods_mapfun) map                 : The mapping function to read
 *                                               the UArray2
 *      (function)         locationMap         : The function which maps
 *                                               points to the location
 *                                               in the transformed array
 *      (bool)             isFlippedDimensions : Whether or not the image
 *                                               has width and height flipped
 * Returns   : 
 *      (None)
 * Expects   : 
 *      The ppm to be a valid ppm. Expects that ppm, map, and locationMap are
 *      not null. 
 * Checks    :  
 *      Checks if ppm, map, and loationMap are null, 
 *      The free and new are assumed to throw a CRE if invalid
 *      Checks if the methods and images are null
 * Notes     :    
 *      Only used for transformations that don't change dimensions, but 
 *      either keep the same dimensions (flips + 180 rotation) or 
 *      swap dimensions (transpose + 90/270 rotation).
 *      Creates a new UArray2 and copies the data to the proper location.
 *      Does not check if the functions inside the Pnm_ppm methods are null
 ****************************************************************************/
void mapToNewImage(Pnm_ppm ppm, A2Methods_mapfun map, 
                   void (*locationMap)(int, int, int, int, int *, int *),
                   bool isFlippedDimensions);

 /****************************mapToNewApplyFunction***************************
 * Purpose   :
 *      The mapping function to be used in the UArray2 on each element in 
 *      order to map them into the new UArray2, which takes each element and 
 *      uses the locationMap function passed into cl to find the location
 *      to put the element in; fits the contract for the A2Methods_applyfun
 * Parameter : 
 *      (int)                col    : The column of the current pixel
 *      (int)                row    : The row of the current pixel
 *      (A2Methods_UArray2)  array2 : The A2UArray2 where the pixels are stored
 *      (A2Methods_Object *) ptr    : The pointer to the current element
 *      (void *)             cl     : Passed a struct that contains:
 *                                    - The function which gives the 
 *                                      location in the new array
 *                                    - The new image to write to
 *                                    - The methods to write the new image
 * Returns   : 
 *      (None)
 * Expects   :
 *      To only be used as a mapping function
 * Checks    :  
 *      None; assumes the inputs to be valid
 * Notes     :    
 *      Only used with the mapping functions
 *      Writes to the new image
 ****************************************************************************/
void mapToNewApplyFunction(int col, int row, A2Methods_UArray2 array2, 
                           A2Methods_Object *ptr, void *cl);

 /******************************setVariables********************************
 * Purpose   :
 *      Sets the variables of the image to match the new image
 * Parameter : 
 *      (Pnm_ppm)           ppm      : The image to change the values of 
 *      (A2Methods_UArray2) newImage : The new image to compare with
 *      (A2Methods_T)       methods  : The methods that contain the functions
 *                                     to get the width and height of the 
 *                                     new image
 * Returns   : 
 *      (None)
 * Expects   :
 *      Assumes that the image, newImage, and methods are all not null
 *      and valid (without checking)
 * Checks    :  
 *      None; assumes the inputs to be valid
 * Notes     :    
 *      Only sets the dimensions changed, as the image data stays the same
 ****************************************************************************/
void setVariables(Pnm_ppm ppm, A2Methods_UArray2 newImage, 
                  A2Methods_T methods);


/* Implementations */
void rotate0(Pnm_ppm ppm, A2Methods_mapfun map) 
{
        (void) ppm;
        (void) map;
}

void rotate90(Pnm_ppm ppm, A2Methods_mapfun map)
{
        mapToNewImage(ppm, map, locationMapRotate90, true);
}
void locationMapRotate90(int col, int row, int width, int height, 
                         int *newCol, int *newRow)
{
        *newCol = height - row - 1;
        *newRow = col;
        (void) width;
}

void rotate180(Pnm_ppm ppm, A2Methods_mapfun map)
{
        mapToNewImage(ppm, map, locationMapRotate180, false);
}
void locationMapRotate180(int col, int row, int width, int height, 
                          int *newCol, int *newRow)
{
        *newCol = width  - col - 1;
        *newRow = height - row - 1;
}

void rotate270(Pnm_ppm ppm, A2Methods_mapfun map)
{
        mapToNewImage(ppm, map, locationMapRotate270, true);
}
void locationMapRotate270(int col, int row, int width, int height, 
                          int *newCol, int *newRow)
{
        *newCol = row;
        *newRow = width - col - 1;
        (void) height;
}

void flipHorizontal(Pnm_ppm ppm, A2Methods_mapfun map)
{
        mapToNewImage(ppm, map, locationMapFlipHorizontal, false);
}
void locationMapFlipHorizontal(int col, int row, int width, int height, 
                               int *newCol, int *newRow)
{
        *newCol = width - col - 1;
        *newRow = row;
        (void) height;
}

void flipVertical(Pnm_ppm ppm, A2Methods_mapfun map)
{
        mapToNewImage(ppm, map, locationMapFlipVertical, false);
        
}
void locationMapFlipVertical(int col, int row, int width, int height, 
                          int *newCol, int *newRow)
{
        *newCol = col;
        *newRow = height - row - 1;
        (void) width;
}

void transpose(Pnm_ppm ppm, A2Methods_mapfun map)
{
        mapToNewImage(ppm, map, locationMapTranspose, true);
        
}
void locationMapTranspose(int col, int row, int width, int height, 
                          int *newCol, int *newRow)
{
        *newCol = row;
        *newRow = col;
        (void) width;
        (void) height;
}


/* Helpers */
typedef struct ImageData {
        void (*locationMap)(int, int, int, int, int *, int *);
        A2Methods_T       methods;
        A2Methods_UArray2 newImage;
} ImageData;

void mapToNewImage(Pnm_ppm ppm, A2Methods_mapfun map, 
                   void (*locationMap)(int, int, int, int, int *, int *),
                   bool isFlippedDimensions)
{
        assert(ppm != NULL && map != NULL && locationMap != NULL);

        A2Methods_T        methods   = (A2Methods_T) ppm -> methods;
        A2Methods_UArray2  image     = ppm     -> pixels;
        
        assert(methods != NULL && image != NULL);

        unsigned int       width     = methods -> width(image);
        unsigned int       height    = methods -> height(image);
        unsigned int       size      = methods -> size(image);
        unsigned int       blocksize = methods -> blocksize(image);

        A2Methods_UArray2 newImage;
        if (isFlippedDimensions) {
                newImage = methods -> 
                           new_with_blocksize(height, width, size, blocksize);
        } else {
                newImage = methods -> 
                           new_with_blocksize(width, height, size, blocksize);
        }
        
        struct ImageData cl = {
                locationMap, 
                methods,
                newImage
        };

        map(image, mapToNewApplyFunction, &cl);

        methods -> free(&image);
        ppm     -> pixels = newImage;
        setVariables(ppm, newImage, methods);
}

void mapToNewApplyFunction(int col, int row, A2Methods_UArray2 array2, 
                           A2Methods_Object *ptr, void *cl) 
{
        struct ImageData  *info     = cl;
        A2Methods_T        methods  = info -> methods;
        A2Methods_UArray2  newImage = info -> newImage;
        int                height   = methods -> height(array2);
        int                width    = methods -> width(array2);
        int                newCol;
        int                newRow;

        void (*locationMap)(int, int, int, int, int *, int *) = 
                info -> locationMap;
        locationMap(col, row, width, height, &newCol, &newRow);

        Pnm_rgb  data       = ptr;
        Pnm_rgb  inNewImage = methods -> at(newImage, newCol, newRow);
        
        *inNewImage = *data;
}

void setVariables(Pnm_ppm ppm, A2Methods_UArray2 newImage, 
                  A2Methods_T methods) 
{
        unsigned int newWidth  = methods -> width(newImage);
        unsigned int newHeight = methods -> height(newImage);

        ppm -> width  = newWidth;
        ppm -> height = newHeight;
}
