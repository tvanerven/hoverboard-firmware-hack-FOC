#include "config.h"

#pragma once
#include <stdint.h>

typedef struct {
  int16_t   raw;    // raw input
  int16_t   cmd;    // command
  uint8_t   typ;    // type
  uint8_t   typDef; // type Defined
  int16_t   min;    // minimum
  int16_t   mid;    // middle
  int16_t   max;    // maximum
  int16_t   dband;  // deadband
} InputStruct;

void calcInputCmd(InputStruct *in, int16_t out_min, int16_t out_max);
int  checkInputType(int16_t min, int16_t mid, int16_t max);


typedef struct{
      uint8_t  start;
      uint8_t  type; 
      uint8_t  channels[IBUS_NUM_CHANNELS*2];
      uint8_t  checksuml;
      uint8_t  checksumh;
} SerialCommand;

