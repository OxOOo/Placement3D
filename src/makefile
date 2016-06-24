SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJDIR = objs
OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:%.cpp=%.o))
CXXFLAGS = -Wall -std=c++11 -fPIC

ifeq ($(shell uname), Linux)
TARGET = libplacement3d.so
DEL = rm -f
MKDIR = mkdir
else
TARGET = placement3d.dll
DEL = del
MKDIR = mkdir
endif

all: $(TARGET)

$(TARGET): $(OBJDIR) $(OBJECTS) $(HEADERS)
	@echo "Now Generating $(TARGET) ..."
	g++ -shared $(OBJECTS) -o $(TARGET) $(CXXFLAGS)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: %.cpp %.h
	@echo "Now Compiling $< ..."
	g++ -I. -c $< -o $@ $(CXXFLAGS)

clean:
	$(DEL) $(OBJDIR)/*.o $(TARGET)

explain:
	@echo "Headers: $(HEADERS)"
	@echo "User Sources: $(SOURCES)"
	@echo "User Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"
