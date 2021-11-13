
.PHONY: main clean

%.out: %.c list.h
	gcc -o $@ $<

clean:
	rm *.out

main: graf.out
	./$<

