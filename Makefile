# Variables
CC = gcc
CFLAGS = -W -Wall -pedantic -O0 -g -fsanitize=address

all: main

# Objects
fatal.o: ./src/fatal.c ./include/fatal.h
	$(CC) $(CFLAGS) -c ./src/fatal.c

file.o: ./src/file.c ./include/file.h ./include/task.h
	$(CC) $(CFLAGS) -c ./src/file.c

date.o: ./src/date.c ./include/date.h ./include/fatal.h ./include/data_check.h
	$(CC) $(CFLAGS) -c ./src/date.c

task.o: ./src/task.c ./include/task.h ./include/ansi_colors.h ./include/date.h
	$(CC) $(CFLAGS) -c ./src/task.c

data_check.o: ./src/data_check.c ./include/data_check.h ./include/date.h
	$(CC) $(CFLAGS) -c ./src/data_check.c

cmd.o: ./src/cmd.c ./include/cmd.h ./include/file.h
	$(CC) $(CFLAGS) -c ./src/cmd.c

main.o: ./src/main.c ./include/cmd.h
	$(CC) $(CFLAGS) -c ./src/main.c

# Executable
main: ./src/main.o ./src/fatal.o ./src/cmd.o ./src/task.o ./src/file.o ./src/date.o ./src/data_check.o
	$(CC) $(CFLAGS) -o ./build/ido ./src/main.o ./src/cmd.o ./src/fatal.o ./src/file.o ./src/date.o ./src/task.o ./src/data_check.o

# Clean object files
clean:
	rm -f ./src/*.o ./src/*~

# Clean object files and build files
mrproper: clean
	rm -f ./build/ido
