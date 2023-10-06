#include <pnm.h>
#include <a2methods.h>
#include <stdio.h>

#ifndef _IMAGE_MAPPER_H_
#define _IMAGE_MAPPER_H_

void imageMapper(Pnm_ppm image, A2Methods_mapfun map, 
                 void (*transform)(Pnm_ppm, A2Methods_mapfun)
                 FILE *timerFile);

#endif