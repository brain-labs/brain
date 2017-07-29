#include <stdio.h>

// you can overwrite those functions! :)

void b_getchar(int idx, int *cells, int size) {
  cells[idx] = getchar();
}

void b_putchar(int idx, int *cells, int size) {
  putchar(cells[idx]);
}

void b_float_print(int idx, int *cells, int size) {
    float value = cells[idx] / 100.0;
    printf("%.2f", value);
}

void b_debug(int idx, int *cells, int size) {
  printf(
    "Index Pointer: %d Value at Index Pointer: %d\n",
    idx,
    cells[idx]
  );
}

