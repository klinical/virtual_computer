#include "includes/util.h"

/* function Name	  : T_FOpen
 * Parameters		    : (char *dest): the 'string' used as target filename, (char* mode): the mode with which to open the file
 * Return value(s)	: (FILE*) pointer to the opened file descriptor
 * Description		  : This function attempts to open a file, exiting if failure is encountered
 */
FILE* T_FOpen(const char* dest, const char* mode) {
  FILE* fp;
  if ((fp = fopen(dest, mode)) == NULL) {
    printf("FAILED TO OPEN %s, TERMINATING.\n", dest);
    exit(1);
  }

  return fp;
}