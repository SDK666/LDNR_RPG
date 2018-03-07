#	settings
CPP = g++
RES =  
M8N = main.cpp
M0N = main_temp.cpp

OBJ = layout.o interface.o equipment.o inventory.o character.o $(RES)
OBJLINK = character.o inventory.o equipment.o interface.o layout.o
LINKOBJ = $(M8N) $(OBJLINK)
LINK0BJ = $(M0N) $(OBJLINK)
LIBS = 

BIN = program.out
RM = rm -f

# cible principale
$(BIN): $(OBJ) $(M8N)
	@echo "Compilation totale"
	$(CPP) $(LINKOBJ) -o  $(BIN)  $(LIBS)

#dependances
character.o: character.cpp character.h inventory.o equipment.o
	$(CPP) -c character.cpp
			
inventory.o: inventory.cpp inventory.h
	$(CPP) -c inventory.cpp
			
equipment.o: equipment.cpp equipment.h
	$(CPP) -c equipment.cpp
			
interface.o: interface.cpp interface.h character.o layout.o
	$(CPP) -c interface.cpp
	
layout.o: layout.cpp layout.h
	$(CPP) -c layout.cpp
	
.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

# cible fictive
test: $(OBJ) $(M0N)
	@echo "Compilation testable"
	$(CPP) $(LINK0BJ) -o  $(BIN)  $(LIBS)
clean: clean-custom
	${RM} $(OBJ) $(BIN)
