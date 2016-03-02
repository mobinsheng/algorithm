CPP=g++
CPPFLAG=-g
EXE=list

$(EXE):list.o main.o
	$(CPP) -o $(EXE) $(CPPFLAG) main.o list.o
	
main.o:main.cpp
	$(CPP) -c  $(CPPFLAG) main.cpp

list.o:list.cpp
	$(CPP) -c  $(CPPFLAG) list.cpp

clean:
	rm *.o $(EXE)


