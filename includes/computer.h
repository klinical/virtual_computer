#ifndef COMPUTER_H_
#define COMPUTER_H_
#include <stdlib.h>
#include <stdio.h>

#define COMPUTER_MEM_SIZE ULONG_MAX /* Max value of a unsigned long */
#define WORD_SIZE (2 * sizeof(char)) /* size of a machine word */

typedef struct {
  char *memory; /* Dynamic memory, laid out in the form
                * [OpCode, Operand], [OpCode, Operand], [OpCode, ...
                * where each [OpCode, Operand] is one machine word,
                * an instruction to execute, and the associated memory location 
                */
  int accumulator;
  int instructionCount;
  int instructionRegister;
  char opCode;
  char operand;
} Computer;

Computer *Init_Computer(size_t);
void Destroy_Computer(Computer *);

#endif