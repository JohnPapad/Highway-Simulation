CC=g++
CXXFLAGS= -Wall -g -std=c++11

highway_sim: main.o attiki_odos.o entrance.o e_tolls.o seg.o tolls.o vehicle.o
	$(CC) $(CXXFLAGS) main.o attiki_odos.o entrance.o e_tolls.o seg.o tolls.o vehicle.o -o highway_sim

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp
	
entrance.o: entrance.cpp entrance.h
	$(CC) $(CXXFLAGS) -c entrance.cpp
	
attiki_odos.o: attiki_odos.cpp attiki_odos.h
	$(CC) $(CXXFLAGS) -c attiki_odos.cpp
	
e_tolls.o: e_tolls.cpp e_tolls.h 
	$(CC) $(CXXFLAGS) -c e_tolls.cpp
	
seg.o: seg.cpp seg.h
	$(CC) $(CXXFLAGS) -c seg.cpp
	
tolls.o: tolls.cpp tolls.h 
	$(CC) $(CXXFLAGS) -c tolls.cpp
	
vehicle.o: vehicle.cpp vehicle.h 
	$(CC) $(CXXFLAGS) -c vehicle.cpp


.PHONY: clean

clean:
	rm -f highway_sim *.o  