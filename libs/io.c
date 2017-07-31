#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// you can overwrite those functions! :)

int number_size(int number) {
    return floor(log10(abs(number))) + 1 + (number > 0 ? 0 : 1);
}

void b_show_tape(int idx, int *cells, int size) {
    // TODO: ellipsize values based on index
    size = 12;
    char tape[255] = "[";
    int tape_idx = 1;
    int idx_position = 0;
    int idx_length = 0;
    bool found_idx = false;
    bool found_idx_length = false;
    int i = 0, j;

    while (i < size) {
        if (!found_idx && i == idx) {
            idx_position = tape_idx;
            found_idx = true;

            if (!*cells) {
                idx_length = 1;
                found_idx_length = true;
            }
        }

        tape[tape_idx++] = ' ';
        // Has a value allocated on register
        if (*cells) {
            unsigned int value_size = number_size(*cells);
            char number[value_size];
            sprintf(number, "%d", *cells);
            // Append each number character
            for (j = 0; j < value_size; j++) {
                tape[tape_idx++] = number[j];
            }

            if (found_idx && !found_idx_length) {
                idx_length = value_size;
                found_idx_length = true;
            }
        } else {
            tape[tape_idx++] = i == idx ? '0' : '_';
        }

        tape[tape_idx++] = ' ';
        // When not last, append separator
        if (i < size - 1) {
            tape[tape_idx++] = '|';
        }
        i++;
        cells++;
    }

    tape[tape_idx++] = ']';
    for (i = 0; i < tape_idx; i++) {
        putchar('-');
    }
    printf("\n%s\n", tape);
    // Print indicator on index position
    for (i = 0; i < idx_position; i++) {
        putchar(' ');
    }
    putchar('^');
    for (int i = 0; i <= idx_length; i++) {
        putchar('^');
    }
    putchar('\n');
    // Print index indicator as number
    for (i = 0; i < idx_position; i++) {
        putchar(' ');
    }
    printf("*(%d)\n", idx);
}

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
    b_show_tape(idx, cells, size);
}

