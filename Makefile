CC=icpc
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES= FOFReaderLib/FOFCube.cpp \
    FOFReaderLib/FOFFile.cpp \
    FOFReaderLib/FOFHalo.cpp \
    FOFReaderLib/FOFMasst.cpp \
    FOFReaderLib/FOFMultiCube.cpp \
    FOFReaderLib/FOFParticles.cpp \
    FOFReaderLib/FOFStrct.cpp
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