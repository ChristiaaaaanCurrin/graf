
.PHONY: main clean

%.out: %.c 
	gcc -o $@ $<

clean:
	rm -f *.out

main: graf.out
	./graf.out

