
# Very small host-side unit test build
CC ?= gcc
CSTD ?= c11
CFLAGS ?= -Wall -Wextra  -std=$(CSTD) -O0 -g

# Project roots
PROJ_ROOT := ..
SRC_DIR   := $(PROJ_ROOT)/Src
INC_DIR   := $(PROJ_ROOT)/Inc
STUBS_DIR := ./stubs

# All test sources
TEST_SRCS := $(wildcard test_*.c)

# Under-test sources (add more .c here as you add tests)
UT_SRCS   := ut_check_input_type.c ut_calc_input_cmd.c ut_ibus_decode.c ut_crsf_decode.c

# Include paths: stubs FIRST so they shadow real HAL headers
INCLUDES  := -I$(STUBS_DIR) -I$(INC_DIR)

# Single test runner binary
OUT := run_tests

all: $(OUT)
	@./$(OUT)

$(OUT): runner.c $(TEST_SRCS) $(UT_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

clean:
	rm -f $(OUT) *.o

.PHONY: all clean

CFLAGS += -DVARIANT_USART
