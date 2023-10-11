/**************************************************************
 *                     a2plain.c
 *
 *     Assignment      : Locality
 *     Authors         : Matthew Wong, Andersen Prince
 *     Date            : 2 October 2023
 *
 *     Program Purpose : 
 *     
 *     Implementation of a 2-dimensional array, as well as 
 *     a collection of functions for performing different 
 *     operations on the array. It defines functions for 
 *     creating, manipulating, and freeing 2-D arrays. 
 *************************************************************/

#include <string.h>
#include <mem.h>
#include <a2plain.h>
#include "uarray2.h"
#include <assert.h>

/************************************************/
/* Define a private version of each function in */
/* A2Methods_T that we implement.               */
/************************************************/

struct small_closure {
        A2Methods_smallapplyfun *apply;
        void                    *cl;
};

/***********************************new**************************************
 * Purpose    :               
 *      Creates a new 2-D array with the specified dimensions, and element size
 * Parameters :
 *      (int) width         : Denotes the 2-D array's width
 *      (int) height        : Denotes the 2-D array's height
 *      (int) size          : Denotes the size of each element in the 2-D 
 *                            array's size
 * Returns : 
 *      (A2Methods_UArray2) : a new 2-D array with new dimensions and element 
 *                            size
 * Expects    :               
 * Notes      :               
 *      Allocates memory for the 2-D array
 ****************************************************************************/
static A2Methods_UArray2 new(int width, int height, int size)
{
        return UArray2_new(width, height, size);
}

/*****************************new_with_blocksize*****************************
 * Purpose    :               
 *      Creates a new 2-D array with the specified dimensions, and the element 
 *      size
 * Parameters :    
 *      (int) width         : Denotes the width of the 2-D array
 *      (int) height        : Denotes the height of the 2-D array
 *      (int) size          : Denotes the size of each element in the 2-D array
 *      (int) blocksize     : Denotes the block size
 * Returns    : 
 *      (A2Methods_UArray2) : A new 2-D array with the width, height, size, and 
 *                            element size
 * Notes      :              
 *      Does not use the blocksize parameter
 ****************************************************************************/
static A2Methods_UArray2 new_with_blocksize(int width, int height, int size,
                                            int blocksize)
{
        (void) blocksize;
        return new(width, height, size);
}

/*********************************a2free*************************************
 * Purpose    :                       
 *      Frees the memory in the 2-D array and sets the pointer to NULL
 * Parameters :    
 *      (A2Methods_UArray2) *array2p : A pointer to a pointer to the 2-D array
 * Returns    : 
 *      (void)                       : nothing
 * Expects    :                        
 *      Should point to a valid 2-D array
 * Notes      :                        
 *      Deallocates memory of the 2-D array
 ****************************************************************************/
static void a2free(A2Methods_UArray2 *array2p) 
{
        UArray2_free((UArray2_T *)array2p);
}

/************************************width***********************************
 * Purpose    :                      
 *      Retrieves the width of a 2-D array
 * Parameters :    
 *      (A2Methods_UArray2) array2 : a 2-D array for which you want to get the
 *                                   width
 * Returns    : 
 *      (int)                      : Denotes the width of the 2-D array
 * Expects    :                      
 *      Should be a valid 2-D array
 * Notes      :                      
 *      Returns the number of columns in the 2-D array
 ****************************************************************************/
static int width(A2Methods_UArray2 array2)
{
        return UArray2_width(array2);
}

/**********************************height************************************
 * Purpose   :                       
 *      Retrieves the height of a 2-D array
 * Paramters :
 *      (A2Methods_UArray2) array2 : A 2-D array which contains the height 
 * Returns   : 
 *      (int)                      : The height of the 2-D array
 * Expects   :                       
 *      Should be a valid 2-D array
 * Notes     :                       
 *      Returns number of rows in the 2-D array, representing the height
 ****************************************************************************/
static int height(A2Methods_UArray2 array2)
{
        return UArray2_height(array2);
}

/**************************************size**********************************
 * Purpose    :                      
 *      Retrieves the size of the 2-D array
 * Parameters :    
 *      (A2Methods_UArray2) array2 : A 2-D array which denotes the size
 * Returns    : 
 *      (int)                      : Denotes the size of the 2-D array
 * Expects    :                      
 *      The 2-D array should be valid 
 * Notes      :                      
 *      Returns the total number of elements in the 2-D array
 ****************************************************************************/
static int size(A2Methods_UArray2 array2)
{
        return UArray2_size(array2);
}

/********************************blocksize***********************************
 * Purpose    : 
 *      Retrieves the block size of a 2-D array
 * Parameters :                      
 *      (A2Methods_UArray2) array2 : A 2-D array which contains the blocksize
 * Returns    : 
 *      (int)                      : Denotes the block size of the 2-D array
 * Expects    :                      
 *      Should be a valid 2-D array
 * Notes      :                      
 *      Returns the block size value, but parameter is unused
 ****************************************************************************/
static int blocksize(A2Methods_UArray2 array2)
{
        (void) array2;
        return 1;
}

/**************************************at************************************
 * Purpose   :                       
 *      Retrieves the element at the specified column and row in a 2-D array
 * Paramters :    
 *      (A2Methods_UArray2) array2 : A 2-D array which stores the element
 *      int                 col    : Denotes the column index of the element
 *      int                 row    : Denotes the row index of the element
 * Returns   :    
 *      (A2Methods_Object)         : A pointer to the element at the specified 
 *                                   column and row
 * Expects   :                       
 *      Should be a valid 2-D array
 * Notes     :                       
 *      Retrieves and returns a pointer to the element at the specified 
 *      col and row indices
 ****************************************************************************/
static A2Methods_Object *at(A2Methods_UArray2 array2, int col, int row)
{
        return UArray2_at(array2, col, row);
}

/******************************map_row_major*********************************
 * Purpose    :                       
 *      Apply a function to each element of a 2-D array in row-major order
 * Parameters :    
 *      (A2Methods_Uarray2)  uarray2 : A 2-D array that will be processed
 *      (A2Methods_applyfun) apply   : Function that will be applied to each
 *                                     element in the 2-D array
 *      (void)               cl      : A closure pointer which stores any info
 *                                      neccessary for the apply function   
 * Returns    :    
 *      (void)                       : nothing
 * Expects    :                        
 *      A valid 2-D array
 * Notes      :                        
 *      Applies this function to each element of the 2-D array
 ****************************************************************************/
static void map_row_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
        UArray2_map_row_major(uarray2, (UArray2_applyfun*)apply, cl);
}

/*******************************map_col_major*******************************
 * Purpose    :                       
 *      Applies the function to each element of the 2-D array in column-major 
 *      order
 * Parameters :    
 *      (A2Methods_UArray2) uarray2 : The 2-D array which will be processed
 *      (A2Mthods_applyfun) apply   : Represents the function which will be 
 *                                    applied to each element 
 *      (void)              *cl     : A closure pointer that stores any info 
 *                                    needed by the apply function
 * Returns    :
 *      (void)                      : nothing
 * Expects    :                       
 *      Should be a valid 2-D array
 * Notes      :                       
 *      Applies the function to each element of the 2-D array
 ****************************************************************************/
static void map_col_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
        UArray2_map_col_major(uarray2, (UArray2_applyfun*)apply, cl);
}

/**********************************apply_small********************************
 * Purpose   :                      
 *      Applies the function to a particular element in the 2-D array
 * Paramters :  
 *      (int)             i       : Denotes the row index of the element
 *      (int)             j       : Denotes the column index of the element
 *      UArray2_T         uarray2 : The 2-D array which will be processed
 *      (void)            *elem   : A pointer to the element in the 2-D array
 *      (void)            *cl     : A closure pointer that will store data that 
 *                                  is necessary for the apply function
 * Returns   :
 *      (void)                    : nothing
 * Expects   :                      
 *      Parameters should be valid within the bounds of the 2-D array
 ****************************************************************************/
static void apply_small(int i, int j, UArray2_T uarray2,
                        void *elem, void *vcl)
{
        struct small_closure *cl = vcl;
        (void)i;
        (void)j;
        (void)uarray2;
        cl->apply(elem, cl->cl);
}

/****************************small_map_row_major*****************************
 * Purpose   :                           
 *      Apply a small apply function to each element of the 2-D array in row 
 *      major order
 * Paramters :    
 *      (A2Methods_UArray2)       a2    : The 2-D array which will be processed
 *      (A2Methods_smallapplyfun) apply : A small apply function that will be 
 *                                        be applied to each element in the 2-D
 *                                        array
 *      (void)                    *cl   : A closure pointer that stores any
 *                                        info needed by the small apply 
 *                                        function
 * Returns   : 
 *      (void)                          : nothing
 * Expects   :                            
 *      Should be a valid 2-D array
 * Notes     :                            
 *      Applies the function to each element in row major order
 ****************************************************************************/
static void small_map_row_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_row_major(a2, apply_small, &mycl);
}

/*****************************small_map_col_major****************************
 * Purpose    :                           
 *      Apply a small apply function to each element in the 2-D array in column 
 *      major order
 * Parameters :    
 *      (A2Methods_UArray2)       a2    : The 2-D array which will be processed
 *      (A2Methods_smallapplyfun) apply : A small apply function which will be
 *                                        applied to each element in the 
 *                                        2-D array
 *      (void)                    *cl   : A closure pointer which stores any
 *                                        info that is necessary for the apply 
 *                                        function
 * Returns    : 
 *      (void)                          : nothing
 * Expects    :                           
 *      Should be a valid 2-D array
 * Notes      :                           
 *      Applies the function to each element in column major order
 ****************************************************************************/
static void small_map_col_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_col_major(a2, apply_small, &mycl);
}

static struct A2Methods_T uarray2_methods_plain_struct = {
        new,
        new_with_blocksize,
        a2free,
        width,
        height,
        size,
        blocksize,
        at,
        map_row_major,
        map_col_major,
        NULL,                   /* map_block_major */
        map_row_major,
        small_map_row_major,
        small_map_col_major,
        NULL,                   /* small_map_block_major */
        small_map_row_major
};

A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;