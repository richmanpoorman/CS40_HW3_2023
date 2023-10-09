/**************************************************************
 *                     UArray2b.c
 *
 *     Assignment      : Locality
 *     Authors         : Matthew Wong, Andersen Prince
 *     Date            : 1 October 2023
 *
 *     Program Purpose : 
 *
 *     This file provides support for a blocked 2-D array.  
 *     To optimize memory access patterns and locality, a 
 *     blocked 2-D array is split into blocks of items.
 ***************************************************************/

#include "uarray2.h"
#include <uarray.h>
#include <mem.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct UArray2b_T {
        UArray2_T blocks;
        int       width;
        int       height;
        int       size;
        int       blocksize;
} *UArray2b_T;

struct UArray2b_blockwise_closure {
        UArray2b_T array2b;
        void (*apply)(int col, int row, UArray2b_T array2b,
                      void *elem, void *cl);
        void *cl;
};

/*********************************UArray2b_new*********************************
 * Purpose    :                   
 *      Creates a blocked 2-D array with the width, height, size of each 
 *      element, and blocksize
 * Parameters : 
 *      (int)        width      : Denotes the 2-D array's width 
 *      (int)        height     : Denotes the 2-D array's height
 *      (int)        size       : Denotes the 2-D array's size
 *      (int)        blocksize  : Denotes the 2-D array's blocksizes
 * Returns    : 
 *      (UArray2b_T)            : A new 2-D blocked array
 * Expects    :                   
 *      The parameters should be integers greater than zero 
 * Notes      :                   
 *      Blocked 2-D array are split into blocks of elements to create efficient 
 *      memory allocation
 ****************************************************************************/
UArray2b_T UArray2b_new (int width, int height, int size, int blocksize);

/****************************UArray2b_mapNewToUArray2*************************
 * Purpose    :                 
 *      Creates a blocked 2-D array with a 64K size block
 * Parameters :  
 *      (int)       width     : Denotes the width of a 2-D array
 *      (int)       height    : Denotes the height of a 2-D array
 *      (int)       size      : Denotes the size of a 2-D array
 * Returns    :  
 *      (UArray2b_T)          : A blocked 2-D array with 64K-sized blocks
 * Expects    :                 
 *      The paramters should be valid inputs (greater) than zero
 * Notes      :                 
 *      Helps with memory storage
 ****************************************************************************/
UArray2b_T UArray2b_new_64K_block(int width, int height, int size);

/*******************************UArray2b_free*********************************
 * Purpose    :                 
 *      Frees the memory created by the 2-D blocked array
 * Parameters :  
 *      (UArray2b_T) *array2b : A pointer to a pointer to the blocked 2-D array
 * Returns    :  
 *      (void)                : nothing
 * Expects    :   
 *      The 2-D array should be valid
 * Notes      :                 
 *      Sets the pointer to the blocked 2-D array to NULL
 ****************************************************************************/
void UArray2b_free (UArray2b_T *array2b);

/****************************UArray2b_mapToFreeUArray*************************
 * Purpose    :              
 *      Map function which is used to free the inner 2-D array
 * Parameters :    
 *      (int)       col    : Denotes the 2-D array column index
 *      (int)       row    : Denotes the 2-D array row index
 *      (UArray2_T) array2 : Denotes a inner 2-D array 
 *      (void)      *elem  : A pointer to an element 
 *      (void)      *cl    : A closure pointer which store info 
 * Returns    :  
 *      (void)             : nothing
 * Notes      :              
 *      Used to free the inner 2-D arrays 
 ****************************************************************************/
void UArray2b_mapToFreeUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl);
                           
/*********************************UArray2b_width******************************
 * Purpose    :                
 *      Retrieves the width of a blocked 2-D array
 * Parameters :  
 *      (UArray2b_T) array2b - Represent a blocked 2-D array
 * Returns    :  
 *      (int)                - The width of the 2-D array
 * Expects    :    
 *      Should be a valid blocked 2-D array
 * Notes      :                
 *      Width represents the number of columns in the array
 ****************************************************************************/
int UArray2b_width (UArray2b_T array2b);

/********************************UArray2b_height*****************************
 * Purpose    :                 
 *      Retrieves the height of the 2-D blocked array
 * Parameters :    
 *      (UArray2b_T)  array2b : Represents a blocked 2-D array
 * Returns    :  
 *      (int)                 : The height of the 2-D array
 * Expects    :                    
 *      The paramter should be a valid blocked 2-D array
 * Notes      :                 
 *      Gets and returns the height of the blocked 2-D array
 ****************************************************************************/
int UArray2b_height (UArray2b_T array2b);

/********************************UArray2b_T***********************************
 * Purpose    :                 
 *      Retrieve the size of a blocked 2-D array
 * Parameters : 
 *      (UArray2b_T) array2b : Represents a 2-D array
 * Returns    :  
 *      (int)                : the size of the 2-D array
 * Expects    : 
 *      The parameter should be a valid blocked 2-D array
 * Notes      :     
 *      Gets and returns the size of the blocked 2-D array
 ****************************************************************************/
int UArray2b_size (UArray2b_T array2b);

/********************************UArray2b_size********************************
 * Purpose    :          
 *      Retrieve the block size of the 2-D array
 * Paramters  : 
 *      (UArray2b_T) array2b : Represents a blocked 2-D array
 * Returns    :  
 *      (int)                : the block size of the 2-D array
 * Expects    :
 *      Should be a valid blocked 2-D array 
 * Notes      :     
 *      Gets and returns the block size
 ****************************************************************************/
int UArray2b_blocksize(UArray2b_T array2b);

/*********************************UArray2b_at*********************************
 * Purpose   :                
 *      Retrieves a pointer to the element at the column and row which is 
 *      specificed in the blocked 2-D array
 * Paramters :    
 *      (UArray2b_T)    array2b : Represents a 2-D array 
 *      (int)           column  : Denotes a 2-D array column
 *      (int)           row     : Denotes a 2-D array row 
 * Returns   :  
 *      (void *)                : A pointer to the element at the column/row in 
 *                                the 2-D array
 * Expects   :
 *      The paramter should be a valid blocked 2-D array
 * Notes     :     
 *      Allows acess to a specific element (column/row) in the blocked 2-D array
 ****************************************************************************/
void *UArray2b_at(UArray2b_T array2b, int column, int row);

/**********************************UArray2b_map*******************************
 * Purpose    : 
 *      Apply a function to each element in the blocked 2-D array
 * Parameters :
 *      (UArray2b_T) array2b : Denotes a blocked 2-D array
 *      (void)       apply   : A function which visits each element in the 2-D 
 *                             array
 *      (void)       cl      : A closure pointer which stores the data for the 
 *                             apply function
 * Returns    :  
 *      (void)               : nothing
 * Expects    :  
 *      visits every cell in one block before moving to another block
 * Notes      :     
 *      Applies the apply function to each elementwithin the 2-D blocked array
 ****************************************************************************/
void UArray2b_map(UArray2b_T array2b,
                  void apply(int col, int row, UArray2b_T array2b,
                  void *elem, void *cl),
                  void *cl);

/****************************UArray2b_mapNewToUArray2*************************
 * Purpose    : 
 *      Apply a function to each element in a blocked 2-D array
 * Parameters :
 *      (UArray2b_T) array2b : A blocked 2-D array
 *      (void)       apply   : A function which visits each element in the 2-D 
 *                             array
 *      (void)       cl      : A closure pointer that stores necessary data for
 *                             the apply function
 * Returns    :  
 *      (void)               : nothing
 * Expects    :  
 *      visits every cell in one block before moving to another block
 ****************************************************************************/
void UArray2b_mapNewToUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl);

/***********************UArray2b_UArray2MapForBlockwise***********************
 * Purpose    :             
 *      Map function which is sued for blockwise operations on a 2-D array
 *      in the 2-D blocked array
 * Parameters :    
 *      (int)       col    : Denotes the 2-D array's column index
 *      (int)       row    : Denotes the 2-D array's row index
 *      (UArray2_T) array2 : Represents a 2-D array in a blocked 2-D array
 *      (void)      *elem  : A pointer to an element
 *      (void)      *cl    : A closure pointer that stores info for the map
 *                           function
 * Returns    :  
 *      (void)             : nothing    
 ****************************************************************************/
void UArray2b_UArray2MapForBlockwise(int col, int row, UArray2_T array2, 
                                     void *elem, void *cl);

UArray2b_T UArray2b_new (int width, int height, int size, int blocksize) 
{
        assert(width >= 0);
        assert(height >= 0);
        assert(size > 0);
        assert(blocksize > 0);
        UArray2b_T newUArray2b    = ALLOC(sizeof(*newUArray2b));
        int        blockWidth     = (width + blocksize  - 1) / blocksize;
        int        blockHeight    = (height + blocksize - 1) / blocksize;

        UArray2_T blocks = UArray2_new(blockWidth, blockHeight, 
                                       sizeof(UArray_T));

        newUArray2b -> width     = width;
        newUArray2b -> height    = height;
        newUArray2b -> size      = size;
        newUArray2b -> blocksize = blocksize;
        newUArray2b -> blocks    = blocks;
        UArray2_map_row_major(blocks, UArray2b_mapNewToUArray2, newUArray2b);

        return newUArray2b;
}

void UArray2b_mapNewToUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl)
{
        assert(array2 != NULL);
        UArray2b_T  data      = cl;
        UArray_T   *block     = elem;
        int         blocksize = data -> blocksize;
        int         size      = data -> size;
        UArray_T    newBlock  = UArray_new(blocksize * blocksize, size);
        
        *block = newBlock;
        (void) col;
        (void) row;
        (void) array2;
}

UArray2b_T UArray2b_new_64K_block(int width, int height, int size) 
{
        assert(width >= 0);
        assert(height >= 0);
        assert(size > 0);
        double maxNumBytes = 64 * 1024;
        int    blocksize   = (int)sqrt(maxNumBytes / size);
        if (blocksize < 1) {
                blocksize = 1;
        }
        return UArray2b_new(width, height, size, blocksize);
}

void UArray2b_free (UArray2b_T *array2b) 
{
        assert(array2b != NULL && *array2b != NULL);
        UArray2_T blocks = (*array2b) -> blocks;
        UArray2_map_row_major((*array2b) -> blocks, 
                              UArray2b_mapToFreeUArray2, NULL);
        UArray2_free(&blocks);
        FREE(*array2b);
}

void UArray2b_mapToFreeUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl)
{
        UArray_T *block = elem;
        if (elem == NULL) {
                return;
        }
        UArray_free(block);
        *block = NULL;
        (void) col;
        (void) row;
        (void) array2;
        (void) cl;
}

int UArray2b_width (UArray2b_T array2b) 
{
        assert(array2b != NULL);
        return array2b -> width;
}


int UArray2b_height (UArray2b_T array2b) 
{
        assert(array2b != NULL);
        return array2b -> height;
}


int UArray2b_size (UArray2b_T array2b) 
{
        assert(array2b != NULL);
        return array2b -> size;
}

int UArray2b_blocksize(UArray2b_T array2b) 
{
        assert(array2b != NULL);
        return array2b -> blocksize;
}

void *UArray2b_at(UArray2b_T array2b, int column, int row) 
{
        assert(array2b != NULL);

        int       width        = UArray2b_width(array2b);
        int       height       = UArray2b_height(array2b);
        int       blocksize    = UArray2b_blocksize(array2b);
        UArray2_T blocks       = array2b -> blocks;
        
        assert(column >= 0 && row >= 0 && column < width && row < height);
        
        int       blockCol     = column / blocksize; 
        int       blockRow     = row    / blocksize;
        int       inBlock      = blocksize * (column % blocksize) + 
                                 (row % blocksize);
        
        UArray_T *block        = UArray2_at(blocks, blockCol, blockRow);
        void     *data         = UArray_at(*block, inBlock);
        return data;
        
}

void UArray2b_map(UArray2b_T array2b,
                  void apply(int col, int row, UArray2b_T array2b,
                  void *elem, void *cl),
                  void *cl) 
{
        assert(array2b != NULL);

        struct UArray2b_blockwise_closure closure = {
                array2b,
                apply,
                cl
        };
        UArray2_map_row_major(array2b -> blocks, 
                              UArray2b_UArray2MapForBlockwise, &closure);
}

void UArray2b_UArray2MapForBlockwise(int col, int row, UArray2_T array2, 
                                     void *elem, void *cl) 
{
        struct UArray2b_blockwise_closure *closure = cl;
        UArray2b_T array2b = closure -> array2b;

        int       width       = UArray2b_width(array2b);
        int       height      = UArray2b_height(array2b);
        int       blocksize   = UArray2b_blocksize(array2b);
        int       blockLength = blocksize * blocksize;
        UArray_T *block       = UArray2_at(array2, col, row);

        int       inArrayCol  = width  - col * blocksize;
        int       inArrayRow  = height - row * blocksize;

        for (int index = 0; index < blockLength; index++) {
                int inBlockCol = index / blocksize;
                int inBlockRow = index % blocksize;
                int absCol     = col * blocksize + inBlockCol;
                int absRow     = row * blocksize + inBlockRow;

                if (inBlockCol >= inArrayCol) {
                        continue;
                }
                if (inBlockRow >= inArrayRow) {
                        continue;
                }

                void *data = UArray_at(*block, index);
                closure -> apply(absCol, absRow, array2b, data, closure -> cl);
        }
        (void) elem;
}