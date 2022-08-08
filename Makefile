btree: main.o btree.o queue.o utility.o 
	gcc main.o btree.o queue.o utility.o -o btree

main.o: main.c btree.h btree.c queue.h queue.c utility.h utility.c
	gcc -c main.c btree.c queue.c utility.c

btree.o: btree.h btree.c queue.h queue.c
	gcc -c btree.c queue.c

queue.o: queue.h queue.c
	gcc -c queue.c

utility.o: btree.h btree.c utility.h utility.c
	gcc -c btree.c utility.c 

clean:
	rm *.o 