CPP = gcc
FLAGS = -O5 -pg -Wall -W
RM  = rm -f
EXEC = testProg1a

OBJECTS = \
	 main.o \
	 func.o \

all: $(OBJECTS) compile touch

main.o : main.c
					 $(CPP) $(FLAGS) -c main.c
func.o : func.c
			   		 $(CPP) $(FLAGS) -c func.c
clean:
					 $(RM) $(OBJECTS) $(EXEC)

compile:
					 $(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC)

touch:
					 @echo " "
					 @echo "Compilation done successfully..................."
					 @echo " "
