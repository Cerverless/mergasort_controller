all: test_it

test_it: test_it.o subsystem 
	gcc -Wl,-R/usr/local/lib -L/usr/local/lib/ -ltap -lm -o test_it ../src/msc_functions.o test_it.o -L../lib -lws

#test_it.o: test_it.c ../src/msc_functions.h
#	gcc -O -c test.c

subsystem:
	cd ../src && $(MAKE)

clean:
	rm -f test_it *.o *.a *.gch #This way is cleaner than your clean
