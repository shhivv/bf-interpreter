#define TAPE_SIZE 30000
#include <stdio.h>
#include <stdlib.h>

char tape[TAPE_SIZE];
int cptr = 0;
int mptr = 0;

void interpret(char* code, int length){
  
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("expected bf file\n");
    return 1;
  }

  char* filename = argv[1];
  FILE *fp = fopen(filename, "r");
  if( fp == NULL){
    perror("file not found");
    return 1;
  }

  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  rewind(fp);
  
  char *buf = malloc(fsize + 1); // +1 for null terminator
  if (buf == NULL){
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
