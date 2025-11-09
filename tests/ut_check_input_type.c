
#include <stdint.h>
#include <stdio.h>

// minimal stubs for optional branches
static inline void beepLong(int n){ (void)n; }

int checkInputType(int16_t min, int16_t mid, int16_t max){

  int type = 0;  
  // Thresholds copied from util.c; CONTROL_ADC branch omitted in tests
  int16_t threshold = 200;

  if ((min / threshold) == (max / threshold) || (mid / threshold) == (max / threshold) || min > max || mid > max) {
    type = 0;
  } else {
    if ((min / threshold) == (mid / threshold)){
      type = 1;
    } else {
      type = 2;
    }
  }

  return type;
}
