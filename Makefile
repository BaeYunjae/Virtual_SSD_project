CC = gcc
OBJS = main.o

ssd : $(OBJS)
	$(CC) $^ -o $@

main.o : main.c
	$(CC) -c $<

clean : 
	rm -r ./*.o nand.txt result.txt ssd
