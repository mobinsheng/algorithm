CPP=g++
CPPFLAG=-g
EXE=set

$(EXE):main.o set.o list.o
	$(CPP) -o $(EXE) $(CPPFLAG) main.o set.o list.o

main.o:main.cpp
	$(CPP) -c $(CPPFLAG) main.cpp

set.o:set.cpp
	$(CPP) -c $(CPPFLAG) set.cpp

list.o:../list/list.cpp
	$(CPP) -c $(CPPFLAG) ../list/list.cpp

clean:
	rm *.o $(EXE)

