CXX = g++ # This is the main compiler
CXXFLAGS = -std=c++14 -Wall

SRCDIR = src
BUILDDIR = build
TARGETDIR = bin
TARGET = ${TARGETDIR}/quadris
 
SRCEXT = cc
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

INC = -I include

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@mkdir -p ${TARGETDIR}
	$(CXX) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)
	
.PHONY: clean