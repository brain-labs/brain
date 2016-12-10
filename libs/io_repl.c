#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// you can overwrite those functions! :)

void b_putchar(int idx, int *cells);

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\033[01;33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void b_getchar(int idx, int *cells) {
  struct termios old,new;
  tcgetattr(fileno(stdin),&old);
  new = old;
  cfmakeraw(&new);
  new.c_iflag &= ~(ICRNL);
  new.c_iflag &= IGNCR ^ -1;
  new.c_lflag &= ~(ECHO | ECHONL | ECHOE | ICANON);
  tcsetattr(fileno(stdin),TCSANOW,&new);
  fflush(NULL);
  int c = fgetc(stdin);
  tcsetattr(fileno(stdin),TCSANOW,&old);

  char *color;
  switch (c)
  {
    case '<':
    case '>':
    case '^':
      color = KMAG;
    break;
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
      color = KGRN;
    break;
    case '.':
    case ',':
    case '#':
      color = KCYN;
    break;
    case '?':
    case ':':
    case ';':
    case '!':
      color = KYEL;
    break;
    case '[':
    case ']':
    case '{':
    case '}':
      color = KBLU;
    break;
    case ' ':
      putchar(' ');
      cells[idx] = c;
      return;
    case  13:
    case 'q':
    case 'r':
    case '\n':
      putchar('\n');
      cells[idx] = c;
      return;
    case 0x7f:
      putchar('\b');
      putchar(' ');
      putchar('\b');
      cells[idx] = c;
      return;
    default:
      return;
  }

  cells[idx] = c;
  printf("%s%c%s", color, c, KNRM);
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
