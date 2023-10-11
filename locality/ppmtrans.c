/**************************************************************
 *                     ppmtrans.c
 *
 *     Assignment      : Locality
 *     Authors         : Matthew Wong, Andersen Prince
 *     Date            : 4 October 2023
 *
 *     Program Purpose : 
 * 
 *     Process the command line argument that the client writes,
 *     such as the operations like rotate 0, 90, 180, 270, 
 *     among others.  
 ***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"
#include "imageMapper.h"
#include "imageTransforms.h"

#define SET_METHODS(METHODS, MAP, WHAT) do {                    \
        methods = (METHODS);                                    \
        assert(methods != NULL);                                \
        map = methods->MAP;                                     \
        if (map == NULL) {                                      \
                fprintf(stderr, "%s does not support "          \
                                WHAT "mapping\n",               \
                                argv[0]);                       \
                exit(1);                                        \
        }                                                       \
} while (false)


static void
usage(const char *progname)
{
        fprintf(stderr, "Usage: %s [-rotate <angle>] "
                        "[-{row,col,block}-major] [filename]\n",
                        progname);
        exit(1);
}

int main(int argc, char *argv[]) 
{
        char *time_file_name    = NULL;
        int   rotation          = 0;
        bool  hasFlipVertical   = false;
        bool  hasFlipHorizontal = false;
        bool  hasTranspose      = false;
        int   i;

        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain; 
        assert(methods);

        /* default to best map */
        A2Methods_mapfun *map = methods->map_default; 
        assert(map);

        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-row-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_row_major, 
                                    "row-major");
                } else if (strcmp(argv[i], "-col-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_col_major, 
                                    "column-major");
                } else if (strcmp(argv[i], "-block-major") == 0) {
                        SET_METHODS(uarray2_methods_blocked, map_block_major,
                                    "block-major");
                } else if (strcmp(argv[i], "-rotate") == 0) {
                        if (!(i + 1 < argc)) {      /* no rotate value */
                                usage(argv[0]);
                        }
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        if (!(rotation == 0 || rotation == 90 ||
                            rotation == 180 || rotation == 270)) {
                                fprintf(stderr, 
                                        "Rotation must be 0, 90 180 or 270\n");
                                usage(argv[0]);
                        }
                        if (!(*endptr == '\0')) {    /* Not a number */
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-time") == 0) {
                        time_file_name = argv[++i];
                } else if (strcmp(argv[i], "-flip") == 0) { 
                        /* ADDED FLIPPING */
                        if (!(i + 1 < argc)) {      /* no flip value */
                                usage(argv[0]);
                        }

                        i++;
                        if (strcmp(argv[i], "horizontal") == 0) {
                                hasFlipHorizontal = true;
                        } else if (strcmp(argv[i], "vertical") == 0) {
                                hasFlipVertical = true;
                        } else {              /* Not a valid flip */
                                fprintf(stderr, 
                                        "Flip must be horizontal or vertical\n"
                                        );      
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-transpose") == 0) {
                        /* ADDED TRANSPOSE */
                        hasTranspose = true;
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                                argv[i]);
                        usage(argv[0]);
                } else if (argc - i > 1) {
                        fprintf(stderr, "Too many arguments\n");
                        usage(argv[0]);
                } else {
                        break;
                }
        }

        FILE *inputFile = stdin;
        if (i < argc) {
                inputFile = fopen(argv[i], "r");
                if (inputFile == NULL) {
                        fprintf(stderr, 
                                "The Image File can not be accessed\n");
                        exit(EXIT_FAILURE);
                }
        }
        Pnm_ppm ppm = Pnm_ppmread(inputFile, methods); 
        if (i < argc) {
                fclose(inputFile);
        }

        FILE *timerFile = NULL;
        if (time_file_name != NULL) {
                timerFile = fopen(time_file_name, "a");
                if (timerFile == NULL) {
                        fprintf(stderr, 
                                "The Timer File can not be accessed\n");
                        Pnm_ppmfree(&ppm);
                        exit(EXIT_FAILURE);
                }
        }

        void (*transform)(Pnm_ppm, A2Methods_mapfun) = NULL;
        if (hasTranspose) {
                transform = *transpose;
        } else if (hasFlipVertical) {
                transform = *flipVertical;
        } else if (hasFlipHorizontal) {
                transform = *flipHorizontal;
        } else if (rotation == 90) {
                transform = *rotate90;
        } else if (rotation == 180) {
                transform = *rotate180;
        } else if (rotation == 270) {
                transform = *rotate270;
        } else {
                transform = *rotate0;
        }
        
        
        imageMapper(ppm, map, transform, timerFile);

        Pnm_ppmwrite(stdout, ppm);
        Pnm_ppmfree(&ppm);

        if (timerFile != NULL) {
                fclose(timerFile);
        }
}
