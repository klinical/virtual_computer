#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdio.h>

/** 
 * Read a source code file and compile it to a more machine readable format
 * return a pointer to the file,
 */
FILE *Compile(FILE *, const char *);

#endif