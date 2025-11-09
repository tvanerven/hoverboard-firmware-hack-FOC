
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "util.h"

int ibus_validate_and_copy(const SerialCommand* in, SerialCommand* out);

// helper to build a valid frame from 14 channels (each little-endian 1000..2000 typical)
static void build_frame(uint16_t ch[IBUS_NUM_CHANNELS], SerialCommand* s){
    memset(s, 0, sizeof(*s));
    s->start = IBUS_LENGTH;
    s->type  = IBUS_COMMAND;
    for (int i=0;i<IBUS_NUM_CHANNELS;i++){
        s->channels[2*i]   = (uint8_t)(ch[i] & 0xFF);
        s->channels[2*i+1] = (uint8_t)(ch[i] >> 8);
    }
    uint16_t sum = 0xFFFF - IBUS_LENGTH - IBUS_COMMAND;
    for (int i=0;i<IBUS_NUM_CHANNELS*2;i++) sum -= s->channels[i];
    s->checksuml = (uint8_t)(sum & 0xFF);
    s->checksumh = (uint8_t)(sum >> 8);
}

void test_ibus_valid_and_copy(){
    uint16_t ch[IBUS_NUM_CHANNELS] = {1500,1500,1000,2000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000};
    SerialCommand in, out;
    build_frame(ch, &in);
    int ok = ibus_validate_and_copy(&in, &out);
    assert(ok==1);
    // Verify channels were copied exactly
    assert(memcmp(&in, &out, sizeof(in))==0);
}

void test_ibus_checksum_rejects(){
    uint16_t ch[IBUS_NUM_CHANNELS] = {1000};
    SerialCommand in, out;
    build_frame(ch, &in);
    // Corrupt one byte
    in.channels[0] ^= 0x01;
    int ok = ibus_validate_and_copy(&in, &out);
    assert(ok==0);
}

void test_ibus_entry(void){
    test_ibus_valid_and_copy();
    test_ibus_checksum_rejects();
    puts("[OK] IBUS decode tests");
    return 0;
}
