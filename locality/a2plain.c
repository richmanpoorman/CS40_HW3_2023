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
 * Parameters :
 *      (int) width         - Denotes the 2-D array's width
 *      (int) height        - Denotes the 2-D array's height
 *      (int) size          - Denotes the 2-D array's size
 * Returns : 
 *      (A2Methods_UArray2) - a 2-D array
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static A2Methods_UArray2 new(int width, int height, int size)
{
        return UArray2_new(width, height, size);
}

/*****************************new_with_blocksize*****************************
 * Purpose    :
 * Parameters :    
 *      (int) width         - Denotes 
 *      (int) height        -
 *      (int) size          -
 *      (int) blocksize     -
 * Returns    : 
 *      (A2Methods_UArray2)
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static A2Methods_UArray2 new_with_blocksize(int width, int height, int size,
                                            int blocksize)
{
        (void) blocksize;
        return new(width, height, size);
}

/*********************************a2free*************************************
 * Purpose    :
 * Parameters :    
 *      (A2Methods_UArray2) *array2p -
 * Returns    : 
 *      (void)                       -
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static void a2free(A2Methods_UArray2 *array2p) 
{
        UArray2_free((UArray2_T *)array2p);
}

/************************************width***********************************
 * Purpose    :
 * Parameters :    
 *      (A2Methods_UArray2) array2 -
 * Returns    : 
 *      (int)                      -
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static int width(A2Methods_UArray2 array2)
{
        return UArray2_width(array2);
}

/**********************************height************************************
 * Purpose   :
 * Paramters :    
 *      (A2Methods_UArray2) array2 -
 * Returns   : 
 *      (int)                      -
 * Expects   :  
 * Notes     :    
 ****************************************************************************/
static int height(A2Methods_UArray2 array2)
{
        return UArray2_height(array2);
}

/**************************************size**********************************
 * Purpose    :
 * Parameters :    
 *      (A2Methods_UArray2) array2 -
 * Returns    : 
 *      (int)                      -
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static int size(A2Methods_UArray2 array2)
{
        return UArray2_size(array2);
}

/********************************blocksize***********************************
 * Parameters :    
 *      (A2Methods_UArray2) array2 -
 * Returns    : 
 *      (int)                      -
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static int blocksize(A2Methods_UArray2 array2)
{
        (void) array2;
        return 1;
}

/**************************************at************************************
 * Purpose   :
 * Paramters :    
 *      (A2Methods_UArray2) array2 -
 *      int                 col    -
 *      int                 row    -
 * Returns   :    
 *      (A2Methods_Object)         -
 * Expects   :  
 * Notes     :    
 ****************************************************************************/
static A2Methods_Object *at(A2Methods_UArray2 array2, int col, int row)
{
        return UArray2_at(array2, col, row);
}

/******************************map_row_major*********************************
 * Purpose    :
 * Parameters :    
 *      (A2Methods_Uarray2)  uarray2 -
 *      (A2Methods_applyfun) apply   -
 *      (void)               cl      -     
 * Returns    :    
 *      (void)                       -
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static void map_row_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
        UArray2_map_row_major(uarray2, (UArray2_applyfun*)apply, cl);
}

/*******************************map_col_major*******************************
 * Purpose    :
 * Parameters :    
 *      (A2Methods_UArray2) uarray2 -
 *      (A2Mthods_applyfun) apply   -
 *      (void)                      -
 * Returns    : 
 *      (void)                      -
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static void map_col_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
        UArray2_map_col_major(uarray2, (UArray2_applyfun*)apply, cl);
}

/**********************************apply_small********************************
 * Purpose   : 
 * Paramters :  
 *      (int)             i       -
 *      (int)             j       -
 *      UArray2_T         uarray2 -
 *      (void)            *elem   -
 *      (void)            *cl     -     
 * Returns   : 
 * Expects   :  
 * Notes     :    
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
 * Paramters :    
 *      (A2Methods_UArray2)       a2    -
 *      (A2Methods_smallapplyfun) apply -
 *      (void)                    *cl   -
 * Returns   : 
 *      (void)                          -
 * Expects   :  
 * Notes     :    
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
 * Parameters :    
 *      (A2Methods_UArray2)       a2    -
 *      (A2Methods_smallapplyfun) apply -
 *      (void)                    *cl   -
 * Returns    : 
 *      (void)                          -
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
static void small_map_col_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_col_major(a2, apply_small, &mycl);
}

/***********************uarray2_methods_plain_struct*************************
 * Purpose    :
 * Parameters :    
 * Returns    : 
 * Expects    :  
 * Notes      :    
 ****************************************************************************/
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
