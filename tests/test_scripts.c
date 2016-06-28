#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5 

int main()
{
  char *execProg = "brain";
  char *files[MAX];

  files[0] = "helloworld";
  files[1] = "loopinc";
  files[2] = "hellbox";
  files[3] = "ifelse";
  files[4] = "else";

  int i = 0;
  for(i = 0; i < MAX; i++)
  {
    int sizeBFileName = strlen(files[i]) + 3;
    char *bFileName = (char *) malloc(sizeof(char) * sizeBFileName);
    strncpy(bFileName, files[i], sizeBFileName);
    strncat(bFileName, ".b", 2);

    int sizeCmpFileName = strlen(files[i]) + 5;
    char *cmpFileName = (char *) malloc(sizeof(char) * sizeCmpFileName);
    strncpy(cmpFileName, files[i], sizeCmpFileName - 5);
    strncat(cmpFileName, ".cmp", 4);

    int sizeCmd = strlen(execProg) + sizeBFileName + strlen(files[i]) + 4; 
    char *cmd = (char *) malloc(sizeof(char) * sizeCmd);
    // brain loopinc.b > loopinc
    snprintf(cmd, sizeCmd, "brain %s > %s", bFileName, files[i]);   

    if (system(cmd) != 0)
      return -2; 

    FILE *f1 = fopen(files[i], "r");
    FILE *f2 = fopen(cmpFileName, "r");
    if (!f1 || !f2 )
      return 1;
    
    int ch1 = getc(f1);
    int ch2 = getc(f2);
 
    while (((ch1 != EOF) || (ch2 != EOF)) && (ch1 == ch2)) 
    {
      ch1 = getc(f1);
      ch2 = getc(f2);
    }

    fclose(f1);
    fclose(f2);

    if (ch1 != ch2)
      return 2;

    printf("%s = OK\n", cmd);

    free(cmpFileName);
    free(bFileName);
    free(cmd);
  }

  printf("All tests are passing!\n");   

  return 0;
}

