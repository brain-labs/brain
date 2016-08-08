#include <stdio.h>

// you can overwrite those functions! :)

void b_getchar(int idx, int *cells) {
  cells[idx] = getchar();
}

void b_putchar(int idx, int *cells) { 
  putchar(cells[idx]);
}

void b_float_print(int idx, int *cells) {
    float value = cells[idx] / 100.0;
    printf("%.2f", value);
}

void b_debug(int idx, int *cells) {
  printf(
    "Index Pointer: %d Value at Index Pointer: %d\n",
    idx,
    cells[idx]
  );
}

