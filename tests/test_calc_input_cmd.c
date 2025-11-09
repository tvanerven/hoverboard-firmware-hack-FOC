
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "util.h"

void test_normal_pot_linear_scale() {
    InputStruct in = {.raw=1500, .typ=1, .min=1000, .max=2000};
    calcInputCmd(&in, -1000, 1000);
    // raw is 50% of range -> cmd ~ 500 (half of 0..1000), clamped
    assert(in.cmd == 500);
}

void test_normal_pot_clamp_low_high() {
    InputStruct in = {.raw=500, .typ=1, .min=1000, .max=2000};
    calcInputCmd(&in, -1000, 1000);
    assert(in.cmd == 0); // below min clamps to 0

    in.raw = 2500;
    calcInputCmd(&in, -1000, 1000);
    assert(in.cmd == 1000); // above max clamps to 1000
}

void test_mid_rest_deadband_zero() {
    InputStruct in = {.typ=2, .min=1000, .mid=2000, .max=3000, .dband=50};
    in.raw = 1990; // within deadband
    calcInputCmd(&in, -1000, 1000);
    assert(in.cmd == 0);
    in.raw = 2010; // within deadband
    calcInputCmd(&in, -1000, 1000);
    assert(in.cmd == 0);
}

void test_mid_rest_forward_and_reverse() {
    InputStruct in = {.typ=2, .min=1000, .mid=2000, .max=3000, .dband=0};

    // Forward side (raw>mid): 2500 maps from [mid..max] to [0..1000] => 500
    in.raw = 2500;
    calcInputCmd(&in, -1000, 1000);
    assert(in.cmd == 500);

    // Reverse side (raw<mid): 1500 maps from [mid..min] to [0..-1000] => -500
    in.raw = 1500;
    calcInputCmd(&in, -1000, 1000);
    assert(in.cmd == -500);
}

void test_default_type_ignored() {
    InputStruct in = {.typ=0, .raw=1234};
    calcInputCmd(&in, -1000, 1000);
    assert(in.cmd == 0);
}

