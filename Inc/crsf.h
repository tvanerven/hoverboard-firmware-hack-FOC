// Inc/crsf.h
#pragma once
#include <stdint.h>

#define CRSF_SYNC_BYTE      0xC8
#define CRSF_TYPE_RC_CHANNELS 0x16
#define CRSF_MAX_PAYLOAD    32

typedef struct {
  uint8_t addr;     // 0xC8
  uint8_t len;
  uint8_t type;     // 0x16
  uint8_t payload[CRSF_MAX_PAYLOAD]; // 16ch packed @11 bits (22 bytes)
  uint8_t crc;
} crsf_frame_t;

int crsf_feed_byte(uint8_t b); // returns 1 when a full valid RC frame is ready
int crsf_read_channels(uint16_t out_ch[16]); // fills 0..15 with 988..2012