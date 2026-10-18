/* test/bench/avr/core_progmem.c
   Stand-in for the Arduino core's own PROGMEM tables, linked LAST like core.a.

   The mirrored hazard: the core reads its pin tables through 16-bit pointers —
   `pgm_read_byte(&digital_pin_to_port_PGM[pin])` in wiring_digital.c — which
   reach only the first 64 KiB of Flash. avr-libc's linker script puts the
   progmem cluster (`*(.progmem.gcc*)` / `*(.progmem*)`) at the START of .text in
   link order, and the Arduino recipe puts core.a last, so any PROGMEM library
   linked before it pushes the core's tables up. Once they sit above 0xFFFF the
   truncated pointer reads a wrong address: pinMode/digitalWrite drive the wrong
   port.

   autoresearch.sh links this object after the library objects and gates that
   `core_probe_pin_to_port_PGM` stays inside the 16-bit window. It is kept by
   `-Wl,--undefined=core_probe_read_pin`, the reason the core's copy survives
   --gc-sections: the core's own code calls it.

   Only the addressing width matters here, so this is deliberately a small
   table, not the real pins_arduino.h layout. */

#include <avr/pgmspace.h>
#include <stdint.h>

// cppcheck sees no avr/pgmspace.h (it is not on its include path), so PROGMEM
// and pgm_read_byte read as unknown names — the same macros the core uses.
// cppcheck-suppress unknownMacro
const uint8_t core_probe_pin_to_port_PGM[16] PROGMEM = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
};

uint8_t core_probe_read_pin(uint8_t pin) {
    return pgm_read_byte(&core_probe_pin_to_port_PGM[pin & 15u]);
}
