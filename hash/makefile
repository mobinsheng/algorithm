CPP=g++
CPPFLAG=-g
EXE=hash

$(EXE):hash.o main.o list.o
	$(CPP) -o $(EXE) $(CPPFLAG) hash.o main.o list.o
	
hash.o:hash.cpp
	$(CPP) -c $(CPPFLAG) hash.cpp

list.o:../list/list.cpp
	$(CPP) -c $(CPPFLAG) ../list/list.cpp

main.o:main.cpp
	$(CPP) -c $(CPPFLAG) main.cpp

clean:
	rm *.o $(EXE)
