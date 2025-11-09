
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "crsf.h"

int crsf_decode_channels(const uint8_t* buf, uint16_t len, uint16_t out_channels[CRSF_NUM_CHANNELS]);
uint8_t crsf_crc8_compute(const uint8_t* data, uint8_t len);

// Pack 16x11-bit into 22-byte payload
static void pack_11bit_16ch(const uint16_t in[CRSF_NUM_CHANNELS], uint8_t payload[CRSF_PAYLOAD_LEN]){
    memset(payload, 0, CRSF_PAYLOAD_LEN);
    uint32_t bitpos = 0;
    for (int ch=0; ch<CRSF_NUM_CHANNELS; ch++){
        uint32_t byte_index = bitpos >> 3;
        uint32_t bit_offset = bitpos & 7;
        uint32_t v = (uint32_t)(in[ch] & 0x7FFu) << bit_offset;
        payload[byte_index]     |= (uint8_t)(v & 0xFFu);
        payload[byte_index+1]   |= (uint8_t)((v >> 8) & 0xFFu);
        if (bit_offset >= 6) { // may spill into the third byte
            payload[byte_index+2] |= (uint8_t)((v >> 16) & 0xFFu);
        }
        bitpos += 11;
    }
}

static void build_crsf_frame(const uint16_t ch[CRSF_NUM_CHANNELS], uint8_t out[2 + 1 + CRSF_PAYLOAD_LEN + 1]){
    out[0] = CRSF_ADDR_RADIO;
    out[1] = CRSF_LEN_FIELD_VALUE;
    out[2] = CRSF_TYPE_CHANNELS;
    pack_11bit_16ch(ch, &out[3]);
    out[2 + 1 + CRSF_PAYLOAD_LEN] = crsf_crc8_compute(&out[2], 1 + CRSF_PAYLOAD_LEN);
}

void test_crsf_valid_packet(){
    uint16_t ch[CRSF_NUM_CHANNELS] = {
        172, 992, 1500, 1811, // edge-ish values typical for CRSF (11-bit)
        500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600
    };
    uint8_t frame[2 + 1 + CRSF_PAYLOAD_LEN + 1];
    uint16_t out[CRSF_NUM_CHANNELS];
    build_crsf_frame(ch, frame);
    int ok = crsf_decode_channels(frame, sizeof(frame), out);
    assert(ok==1);
    for(int i=0;i<CRSF_NUM_CHANNELS;i++){
        assert(out[i] == (ch[i] & 0x7FF));
    }
}

void test_crsf_crc_rejects(){
    uint16_t ch[CRSF_NUM_CHANNELS] = { 1000 };
    uint8_t frame[2 + 1 + CRSF_PAYLOAD_LEN + 1];
    uint16_t out[CRSF_NUM_CHANNELS];
    build_crsf_frame(ch, frame);
    // corrupt one payload byte
    frame[4] ^= 0x55;
    int ok = crsf_decode_channels(frame, sizeof(frame), out);
    assert(ok==0);
}

void test_crsf_addr_len_type_checks(){
    uint16_t ch[CRSF_NUM_CHANNELS] = { 1000 };
    uint8_t frame[2 + 1 + CRSF_PAYLOAD_LEN + 1];
    uint16_t out[CRSF_NUM_CHANNELS];
    build_crsf_frame(ch, frame);
    frame[0] ^= 1; // bad address
    assert(crsf_decode_channels(frame, sizeof(frame), out)==0);
    build_crsf_frame(ch, frame);
    frame[1] ^= 1; // bad length
    assert(crsf_decode_channels(frame, sizeof(frame), out)==0);
    build_crsf_frame(ch, frame);
    frame[2] ^= 1; // bad type
    assert(crsf_decode_channels(frame, sizeof(frame), out)==0);
}

// test entry hook for runner
void test_crsf_entry(void){
    test_crsf_valid_packet();
    test_crsf_crc_rejects();
    test_crsf_addr_len_type_checks();
    puts("[OK] CRSF decode tests");
}
