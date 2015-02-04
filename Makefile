CC=g++
CFLAGS=-c -Wall -O3 -g -fopenmp -std=c++0x
LDFLAGS=-fopenmp
SOURCES= FOFReaderLib/FOFFiles/FOFCube.cpp \
    FOFReaderLib/FOFFiles/FOFFile.cpp \
    FOFReaderLib/FOFFiles/FOFHalo.cpp \
    FOFReaderLib/FOFFiles/FOFMasst.cpp \
    FOFReaderLib/FOFFiles/FOFMultiCube.cpp \
    FOFReaderLib/FOFFiles/FOFParticles.cpp \
    FOFReaderLib/FOFFiles/FOFStrct.cpp \
    FOFReaderLib/FOFFiles/FOFCubeGrav.cpp \
    FOFReaderLib/FOFFiles/FOFCubeGravLevel.cpp \
    FOFReaderLib/DEUSSimulation/DEUSHalos.cpp \
    FOFReaderLib/DEUSSimulation/DEUSHalo.cpp \
    FOFReaderLib/DEUSSimulation/DEUSCubes.cpp \
    FOFReaderLib/DEUSSimulation/DEUSGrav.cpp \
    FOFReaderLib/DEUSSimulation/DEUSArea.cpp \
    FOFReaderLib/DEUSSimulation/DEUSSimulationSingleton.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) FOFReader FOFGetFiles getBiggestHalo exportMasst generateImage generateRandomCube
	
FOFReader: FOFReader.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@
	
FOFGetFiles: FOFGetFiles.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@	

getBiggestHalo: getBiggestHalo.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@
	
exportMasst: exportMasst.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@
	
generateImage: generateImage.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@
	
generateRandomCube: generateRandomCube.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o FOFReaderLib/*.o FOFReaderLib/FOFFiles/*.o FOFReaderLib/DEUSSimulation/*.o FOFReader getBiggestHalo exportMasst generateImage generateRandomCube FOFGetFiles
