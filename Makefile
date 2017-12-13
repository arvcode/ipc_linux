reciprocal.o: reciprocal.c	
	$(CC) -o reciprocal reciprocal.c

	$(CC) -o forke forke.c

clean:
	$(RM) *.o
