#ifndef IO_H
#define IO_H

// This module interfaces towards the IO pins of the microcontroller

typedef enum
{
    IO_LED1,
    IO_LED2,
    IO_LED3,
} io_e;

typedef enum
{
    IO_SELECT_GPIO,
    IO_SELECT_ALT1,
    IO_SELECT_ALT2,
    IO_SELECT_ALT3,
} io_select_e;

typedef enum
{
    IO_DIRECTION_OUTPUT,
    IO_DIRECTION_INPUT,
} io_direction_e;

typedef enum
{
    IO_RESISTOR_DISABLED,
    IO_RESISTOR_ENABLED,
} io_resistor_e;

typedef enum
{
    IO_OUT_LOW,  // Pull-down
    IO_OUT_HIGH, // Pull-up
} io_out_e;

typedef enum
{
    IO_INPUT_LOW,
    IO_INPUT_HIGH,
} io_input_e;

// Sets the select value for the given IO.
void io_set_select(io_e io, io_select_e io_select);

// Sets the direction for the given IO.
void io_set_direction(io_e io, io_direction_e io_select);

// Sets the resistor mode for the given IO.
void io_set_resistor(io_e io, io_resistor_e io_resistor);

// Sets the output level for the given IO.
void io_set_out(io_e io, io_out_e io_out);

// Gets the input level for the given IO:
io_input_e io_get_input(io_e);

#endif // IO_H