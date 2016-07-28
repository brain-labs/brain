#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <stdbool.h>

#define RED_COLOR "\e[91m"
#define GREEN_COLOR "\e[92m"
#define END_COLOR "\e[0m"

static int returnValue = 0;

bool hasExt(char *ext);
char* callocString(int size);
void appendExtToFile(char *dest, char *source, char *ext);
void compareFiles(char *filename1, char *filename2);
void execToFile(char *options, char *destFile);

int main()
{
  char *execProg = "brain";

  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      char *ext = strrchr(dir->d_name, '.');
      if (hasExt(ext)) {
        char *fWithNoExt = callocString(strlen(dir->d_name));
        strncpy(fWithNoExt, dir->d_name, ext - dir->d_name);

        char *fCmp = callocString(strlen(dir->d_name) + 5);
        appendExtToFile(fCmp, fWithNoExt, ".cmp");
        execToFile(dir->d_name, fWithNoExt);
        compareFiles(fCmp, fWithNoExt);

        // does not compare InputExpr for 0O and O1
        if (strncmp(dir->d_name, "read", 4) == 0) {
          continue;
        }

        char *fCmp0 = callocString(strlen(dir->d_name) + 5);
        appendExtToFile(fCmp0, fWithNoExt, ".cmp0");
        char *options = callocString(strlen(dir->d_name) + strlen(" -O0 -emit-ast") + 1);
        strcat(options, dir->d_name);
        strcat(options, " -O0 -emit-ast");
        execToFile(options, fWithNoExt);
        compareFiles(fCmp0, fWithNoExt);
        free(options);

        char *fCmp1 = callocString(strlen(dir->d_name) + 5);
        appendExtToFile(fCmp1, fWithNoExt, ".cmp1");
	options = callocString(strlen(dir->d_name) + strlen(" -O1 -emit-ast") + 1);
        strcat(options, dir->d_name);
        strcat(options, " -O1 -emit-ast");
        execToFile(options, fWithNoExt);
        compareFiles(fCmp1, fWithNoExt);
        free(options);

	printf("====================\n");

        free(fWithNoExt);
        free(fCmp);
        free(fCmp0);
        free(fCmp1);
      }
    }

    closedir(d);
  }

  return returnValue;
}

bool hasExt(char *ext)
{
  return ext && (strcmp(ext, ".b") == 0 || 
                 strcmp(ext, ".br") == 0 || 
                 strcmp(ext, ".brain") == 0); 
}

char* callocString(int size)
{
  return calloc(size, sizeof(char));
}

void appendExtToFile(char *dest, char *source, char *ext)
{
  strcat(dest, source);
  strcat(dest, ext);
}

void compareFiles(char *filename1, char *filename2)
{
  FILE *f1 = fopen(filename1, "r");
  FILE *f2 = fopen(filename2, "r");
  if (!f1 || !f2 )
  {
    printf("%simpossible to open file %s or %s%s\n", \
                                          RED_COLOR, \
                                          filename1, \
                                          filename2, \
                                          END_COLOR);
    returnValue = 1;
    return;
  }
    
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
  {
    printf("%sfile %s does not match !%s\n", \
                                  RED_COLOR, \
                                  filename1, \
                                  END_COLOR);
    returnValue = 1;
    return;
  }

  printf("%sfile %s passed !%s\n", \
                      GREEN_COLOR, \
                        filename1, \
                        END_COLOR);
}

void execToFile(char *options, char *destFile)
{
  int sizeCmd = strlen("brain") + strlen(options) + strlen(destFile) + 5; 
  char *cmd = callocString(sizeCmd);
  // ex: brain loopinc.b > loopinc
  snprintf(cmd, sizeCmd, "brain %s > %s", options, destFile);   

  if (system(cmd) != 0)
  {
    printf("%simpossible to run command %s %s\n", \
                                       RED_COLOR, \
                                             cmd, \
                                       END_COLOR);
    free(cmd);
    returnValue = 1;
    return;
  }

  printf("%s%s%s\n", GREEN_COLOR, cmd, END_COLOR);
  free(cmd); 
}

