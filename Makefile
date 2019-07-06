CXX = g++ # This is the main compiler
CXXFLAGS = -std=c++14 -Wall

SRCDIR = src
BUILDDIR = build
TARGET = bin/quadris
 
SRCEXT = cc
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

INC = -I include

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)

# Tests
#tester:
#	$(CXX) $(CXXFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean