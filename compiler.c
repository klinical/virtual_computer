#include "includes/compiler.h"
#include "includes/computer.h" /* for max size definition */

unsigned long num_ops(FILE *);

FILE *Compile(FILE * const srcfile) {
  /**
   * For each line, split on white space into a list of three 'tokens'
   *  . If there are more than three tokens, invalid syntax . exit
   *  . If there are less than three tokens, invalid syntax . exit
   *  . if (Num Ops <= COMPUTER_MEM_SIZE) INCREMENT Num Ops else OUT OF MEMORY  . exit
   * 
   * For each token list
   *  . token[0] should be strictly numeric. between 00 AND N , where N = Num Ops
   *  . token[1] should be strictly characters, at MAX 4 chars wide AND
   *  . . FROM the following list: 
   *  . . . READ , WRIT , PRNT . LOAD , STOR , SET . 
   *  . . . ADD , SUB , DIV , MULT , MOD .
   *  . . . BRAND , BRNG, BRZR , HALT .
   *  . token[2] should be strictly numeric.  >= 2 digits wide and in range 0 - COMPUTER_MEM_SIZE
   *  . . UNLESS token[1] is a SET op. THEN >= 4 digits wide AND 0000 - COMPUTER_MEM_SIZE:COMPUTER_MEM_SIZE
   *  . Write to objfile ; Token:OpCode|Token:MemLoc
   *  . Free all dynamically allocated memory as necessary
   */ 
  unsigned long int opcount;

  opcount = num_ops(srcfile);
  printf("%lu\n", opcount);

  return NULL;
}

unsigned long int num_ops(FILE *srcfile) {
  int opcount, iter;
  char ch;

  opcount = 1;
  while ((ch=getc(srcfile)) != EOF) {
    if (ch == '\n')
      opcount++;
  }

  rewind(srcfile);
  return opcount;
}