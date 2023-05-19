CC = g++
CFLAGS = -c
OBJS = AnimalSetters.o DataProcessing.o Simulation.o HeaderSetters.o InputChacker.o InputEntities.o InputReader.o gettersSettersMap.o Main.o Map.o plantSpeciesSetters.o simulationEntitie.o
TARGET = evolution

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)  $(OBJS) -o $(TARGET)

AnimalSetters.o: AnimalSetters.cpp InputEntities.h
	$(CC) $(CFLAGS) AnimalSetters.cpp

DataProcessing.o: DataProcessing.h DataProcessing.cpp
	$(CC) $(CFLAGS) DataProcessing.cpp

Simulation.o: Simulation.h Simulation.cpp
	$(CC) $(CFLAGS) Simulation.cpp

HeaderSetters.o: HeaderSetters.cpp InputEntities.h
	$(CC) $(CFLAGS) HeaderSetters.cpp

InputChacker.o: InputChacker.cpp chacker.h
	$(CC) $(CFLAGS) InputChacker.cpp

InputEntities.o: InputEntities.h InputEntities.cpp
	$(CC) $(CFLAGS) InputEntities.cpp

InputReader.o: InputReader.h InputReader.cpp chacker.h
	$(CC) $(CFLAGS) InputReader.cpp

gettersSettersMap.o: gettersSettersMap.cpp Map.h
	$(CC) $(CFLAGS) gettersSettersMap.cpp

Main.o: Main.cpp Simulation.h
	$(CC) $(CFLAGS) Main.cpp

Map.o: Map.h Map.cpp
	$(CC) $(CFLAGS) Map.cpp

plantSpeciesSetters.o: plantSpeciesSetters.cpp InputEntities.h
	$(CC) $(CFLAGS) plantSpeciesSetters.cpp

simulationEntitie.o: simulationEntitie.h simulationEntitie.cpp
	$(CC) $(CFLAGS) simulationEntitie.cpp

clean:
	rm -f $(OBJS) $(TARGET)
