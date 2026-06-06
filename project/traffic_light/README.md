# Traffic Light

A traffic light example based on STM32F103C8T6, using only PA pins.

## Implementation

- Uses custom `GPIOA_MOD` and `GPIOA_IO_BSRR` functions to control LEDs via 16-character strings.
- All code is currently in `main.c` (not yet split into separate library files).

## Functions

### `GPIOA_MOD(int PAx, int mod)`

Configures the mode of a PA pin.

- `mod = 0`: floating input (high impedance)
- `mod = 1`: push-pull output

### `GPIOA_IO_BSRR(char lights[17])`

Controls PA0–PA15 levels using a 16-character string.

- `'1'`: sets the corresponding pin to **HIGH**
- `'0'`: sets the corresponding pin to **LOW**
- Only the first 16 characters are used; the 17th is for the null terminator.

## Hardware Connection

- PA0: Red LED (active low)
- PA1: Yellow LED (active low)
- PA2: Green LED (active low)
- LED anode → 3.3V, cathode → GPIO pin

## State Machine

Red ON (5s) → Yellow blinks (3 times) → Green ON (5s) → Yellow blinks (3 times) → loop

## Note

This project is for learning STM32 register-level programming. No HAL libraries are used.
