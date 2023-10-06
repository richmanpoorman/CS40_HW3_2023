#include <pnm.h>
#include <a2methods.h>


#ifndef _IMAGE_TRANSFORMS_H_
#define _IMAGE_TRANSFORMS_H_

void rotate0(Pnm_ppm ppm, A2Methods_mapfun map);
void rotate90(Pnm_ppm ppm, A2Methods_mapfun map);
void rotate180(Pnm_ppm ppm, A2Methods_mapfun map);
void rotate270(Pnm_ppm ppm, A2Methods_mapfun map);
void flipHorizontal(Pnm_ppm ppm, A2Methods_mapfun map);
void flipVertical(Pnm_ppm ppm, A2Methods_mapfun map);
void transpose(Pnm_ppm ppm, A2Methods_mapfun map);

#endif