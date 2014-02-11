CC=icpc
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES= FOFReaderLib/FOFFiles/FOFCube.cpp \
    FOFReaderLib/FOFFiles/FOFFile.cpp \
    FOFReaderLib/FOFFiles/FOFHalo.cpp \
    FOFReaderLib/FOFFiles/FOFMasst.cpp \
    FOFReaderLib/FOFFiles/FOFMultiCube.cpp \
    FOFReaderLib/FOFFiles/FOFParticles.cpp \
    FOFReaderLib/FOFFiles/FOFStrct.cpp \
    FOFReaderLib/DEUSSimulation/DEUSHalos.cpp \
    FOFReaderLib/DEUSSimulation/DEUSHalo.cpp \
    FOFReaderLib/DEUSSimulation/DEUSCubes.cpp \
    FOFReaderLib/DEUSSimulation/DEUSArea.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) FOFReader getBiggestHalo
	
FOFReader: FOFReader.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@

getBiggestHalo: getBiggestHalo.o $(OBJECTS) 
	$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o FOFReaderLib/*.o FOFReader getBiggestHalo