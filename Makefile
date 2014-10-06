.PHONY: compile clean run

compile: bin/main
	
bin/main:
	mkdir -p bin
	g++ -o $@ main.cpp -lmemcached -I/usr/include/libmemcached

clean:
	rm -rf bin output
	
run:
	./bin/main
	echo "stats items" | nc 127.0.0.1 11211