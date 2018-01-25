// -------------- 8 bits

#include <stdio.h>

// you can overwrite those functions! :)

void b_getchar_8(char idx, char *cells, int size) {
    cells[idx] = (char)getchar();
}

void b_putchar_8(char idx, char *cells, int size) {
    putchar((int)cells[idx]);
}

void b_float_print_8(char idx, char *cells, int size) {
    float value = cells[idx] / 100.0;
    printf("%.2f", value);
}

void b_debug_8(char idx, char *cells, int size) {
    printf(
      "Index Pointer: %d Value at Index Pointer: %d\n",
      idx,
      cells[idx]
    );
}
