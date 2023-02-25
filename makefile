CC = g++ 
CCFLAGS = -std=c++2a

tagDriver.exe: tagDriver.o tag.o
	$(CC) $(CCFLAGS) tagDriver.o tag.o -o tagDriver.exe 

tagDriver.o: tagDriver.cpp tag.cpp
	$(CC) $(CCFLAGS) -c tagDriver.cpp -o tagDriver.o

tag.o: tag.cpp
	$(CC) $(CCFLAGS) -c tag.cpp -o tag.o

clean:
	rm *.o tagDriver.exe
	rm tag.txt