// -------------- 64 bits

#include <stdio.h>

// you can overwrite those functions! :)

void b_getchar_64(long idx, long *cells, int size) {
    cells[idx] = (long)getchar();
}

void b_putchar_64(long idx, long *cells, int size) {
    putchar((int)cells[idx]);
}

void b_float_print_64(long idx, long *cells, int size) {
    float value = cells[idx] / 100.0;
    printf("%.2f", value);
}

void b_debug_64(long idx, long *cells, int size) {
    printf(
      "Index Pointer: %ld Value at Index Pointer: %ld\n",
      idx,
      cells[idx]
    );
}
