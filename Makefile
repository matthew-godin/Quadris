CXX = g++ # This is the main compiler
CXXFLAGS = -std=c++14 -Wall -MMD

SRCDIR = src
BUILDDIR = build
TARGET = bin/quadris
 
SRCEXT = cc
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

INC = -I include

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $(TARGET)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET) $(LIB)";

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<" 

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
#tester:
#	$(CXX) $(CXXFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean