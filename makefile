CC = gcc
CFLAGS := -Wall -ansi -pedantic -g -c
CHKFLAGS := -Wall -Wextra -Wparentheses -ansi -pedantic -pedantic-errors -Wextra -O
TARGET = virtual_computer
UTIL = util
XCTR = executor
CMPTR = computer
CMPLR = compiler
INC = includes/

default: $(TARGET)
$(TARGET): $(TARGET).o $(UTIL).o $(XCTR).o $(CMPTR).o $(CMPLR).o
	$(CC) $(UTIL).o $(XCTR).o $(CMPTR).o $(CMPLR).o $(TARGET).o -o $(TARGET)

$(UTIL).o: $(UTIL).c includes/$(UTIL).h
	$(CC) -I ./includes $(CFLAGS) $(UTIL).c -o $(UTIL).o

$(XCTR).o: $(XCTR).c includes/$(XCTR).h
	$(CC) -I ./includes $(CFLAGS) $(XCTR).c -o $(XCTR).o

$(CMPTR).o: $(CMPTR).c includes/$(CMPTR).h
	$(CC) -I ./includes $(CFLAGS) $(CMPTR).c -o $(CMPTR).o

$(CMPLR).o: $(CMPLR).c includes/$(CMPLR).h
	$(CC) -I ./includes $(CFLAGS) $(CMPLR).c -o $(CMPLR).o

$(TARGET).o: $(TARGET).c $(INC)$(UTIL).h $(INC)$(XCTR).h $(INC)$(CMPTR).h $(INC)$(CMPLR).h
	$(CC) -I ./includes $(CFLAGS) $(UTIL).c $(XCTR).c $(CMPTR).c $(CMPLR).c $(TARGET).c

clean:
	@$(RM) $(TARGET)
	@$(RM) $(TARGET).o
	@$(RM) $(UTIL).o
	@$(RM) $(XCTR).o
	@$(RM) $(CMPTR).o
	@$(RM) $(CMPLR).o
