// Src/crsf.c (super-short sketch; implement proper CRC & packing in real code)
#include "crsf.h"

static crsf_frame_t f;
static uint8_t idx;

int crsf_feed_byte(uint8_t b) {
  // very rough state machine sketch – complete it for robustness
  if (idx == 0 && b != CRSF_SYNC_BYTE) return 0;
  ((uint8_t*)&f)[idx++] = b;
  if (idx == 2) { if (f.len > CRSF_MAX_PAYLOAD+2) idx = 0; } // sanity
  if (idx >= 2 && idx == f.len + 2) { // full frame: addr + len + len bytes (type+payload+crc)
    // TODO: verify CRC here
    int done = (f.type == CRSF_TYPE_RC_CHANNELS);
    idx = 0;
    return done;
  }
  return 0;
}

int crsf_read_channels(uint16_t out_ch[16]) {
  // unpack 16 x 11-bit channels from f.payload[0..21]
  const uint8_t *p = f.payload+1; // payload[0] is type already copied to f.type
  uint32_t bits = 0, acc = 0;
  int pi = 0, ci = 0;
  while (ci < 16) {
    while (bits < 11) { acc |= ((uint32_t)p[pi++]) << bits; bits += 8; }
    out_ch[ci++] = (acc & 0x7FF) + 988; // CRSF base is ~172..1811, map as needed
    acc >>= 11; bits -= 11;
  }
  return 1;
}
