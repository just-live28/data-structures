clean:
	rm -f *.o *.out *.exe *.bin

hello: hello.c
	gcc hello.c -o hello
