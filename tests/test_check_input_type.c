
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

// pull prototype from util.c via Inc/util.h
#include "stm32f1xx_hal.h"
#include "util.h"

// The function lives in util.c; we link that file directly via Makefile.
// We don't define CONTROL_ADC here, so the protection/beep branch is skipped.

void test_check_input_type_normal_pot() {
    // min ~= mid << max -> type 1 ("normal pot")
    int t = checkInputType(100, 150, 3000);
    assert(t == 1);
}

void test_check_input_type_mid_rest() {
    // min far from mid, both far from max -> type 2 ("mid-resting pot")
    int t = checkInputType(100, 2000, 3500);
    assert(t == 2);
}

void test_check_input_type_invalid_close_values() {
    // Values too close or inconsistent -> type 0 (ignored)
    int t1 = checkInputType(3800, 3900, 3905);
    assert(t1 == 0);
    int t2 = checkInputType(3000, 4000, 3500); // min>max or mid>max
    assert(t2 == 0);
}

