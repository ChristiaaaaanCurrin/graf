
.PHONY: main clean

%.out: %.c 
	gcc -o $@ $<

clean:
	rm *.out

main: graf.out
	./$<

