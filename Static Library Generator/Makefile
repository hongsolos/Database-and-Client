#MAKE FILE FOR GENERATING A LIBRARY FILE
#TAKES .h files and .cpp -> into .o files -> .a file
#TEAM 9#

OBJS = Record.o Table.o Database.o
CC = g++ -std=c++11
CS = g++ -shared -std=c++11
DEBUG = -g
CFLAGS =  -O2 -c -fpic -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

datalib.a: $(OBJS)
	$(CS) -o datalib.a $(OBJS)
	
Record.o: Record.h Record.cpp
	$(CC) $(CFLAGS) Record.cpp
Table.o: Table.h Table.cpp
	$(CC) $(CFLAGS) Table.cpp
Database.o: Database.h Database.cpp
	$(CC) $(CFLAGS) Database.cpp

clean:
	@echo "CLEANING UP ..."
	\rm *.o datalib.a
