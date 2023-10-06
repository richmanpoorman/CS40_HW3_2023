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
/*
* new blocked 2d array
* blocksize = square root of # of cells in block.
* blocksize < 1 is a checked runtime error
*/
UArray2b_T UArray2b_new (int width, int height, int size, int blocksize);
/* new blocked 2d array: blocksize as large as possible provided
* block occupies at most 64KB (if possible)
*/
UArray2b_T UArray2b_new_64K_block(int width, int height, int size);
void UArray2b_free (UArray2b_T *array2b);
int UArray2b_width (UArray2b_T array2b);
int UArray2b_height (UArray2b_T array2b);
int UArray2b_size (UArray2b_T array2b);
int UArray2b_blocksize(UArray2b_T array2b);
/* return a pointer to the cell in the given column and row.
* index out of range is a checked run-time error
*/
void *UArray2b_at(UArray2b_T array2b, int column, int row);
/* visits every cell in one block before moving to another block */
void UArray2b_map(UArray2b_T array2b,
                  void apply(int col, int row, UArray2b_T array2b,
                  void *elem, void *cl),
                  void *cl);

void UArray2b_mapDataToUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl);
void UArray2b_mapToFreeUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl);
void UArray2b_UArray2MapForBlockwise(int col, int row, UArray2_T array2, 
                                     void *elem, void *cl);
/*
* it is a checked run-time error to pass a NULL UArray2b_T
* to any function in this interface
*/

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

        UArray2_map_row_major(blocks, UArray2b_mapDataToUArray2, newUArray2b);

        return newUArray2b;
}

void UArray2b_mapDataToUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl)
{
        assert(array2 != NULL);
        UArray2b_T *data      = cl;
        UArray_T   *block     = elem;
        int         blocksize = (*data) -> blocksize;
        int         size      = (*data) -> size;
        UArray_T    newBlock  = UArray_new(blocksize * blocksize, size);
        
        *block = newBlock;
        (void) col;
        (void) row;
        (void) array2;
}
/* new blocked 2d array: blocksize as large as possible provided
* block occupies at most 64KB (if possible)
*/
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
        UArray2_map_row_major((*array2b) -> blocks, 
                              UArray2b_mapToFreeUArray2, NULL);
        FREE(array2b);
        *array2b = NULL;
}
void UArray2b_mapToFreeUArray2(int col, int row, UArray2_T array2, 
                           void *elem, void *cl)
{
        UArray_T *block = elem;
        
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
/* return a pointer to the cell in the given column and row.
* index out of range is a checked run-time error
*/
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

struct UArray2b_blockwise_closure {
        UArray2b_T array2b;
        void (*apply)(int col, int row, UArray2b_T array2b,
                      void *elem, void *cl);
        void *cl;
};

/* visits every cell in one block before moving to another block */
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