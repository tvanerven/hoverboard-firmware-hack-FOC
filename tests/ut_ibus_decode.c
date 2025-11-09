
#include <stdint.h>
#include <string.h>
#include "config.h"
#include "util.h"

int ibus_validate_and_copy(const SerialCommand* in, SerialCommand* out){
    if (in->start != IBUS_LENGTH || in->type != IBUS_COMMAND) return 0;
    uint16_t sum = 0xFFFF - IBUS_LENGTH - IBUS_COMMAND;
    for (uint8_t i = 0; i < (IBUS_NUM_CHANNELS * 2); i++) {
        sum -= in->channels[i];
    }
    uint16_t chk = (uint16_t)((in->checksumh << 8) | in->checksuml);
    if (sum != chk) return 0;
    *out = *in;
    return 1;
}
