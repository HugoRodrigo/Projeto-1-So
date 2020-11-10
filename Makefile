all: sourcefile.c
	gcc -o shell sourcefile.c
	./sourcefile
	
clean:
	$(RM) shell
