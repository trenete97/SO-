TARGET=printints arith Thabit ansi

all: $(TARGET)

printints: printints.c
	gcc -o printints printints.c

arith: arith.c
	gcc -o arith -lm arith.c

Thabit: Thabit.c
	gcc -o Thabit Thabit.c

ansi: ansi.c
	gcc -o ansi ansi.c

clean:
	rm $(TARGET)
