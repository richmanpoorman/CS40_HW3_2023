#include <pnm.h>
#include <a2methods.h>
#include <stdio.h>


void imageMapper(Pnm_ppm image, A2Methods_mapfun map, 
                 void (*transform)(Pnm_ppm, A2Methods_mapfun)
                 FILE *timerFile);

void imageMapper(Pnm_ppm image, A2Methods_mapfun map, 
                 void (*transform)(Pnm_ppm, A2Methods_mapfun)
                 FILE *timerFile) 
{
        /* Start the Timer */
        CPU_Time timer = NULL;
        if (timerFile != NULL) {
                timer = CPUTime_new();
                CPUTime_Start(timer);
        }

        /* Run the operation */
        transform(image, map);       

        /* Stop the timer */
        if (timerFile != NULL) {
                double time = CPUTime_Stop(timer);
                CPUTime_free(timer);

                A2Methods_T methods = ppm -> methods;
                A2_UArray2  image   = ppm -> pixels;
                int numPixels = methods -> width(image) * 
                                methods -> height(image);
                
                fprintf(timerFile, "Timing: %.0f, Time per pixel: %.0f / px", 
                        time, time / numPixels);
        }
}