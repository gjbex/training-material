hello.exe: hello.o
	ld -s -o $@ $<

hello.o: hello.nsm
	nasm -f elf64 -o $@ $<

clean:
	$(RM) hello.o hello.exe
