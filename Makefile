lps.o: lps.c
	gcc -c lps.c
lps: lps.o
	gcc lps.o -o lps