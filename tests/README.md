# Unit test scaffold

This `tests/` folder adds a tiny, host‑buildable unit test harness for selected logic in the firmware, without flashing hardware.

## Quick start (Linux/macOS)

```sh
cd tests
make           # builds and runs all tests
```

## What this is

- **No external libs required** (no Unity/CMocka yet). It uses plain C + `assert` and a few **stubs** for HAL‑level headers.
- Starts with one test file: `test_check_input_type.c`, covering `checkInputType()` from `Src/util.c`.
- You can add more tests by dropping `test_*.c` files here; they are picked up automatically by the Makefile.
- The stubs in `tests/stubs/` shadow embedded headers so the code compiles on your host compiler.

## Add more tests

1. Create a new `test_*.c` in this folder.
2. Include the function prototypes you need from `Inc/` (or declare `extern` if needed).
3. If the file under test includes HAL or board headers, add minimal shims to `tests/stubs/`.

## Switch to a full framework later

Once we agree on scope, we can swap this out for **Unity + fff** or **cmocka**, and/or add `CMakeLists.txt` if you prefer CMake.
