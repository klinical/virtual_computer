/**
 * Main entry point of the virtual computer
 * Acts as the main controller of the program
 * Initializing the computer, reading the input instructions
 * Compiling the instruction set into machine code
 * Aswell as executing the final compiled machine code
 * 
 * @Zachary Nickels, 2021
 * */
#include "includes/computer.h"
#include "includes/util.h"
#include "includes/compiler.h"
#include "includes/executor.h"
#include <stdint.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int arglen;

  FILE *srcfile = NULL, *objfile = NULL;

  /* Correct usage: ./program srcfile  */
  if (argc < 2)
  {
    puts("Missing required argument for source file. View the included README file for instructions on using this application.");
    exit(-1);
  }
  else if (argc == 2)
  {
    arglen = (int)strlen(argv[1]);

    if (arglen < 0 || arglen > 50)
    { /* In case of buffer overflow */
      puts("Specified source file name too long.");
      exit(-1);
    }

    srcfile = T_FOpen(argv[1], "r");
  }
  else
  {
    puts("Too many arguments. View the included README file for instructions on using this application.");
    exit(-1);
  }

  /* Source file opened, now it must be compiled */
  objfile = Compile(srcfile, argv[1]);

  if (objfile)
  {
    /* Note: COMPUTER_MEM_SIZE refers to the number of machine instructions */
    Computer *v_cp = Init_Computer(COMPUTER_MEM_SIZE);

    /* load objfile into computer memory & execute */
    Execute(objfile, v_cp);

    /* computer has gone away */
    Destroy_Computer(v_cp);
  }
  else
  {
    puts("Source file failed compilation attempt. Nothing to do.");
    exit(-1);
  }

  fclose(srcfile);
  fclose(objfile);

  exit(0);
}
