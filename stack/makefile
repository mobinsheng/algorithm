CPP=g++
CPPFLAG=-g

EXE=stack

$(EXE):main.o stack.o
	 $(CPP) -o $(EXE) $(CPPFLAG) main.o stack.o

main.o:main.cpp
	$(CPP) -c  $(CPPFLAG) main.cpp

stack.o:stack.cpp
	$(CPP) -c  $(CPPFLAG) stack.cpp

clean:
	rm *.o $(EXE)


