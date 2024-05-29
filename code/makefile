main:				../main.cpp bin/signal.o bin/four1.o
					g++ ../main.cpp bin/signal.o bin/four1.o -o ../main

bin/signal.o: 		headers/signal.hpp src/signal.cpp
					g++ -c src/signal.cpp -o bin/signal.o

bin/four1.o:		headers/four1.h src/four1.c
					g++ -c src/four1.c -o bin/four1.o

clean:
					rm bin/*.o
cleanWin:
					del bin/*.o