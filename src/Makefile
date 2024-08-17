all: msc


msc: msc.o msc_functions.o
	$(Q)$(CC) $(CFLAGS) $^ -o $@ -L../lib -lws -pthread

#msc: msc.o  #libmylib.a is the dependency for the executable
#	gcc -o msc msc.o -L../lib -lws

#msc.o: msc.c 
#	gcc -O -c msc.c


#	gcc -O -c test.c main.h
#
#iddSorted.o: addSorted.c addSorted.h
#	gcc -O -c addSorted.c

#freeLinks.o: freeLinks.c freeLinks.h
#	gcc -O -c freeLinks.c

#libmylib.a: addSorted.o freeLinks.o #let's link library files into a static library
#	ar rcs libmylib.a addSorted.o freeLinks.o

#libs: libmylib.a

clean:
	rm -f msc *.o *.a *.gch #This way is cleaner than your clean
