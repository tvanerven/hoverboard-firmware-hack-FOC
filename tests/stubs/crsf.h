
#pragma once
#include <stdint.h>

// Minimal CRSF framing for "RC channels packed" packet
// Frame layout: [ADDR][LEN][TYPE][PAYLOAD (22 bytes)][CRC]
// - ADDR is typically 0xC8 (Radio Transmitter -> Flight Controller)
// - LEN = TYPE(1) + PAYLOAD(22) + CRC(1) = 24
// - TYPE for channels is 0x16
// - Payload packs 16x 11-bit channel values little-endian across 22 bytes
// - CRC8 is computed over TYPE+PAYLOAD using poly 0xD5, init 0x00.

#define CRSF_ADDR_RADIO           0xC8
#define CRSF_TYPE_CHANNELS        0x16
#define CRSF_NUM_CHANNELS         16
#define CRSF_PAYLOAD_LEN          22
#define CRSF_LEN_FIELD_VALUE      (1 /*type*/ + CRSF_PAYLOAD_LEN + 1 /*crc*/)

