
.PHONY: main clean

%.out: %.c 
	gcc -Wall -std=c99 -o $@ $<

clean:
	rm -f *.out

main: graf.out
	./graf.out

