procsyn:buffer.o procsyn.o
	gcc buffer.o procsyn.o -o procsyn 

buffer.o:buffer.c
	gcc -c buffer.c -o buffer.o

procsyn.o:procsyn.c
	gcc -c procsyn.c -o procsyn.o

.PHONY:clean
clean:
	rm -rf .*o
