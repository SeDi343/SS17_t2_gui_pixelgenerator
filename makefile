#-------------------------------------------------------------

TARGET   = pixelgenerator
SOURCES  = gui_pixelgenerator.c gui_pixelgenerator_functions.c
RESOURCE = style_res

#-------------------------------------------------------------

#-------------------------------------------------------------

CXX      = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0` -Wall -g
CPPFLAGS = -I.
LDFLAGS  = -lm

#-------------------------------------------------------------
# Rules
#

all: $(TARGET) $(RESOURCE).c clean

$(TARGET): $(SOURCES) $(RESOURCE).c
	$(CXX) $(SOURCES) $(RESOURCE).c $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

$(RESOURCE).c: $(RESOURCE).gresource.xml
	glib-compile-resources --sourcedir=. $(RESOURCE).gresource.xml --generate-source

.PHONY: clean
clean:
	@rm -rf $(OBJECTS) core *~
	@rm -rf $(RESOURCE).c
