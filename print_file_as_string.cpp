#include <stdio.h>

int main(int argc, char *argv[]) {

  FILE *fp;

  fp = fopen(argv[1], "r");
  while (!feof(fp)) {
    int c = fgetc(fp);
    if (c == -1)
      break;
    printf("\\x%02x", c);
  }
  fclose(fp);

}

