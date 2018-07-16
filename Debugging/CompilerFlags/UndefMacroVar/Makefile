all: undef_macro_var.exe

warnings:
	$(CC) $(CFLAGS) -Wundef -c undef_macro_var.c

correct:
	$(CC) $(CFLAGS) -Wundef -c undef_macro_var.c -DPREC=32

undef_macro_var.exe: undef_macro_var.c
	$(CC) $(CFLAGS) -Wall -Wextra -o $@ $< -lm

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
