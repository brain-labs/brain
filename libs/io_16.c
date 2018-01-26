// -------------- 16 bits

#include <stdio.h>

// you can overwrite those functions! :)

void b_getchar_16(short idx, short *cells, int size) {
    cells[idx] = (short)getchar();
}

void b_putchar_16(short idx, short *cells, int size) {
    putchar((int)cells[idx]);
}

void b_float_print_16(short idx, short *cells, int size) {
    float value = cells[idx] / 100.0;
    printf("%.2f", value);
}

void b_debug_16(short idx, short *cells, int size) {
    printf(
      "Index Pointer: %d Value at Index Pointer: %d\n",
      idx,
      cells[idx]
    );
}
