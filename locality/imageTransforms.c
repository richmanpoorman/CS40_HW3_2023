#include <pnm.h>
#include <a2methods.h>
#include <stdbool.h>
#include "assert.h"

void rotate0(Pnm_ppm ppm, A2Methods_mapfun map);
void rotate90(Pnm_ppm ppm, A2Methods_mapfun map);
void rotate180(Pnm_ppm ppm, A2Methods_mapfun map);
void rotate270(Pnm_ppm ppm, A2Methods_mapfun map);
void flipHorizontal(Pnm_ppm ppm, A2Methods_mapfun map);
void flipVertical(Pnm_ppm ppm, A2Methods_mapfun map);
void transpose(Pnm_ppm ppm, A2Methods_mapfun map);


void locationMapRotate90(int col, int row, int width, int height, 
                         int *newCol, int *newRow);
void locationMapRotate180(int col, int row, int width, int height, 
                         int *newCol, int *newRow);
void locationMapRotate270(int col, int row, int width, int height, 
                          int *newCol, int *newRow);
void locationMapFlipHorizontal(int col, int row, int width, int height, 
                               int *newCol, int *newRow);
void locationMapFlipVertical(int col, int row, int width, int height, 
                             int *newCol, int *newRow);
void locationMapTranspose(int col, int row, int width, int height, 
                          int *newCol, int *newRow);

void mapToNewImage(Pnm_ppm ppm, A2Methods_mapfun map, 
                   void (*locationMap)(int, int, int, int, int *, int *),
                   bool isFlippedDimensions);
void mapToNewApplyFunction(int col, int row, A2Methods_UArray2 array2, 
                           A2Methods_Object *ptr, void *cl);
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
        assert(ppm != NULL && map != NULL);
        assert(locationMap != NULL);

        A2Methods_T        methods   = (A2Methods_T) ppm -> methods;
        A2Methods_UArray2  image     = ppm     -> pixels;
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
