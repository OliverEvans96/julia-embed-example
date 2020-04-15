JFLAGS=$(shell $(shell dirname $(shell which julia))/../share/julia/julia-config.jl --cflags --ldflags --ldlibs)
CC=gcc

host: host.c plugin.so
	$(CC) -std=c99 -Wall -ldl $< -o $@ 

%.so: %.c
	$(CC) -shared -o $@ $(JFLAGS) -fPIC $<

.PHONY: clean

clean:
	rm -f *.so host
