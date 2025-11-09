
#include <stdint.h>
#include <string.h>
#include "crsf.h"

// CRC8 using polynomial 0xD5, init 0x00 (CRSF standard)
static uint8_t crc8_d5(const uint8_t* data, uint8_t len){
    uint8_t crc = 0x00;
    for (uint8_t i=0;i<len;i++){
        crc ^= data[i];
        for (uint8_t b=0;b<8;b++){
            if (crc & 0x80) crc = (crc << 1) ^ 0xD5;
            else            crc <<= 1;
        }
    }
    return crc;
}

// Unpack 16 x 11-bit values from 22-byte payload (little-endian bit packing)
static void unpack_11bit_16ch(const uint8_t payload[CRSF_PAYLOAD_LEN], uint16_t out[CRSF_NUM_CHANNELS]){
    uint32_t bitpos = 0;
    for (int ch=0; ch<CRSF_NUM_CHANNELS; ch++){
        uint32_t byte_index = bitpos >> 3;
        uint32_t bit_offset = bitpos & 7;
        // read 16 bits window to extract 11 bits
        uint32_t v =  payload[byte_index]
                    | ((uint32_t)payload[byte_index+1] << 8)
                    | ((uint32_t)payload[byte_index+2] << 16);
        v >>= bit_offset;
        out[ch] = (uint16_t)(v & 0x7FFu);
        bitpos += 11;
    }
}

// Return 1 on success; 0 on reject.
// buf must contain exactly [0]=addr,[1]=len,[2]=type,[3..24]=payload(22),[25]=crc
int crsf_decode_channels(const uint8_t* buf, uint16_t len, uint16_t out_channels[CRSF_NUM_CHANNELS]){
    if (len < 2 + 1 + CRSF_PAYLOAD_LEN + 1) return 0;
    if (buf[0] != CRSF_ADDR_RADIO) return 0;
    if (buf[1] != CRSF_LEN_FIELD_VALUE) return 0;
    if (buf[2] != CRSF_TYPE_CHANNELS) return 0;
    uint8_t crc = crc8_d5(&buf[2], 1 + CRSF_PAYLOAD_LEN);
    if (crc != buf[2 + 1 + CRSF_PAYLOAD_LEN]) return 0; // position of CRC
    unpack_11bit_16ch(&buf[3], out_channels);
    return 1;
}

// Helpers exposed for tests
uint8_t crsf_crc8_compute(const uint8_t* data, uint8_t len){ return crc8_d5(data, len); }
