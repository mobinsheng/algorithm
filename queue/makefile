CPP=g++
CPPFLAG=-g

EXE=queue

$(EXE):queue.o main.o
	$(CPP) -o $(EXE) $(CPPFLAG) queue.o main.o

queue.o:queue.cpp
	$(CPP) -c $(CPPFLAG) queue.cpp

main.o:main.cpp
	$(CPP) -c $(CPPFLAG) main.cpp

clean:
	rm *.o $(EXE)

