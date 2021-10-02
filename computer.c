#include "includes/computer.h"

Computer *Init_Computer(size_t memsize) {
  Computer *cptr;

  cptr = (Computer *) malloc(sizeof(Computer));
  cptr->memory = (char *) malloc(memsize * WORD_SIZE);
  cptr->accumulator = 0;
  cptr->instructionCount = 0;
  cptr->instructionRegister = 0;
  
  return cptr;
}

void Destroy_Computer(Computer *computer) {
  free(computer->memory);
  free(computer);
  puts("Computer destroyed.");
}