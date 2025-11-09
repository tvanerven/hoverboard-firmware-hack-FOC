
#include <stdint.h>
#include "util.h"

#define MAP(x, in_min, in_max, out_min, out_max) \
  (((((x) - (in_min)) * ((out_max) - (out_min))) / ((in_max) - (in_min))) + (out_min))

#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

void calcInputCmd(InputStruct *in, int16_t out_min, int16_t out_max) {
  switch (in->typ){
    case 1: // Input is a normal pot
      in->cmd = CLAMP(MAP(in->raw, in->min, in->max, 0, out_max), 0, out_max);
      break;
    case 2: // Input is a mid resting pot
      if( in->raw > in->mid - in->dband && in->raw < in->mid + in->dband ) {
        in->cmd = 0;
      } else if(in->raw > in->mid) {
        in->cmd = CLAMP(MAP(in->raw, in->mid + in->dband, in->max, 0, out_max), 0, out_max);
      } else {
        in->cmd = CLAMP(MAP(in->raw, in->mid - in->dband, in->min, 0, out_min), out_min, 0);
      }
      break;
    default: // Input is ignored
      in->cmd = 0;
      break;
  }
}
