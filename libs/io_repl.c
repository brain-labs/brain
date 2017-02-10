#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// you can overwrite those functions! :)

void b_help();
void b_conditions();
void b_putchar(int idx, int *cells);

#define DEL 0x7f

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
    case DEL:
      putchar('\b');
      putchar(' ');
      putchar('\b');
      cells[idx] = c;
      return;
    case  13:
    case '\n':
      putchar('\n');
      cells[idx] = c;
      return;
    case 'h':
      b_help(); // fallthrough
    case 'c':
      b_conditions(); // fallthrough
    default:
      cells[idx] = c;
      return;
  }

  cells[idx] = c;
  printf("%s%c%s", color, c, KNRM);
}

void b_putchar(int idx, int *cells) {
  putchar(cells[idx]);
}

void b_float_print(int idx, int *cells) {
//  float value = cells[idx] / 100.0;
//  printf("%.2f", value);
printf(
    "Index Pointer: %d Value at Index Pointer: %d\n",
    idx,
    cells[idx]
  );
}

void b_debug(int idx, int *cells) {
  /* overriding the debug 
   * in order to minimize the size
   * the final repl size.
   */
  printf("Brain · Copyright (C) 2016 Brain Labs\n\
This program comes with ABSOLUTELY NO WARRANTY.\n\
Type 'h' for help\n\
Type 'c' for conditions\n\
Type 'q' for quitting\n");
}

void b_help()
{
printf(">\tIncrement the data pointer\n\
<\tdecrement the data pointer\n\
+\tincrement the value at the data pointer\n\
-\tdecrement the value at the data pointer\n\
.\toutput the value at the data pointer\n\
,\tread input and store it data pointer value\n\
[\texecute its inner block of code if the value at the data pointer is != 0\n\
]\tjump to its correspondent [\n\
*\tmultiply *ptr with *(ptr-1) and store result in *ptr\n\
/\tdivide *ptr with *(ptr-1) and store the result in *ptr\n\
%%\tdivide *ptr with *(ptr-1) and store the remainder in *ptr\n\
#\tprints out the current debug information\n\
{\tfor loop - iterates 'value-at-the-data-pointer' times\n\
}\tjump to its correspondent '{'\n\
!\tbreak - jumps to the end of a loop ('[' ']' or '{' '}')\n\
?\tif the value at the data pointer is zero, jumps to the block with ':' or ';' and executes the commands one by one up to its correlative ';', otherwise, it executes the code until it finds a ':' or ';'\n\
:\tit works as an 'otherwise' (or 'else') for '?'\n\
;\tends a statement\t\
$\tprints out the value at the data pointer **divided** by 100\n\
^\tmove the data pointer (jump) on the tape\n");   
}

void b_conditions()
{
  printf("\nSoftware conditions: https://github.com/brain-labs/brain/blob/master/LICENSE\n");
}
