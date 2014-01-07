CC=icpc
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES=main.cpp \
    FOFReaderLib/FOFCube.cpp \
    FOFReaderLib/FOFFile.cpp \
    FOFReaderLib/FOFHalo.cpp \
    FOFReaderLib/FOFMasst.cpp \
    FOFReaderLib/FOFMultiCube.cpp \
    FOFReaderLib/FOFParticles.cpp \
    FOFReaderLib/FOFStrct.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=FOFReader

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)