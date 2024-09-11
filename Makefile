CC = gcc
CFLAGS = -std=c99 -w

all: version1 version2 run

version1: version1.c timer.h
    @$(CC) $(CFLAGS) -o version1 version1.c

version2: version2.c timer.h
    @$(CC) $(CFLAGS) -o version2 version2.c

run: version1 version2
    @echo -e "\n---------------Running Test---------------\n"
    @echo -e "Running version 1...\n"
    @./version1
    @echo -e "------------------------------------------\n"
    @echo -e "Running version 2...\n"
    @./version2
    @echo -e "------------------------------------------\n"
    
clean:
    rm -f version1 version2