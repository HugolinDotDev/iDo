# Variables
CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -O0 -g -fsanitize=address

# Objects
fatal.o: ./src/fatal.c ./include/fatal.h
	$(CC) $(CFLAGS) -c ./src/fatal.c

date.o: ./src/date.c ./include/date.h ./include/fatal.h
	$(CC) $(CFLAGS) -c ./src/date.c

task.o: ./src/task.c ./include/task.h ./include/ansi_colors.h ./include/date.h
	$(CC) $(CFLAGS) -c ./src/task.c

main.o: ./src/main.c ./include/task.h
	$(CC) $(CFLAGS) -c ./src/main.c

# Executable
main: ./src/main.o ./src/fatal.o ./src/task.o ./src/date.o
	$(CC) $(CFLAGS) -o ./build/todoit ./src/main.o ./src/fatal.o ./src/date.o ./src/task.o

# Clean object files
clean:
	rm -f ./src/*.o ./src/*~

# Clean object files and build files
mrproper: clean
	rm -f ./build/todoit