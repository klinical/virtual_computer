#include "includes/compiler.h"
#include "includes/computer.h" /* for max size definition */
#include "includes/util.h"
#include <limits.h>
#include <string.h>

typedef char *token;        /* a token is a string */
typedef token tokenlist[3]; /* array of 3 tokens */

#define MAX_ADDRESS_LEN 16     /* support up to 16 byte addresses */
#define MAX_OPERATION_LEN 4    /* instruction names do not exceed 4 bytes */
#define MAX_INSTRUCTIONS 10000 /* For sanity sakes */

unsigned long build_instruction_set(FILE *, tokenlist **, unsigned long int);
unsigned long int read_num_ops(FILE *srcfile);
short int read_token(FILE *, token, const char *);
void free_instr_set(tokenlist **, unsigned long int);
FILE *open_objfile(const char *srcfilename);

FILE *Compile(FILE *const srcfile, const char *srcfilename)
{
  unsigned long int num_instructions;
  tokenlist *instruction_set;
  FILE *objfile = NULL;

  num_instructions = read_num_ops(srcfile);
  build_instruction_set(srcfile, &instruction_set, num_instructions);

  objfile = open_objfile(srcfilename);

  free_instr_set(&instruction_set, num_instructions); /* let's try to avoid a use-after-free */

  instruction_set = NULL;

  return objfile;
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
}

FILE *open_objfile(const char *srcfilename)
{
  int i;
  size_t srcfilename_len;
  char *objfilename = NULL;
  FILE *objfile = NULL;

  srcfilename_len = strlen(srcfilename);
  objfilename = (char *)malloc((srcfilename_len + 2) * sizeof(char));

  for (i = 0; i < srcfilename_len; i++)
  {
    objfilename[i] = srcfilename[i];
  }
  objfilename[srcfilename_len + 1] = 'o';
  objfilename[srcfilename_len] = '.';

  objfile = T_FOpen(objfilename, "w");
  free(objfilename);

  return objfile;
}

void free_instr_set(tokenlist **list, unsigned long int num_instructions)
{
  unsigned long int i;
  int j;
  tokenlist *mem = *list;

  for (i = 0; i < (num_instructions - 1); i++)
  {
    for (j = 0; j < 3; j++)
    {
      printf(" %-4s ", mem[i][j]);
      free((*list)[i][j]);
    }
    puts("");
  }

  free(mem); /* free the dynamic parent array */
}

unsigned long int read_num_ops(FILE *srcfile)
{
  unsigned long int opcount;
  char ch;

  opcount = 1;
  while ((ch = getc(srcfile)) != EOF)
  {
    if (ch == '\n')
      opcount++;

    if (opcount >= COMPUTER_MEM_SIZE)
    {
      puts("Source code file contains too many instructions. Computer will run out of memory. Terminating.");
      exit(-1);
    }
  }

  rewind(srcfile);
  return opcount;
}

/**
 * Reads a source code file and parses out instruction tokens from the source file
 * Builds a tokenlist object and points the supplied pointer to the new tokenlist
 * */
unsigned long build_instruction_set(FILE *srcfile, tokenlist **instr_set, unsigned long int opcount)
{
  short int t_num, i, status; /* the current token number */
  unsigned long int iter;
  token ctoken; /* for storing the current token */
  tokenlist *new_instr_set;

  /**
   *  Dynamic array of static arrays. 
   *  Each internal array contains 3 char ptrs. 
   *  Note that we are allocating a block of memory to be pointed at later
  **/
  new_instr_set = (tokenlist *)malloc(opcount * sizeof(char *[3]));

  for (iter = 0; iter < (opcount - 1); iter++)
  {
    t_num = 0;

    for (i = 0; i < 3; i++) /* Go 1 past max num tokens to check if a line is invalid */
    {
      ctoken = (token)malloc(sizeof(char) * MAX_ADDRESS_LEN);

      switch (t_num)
      {
      case 0:
        if (read_token(srcfile, ctoken, "identifier") == -1)
        {
          printf("SYNTAX ERROR ON LINE %lu: IDENTIFIER NUMBER TOO HIGH'LOW. MAX NUMER OF INSTRUCTIONS SIZE: %d", iter, MAX_INSTRUCTIONS);
          exit(-1);
        }
        break;
      case 1:
        if (read_token(srcfile, ctoken, "operation") == -1)
        {
          printf("SYNTAX ERROR ON LINE %lu: OPERATION NOT SUPPORTED OR RECOGNIZED.", iter);
          exit(-1);
        }
        break;
      case 2:
        status = read_token(srcfile, ctoken, "address");
        if (status == -1)
        {
          printf("SYNTAX ERROR ON LINE %lu: SUPPLIED ADDRESS IS OF AN INVALID LENGTH. ADDRESSES MUST BE > 0 AND < %d", iter, MAX_ADDRESS_LEN);
          exit(-1);
        }
        if (status != 1)
        {
          printf("Syntax error: too many tokens @ line %lu\n", iter);
          exit(-1);
        }
        break;
      }

      new_instr_set[iter][t_num] = ctoken;

      t_num++;
    }
  }

  /* Point our instruction set at the freshly allocated block of memory */
  *instr_set = new_instr_set;
  return opcount;
}

/**
 * Reads a token based on type, return 0 if all good, -1 if failure.
 * */
short int read_token(FILE *srcfile, token tkn, const char *t_type)
{
  char ch;
  int token_width;
  int max_size;
  int ok;

  if (strcmp(t_type, "identifier") == 0)
  {
    max_size = MAX_INSTRUCTIONS;
  }
  else if (strcmp(t_type, "operation") == 0)
  {
    max_size = MAX_OPERATION_LEN;
  }
  else if (strcmp(t_type, "address") == 0)
  {
    max_size = MAX_ADDRESS_LEN;
  }
  else
  {
    printf("token: %s\n", t_type);
    puts("Unknown token type supplied to #read_token. Compiler bug. Terminating.");
    exit(-1);
  }

  token_width = 0, ok = 0;
  while (((ch = getc(srcfile)) != ' ' && ch != '\n'))
  {
    if (token_width > max_size || token_width < 0)
    {
      ok = -1;
    }

    tkn[token_width] = ch;
    token_width++;
  }

  if (ch == '\n')
  {
    ok = 1; /* signifies that we have read a newline, end of a token set */
  }

  return ok;
}
