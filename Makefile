# Variables
CC = gcc
CFLAGS = -W -Wall -pedantic -O0 -g -fsanitize=address

all: main

# Objects
fatal.o: ./src/fatal.c ./include/fatal.h
	$(CC) $(CFLAGS) -c ./src/fatal.c

reader.o: ./src/reader.c ./include/reader.h
	$(CC) $(CFLAGS) -c ./src/reader.c

file.o: ./src/file.c ./include/file.h ./include/task.h ./include/reader.h
	$(CC) $(CFLAGS) -c ./src/file.c

date.o: ./src/date.c ./include/date.h ./include/fatal.h
	$(CC) $(CFLAGS) -c ./src/date.c

task.o: ./src/task.c ./include/task.h ./include/ansi_colors.h ./include/date.h
	$(CC) $(CFLAGS) -c ./src/task.c

cmd.o: ./src/cmd.c ./include/cmd.h ./include/file.h
	$(CC) $(CFLAGS) -c ./src/cmd.c

main.o: ./src/main.c ./include/cmd.h ./include/task.h
	$(CC) $(CFLAGS) -c ./src/main.c

# Executable
main: ./src/main.o ./src/fatal.o ./src/cmd.o ./src/reader.o ./src/task.o ./src/file.o ./src/date.o
	$(CC) $(CFLAGS) -o ./build/todoit ./src/main.o ./src/cmd.o ./src/fatal.o ./src/file.o ./src/date.o ./src/task.o ./src/reader.o

# Clean object files
clean:
	rm -f ./src/*.o ./src/*~

# Clean object files and build files
mrproper: clean
	rm -f ./build/todoit
