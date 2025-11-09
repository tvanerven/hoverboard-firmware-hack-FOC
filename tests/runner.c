
#include <stdio.h>
#include <stdlib.h>

// Prototypes from test files
void test_check_input_type_normal_pot();
void test_check_input_type_mid_rest();
void test_check_input_type_invalid_close_values();

void test_normal_pot_linear_scale();
void test_normal_pot_clamp_low_high();
void test_mid_rest_deadband_zero();
void test_mid_rest_forward_and_reverse();
void test_default_type_ignored();

int main(void){
    // run all tests
    test_check_input_type_normal_pot();
    test_check_input_type_mid_rest();
    test_check_input_type_invalid_close_values();

    test_normal_pot_linear_scale();
    test_normal_pot_clamp_low_high();
    test_mid_rest_deadband_zero();
    test_mid_rest_forward_and_reverse();
    test_default_type_ignored();

    test_ibus_entry();
    test_crsf_entry();
    puts("[OK] All tests passed.");
    return 0;
}
