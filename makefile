
.PHONY: main 

%.out: %.c 
	gcc $< -o $<

main: graf
	./$<

