OBJS = main.o csv.o dbmanager.o utility.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
INCFLAGS = -I/usr/include/mysql/ -I/usr/local/include/mysql/ -I/usr/include/mysql++/ -I/usr/local/include/mysql++/
LIBFLAGS = -lmysqlpp -L/usr/local/lib

parser: $(OBJS)
	$(CC) $(LFLAGS) $(LIBFLAGS) $(OBJS) -o parser

main.o: main.cpp csv.hpp dbmanager.hpp utility.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) main.cpp

csv.o: csv.cpp
	$(CC) $(CFLAGS) csv.cpp

dbmanager.o: dbmanager.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) dbmanager.cpp

utility.o: utility.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) utility.cpp

clean:
	rm -rf *.o