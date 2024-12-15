#define TAPE_SIZE 30000
#include <stdio.h>
#include <stdlib.h>

char tape[TAPE_SIZE] = {0};
int cptr = 0;
int mptr = 0;

void interpret(char *code, int length) {
  while (cptr < length) {
    if (mptr < 0 || mptr >= TAPE_SIZE) {
      printf("bad mptr\n");
      return;
    }
    switch (code[cptr]) {
    case '>':
      mptr++;
      break;
    case '<':
      mptr--;
      break;
    case '+':
      tape[mptr]++;
      break;
    case '-':
      if (tape[mptr] <= 0) {
        break;
      }
      tape[mptr]--;
      break;
    case ',':
      tape[mptr] = getchar();
      break;
    case '.':
      printf("%c", tape[mptr]);
      break;
    case '[':
      if (tape[mptr] == 0) {
        int nest = 1;
        while (nest > 0) {
          cptr++;
          if (code[cptr] == '[') {
            nest++;
          } else if (code[cptr] == ']') {
            nest--;
          }
        }
      }
      break;
    case ']':
      if (tape[mptr] != 0) {
        int nest = 1;
        while (nest > 0) {
          cptr--;
          if (code[cptr] == ']') {
            nest++;
          } else if (code[cptr] == '[') {
            nest--;
          }
        }
      }
      break;
    }

    cptr++;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("expected bf file\n");
    return 1;
  }

  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("file not found");
    return 1;
  }

  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  rewind(fp);

  char *buf = malloc(fsize + 1); // +1 for null terminator
  if (buf == NULL) {
    perror("malloc failed");
    fclose(fp);
    return 1;
  }
  size_t bytesRead = fread(buf, 1, fsize, fp);
  buf[bytesRead] = '\0';

  interpret(buf, bytesRead);

  free(buf);
  fclose(fp);
  return 0;
}
