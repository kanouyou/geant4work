TARGET   = PionYield.exe
CXX      = g++
OBJECTS  = Run.o IPlot.o IAnalysis.o
CXXLIBS  =
CXXFLAGS = -Wall -O3 #-I include
#VPATH    = include src

ROOTLIBS  = `root-config --evelibs`
ROOTFLAGS = `root-config --cflags`

CXXLIBS  += $(ROOTLIBS)
CXXFLAGS += $(ROOTFLAGS)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXLIBS) $^ -o $@

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(TARGET) $(TARGET2) $(OBJECTS) $(OBJECTS2)


