#include "uarray2b.h"
#include <stdlib.h>
#include <uarray.h>
#include <assert.h>
#include <stdio.h>
void sizeTest() 
{
        int width = 4;
        int height = 5;
        int size = sizeof(UArray_T);
        int blocksize = 5;
        UArray2b_T array = UArray2b_new(width, height, size, blocksize);
        
        int testWidth = UArray2b_width(array);
        int testHeight = UArray2b_height(array);
        int testSize = UArray2b_size(array);
        int testBlocksize = UArray2b_blocksize(array);

        assert(testWidth == width);
        assert(testHeight == height);
        assert(testSize == size);
        assert(testBlocksize == blocksize);

        UArray2b_free(&array);
        assert(array == NULL);

        printf("Passed Size Test\n");

}

void elementsTest() 
{
        int width = 4;
        int height = 5;
        int size = sizeof(int);
        int blocksize = 2;
        UArray2b_T array = UArray2b_new(width, height, size, blocksize);

        for (int c = 0; c < width; c++) {
                for (int r = 0; r < height; r++) {
                        int *elem = UArray2b_at(array, c, r);
                        *elem = c * height + r;
                }
        }

        for (int r = 0; r < width; r++) {
                for (int c = 0; c < width; c++) {
                        int *elem = UArray2b_at(array, c, r);
                        assert (*elem == c * height + r);
                }
        }

        UArray2b_free(&array);
        assert(array == NULL);

        printf("Passed Elements Test\n");

}

void blockMajorTest_blockMap(int col, int row, UArray2b_T array2b, 
                             void *elem, void *cl)
{
        int *data  = elem;
        int *count = cl;
        int height = UArray2b_height(array2b);
        assert(*data == col * height + row);
        (*count)++;
}
void blockMajorTest() 
{
        int width = 100;
        int height = 5000;
        int size = sizeof(int);
        int blocksize = 13;
        UArray2b_T array = UArray2b_new(width, height, size, blocksize);

        for (int c = 0; c < width; c++) {
                for (int r = 0; r < height; r++) {
                        int *elem = UArray2b_at(array, c, r);
                        *elem = c * height + r;
                }
        }
        int count = 0;
        UArray2b_map(array, blockMajorTest_blockMap, &count);
        assert(count == width * height);
        
        UArray2b_free(&array);
        assert(array == NULL);

        printf("Passed Block Major Test\n");
}

void new64kTest() {
        int width = 100;
        int height = 5000;
        int size = sizeof(int);
        UArray2b_T array = UArray2b_new_64K_block(width, height, size);

        int testWidth = UArray2b_width(array);
        int testHeight = UArray2b_height(array);
        int testSize = UArray2b_size(array);
        int testBlocksize = UArray2b_blocksize(array);

        assert(testWidth == width);
        assert(testHeight == height);
        assert(testSize == size);
        assert(testBlocksize == 128);

        

        for (int c = 0; c < width; c++) {
                for (int r = 0; r < height; r++) {
                        int *elem = UArray2b_at(array, c, r);
                        *elem = c * height + r;
                }
        }

        for (int r = 0; r < width; r++) {
                for (int c = 0; c < width; c++) {
                        int *elem = UArray2b_at(array, c, r);
                        assert (*elem == c * height + r);
                }
        }

        int count = 0;
        UArray2b_map(array, blockMajorTest_blockMap, &count);
        assert(count == width * height);

        UArray2b_free(&array);
        assert(array == NULL);

        printf("Passed New 64k Block Test\n");
}

void longLongTest() 
{
        int width = 100;
        int height = 5000;
        int size = sizeof(long long);
        UArray2b_T array = UArray2b_new_64K_block(width, height, size);

        int testWidth = UArray2b_width(array);
        int testHeight = UArray2b_height(array);
        int testSize = UArray2b_size(array);
        int testBlocksize = UArray2b_blocksize(array);

        assert(testWidth == width);
        assert(testHeight == height);
        assert(testSize == size);
        assert(testBlocksize == 90);

        

        for (int c = 0; c < width; c++) {
                for (int r = 0; r < height; r++) {
                        long long *elem = UArray2b_at(array, c, r);
                        *elem = c * height + r;
                }
        }

        for (int r = 0; r < width; r++) {
                for (int c = 0; c < width; c++) {
                        long long *elem = UArray2b_at(array, c, r);
                        assert (*elem == c * height + r);
                }
        }

        int count = 0;
        UArray2b_map(array, blockMajorTest_blockMap, &count);
        assert(count == width * height);

        UArray2b_free(&array);
        assert(array == NULL);

        printf("Passed Long Long Test\n");
}

struct bigStruct {
        char new64kArray [64 * 1024];
};
void bigStructTest() {
        int width = 100;
        int height = 100;
        int size = sizeof(struct bigStruct);
        UArray2b_T array = UArray2b_new_64K_block(width, height, size);

        int testWidth = UArray2b_width(array);
        int testHeight = UArray2b_height(array);
        int testSize = UArray2b_size(array);
        int testBlocksize = UArray2b_blocksize(array);

        assert(testWidth == width);
        assert(testHeight == height);
        assert(testSize == size);
        assert(testBlocksize == 1);

        printf("Passed Big Struct Test\n");
}
int main(int argc, char *argv[]) 
{
        sizeTest();
        elementsTest();
        blockMajorTest();
        new64kTest();
        longLongTest();
        bigStructTest();
        (void) argc;
        (void) argv;
}