#MAKE FILE FOR PROJECT 1
#NON-FUNCTIONAL STATIC LIBRARY YET

OBJS = Record.o Table.o Database.o TestCasesTeam10.o
CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

./a.out: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./a.out
	
Record.o: Record.h Record.cpp
	$(CC) $(CFLAGS) Record.cpp
Table.o: Table.h Table.cpp
	$(CC) $(CFLAGS) Table.cpp
Database.o: Database.h Database.cpp
	$(CC) $(CFLAGS) Database.cpp
TestCasesTeam10.o: TestCasesTeam10.cpp
	$(CC) $(CFLAGS) TestCasesTeam10.cpp
clean:
	@echo "CLEANING UP ..."
	\rm *.o ./a.out

#TO CREATE LIBRARY FILE: g++ -shared -std=c++11 -o fileLib files....
