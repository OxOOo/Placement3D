SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJDIR = objs
OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:%.cpp=%.o))
CXXFLAGS = -Wall -std=c++11 -fPIC

ifeq ($(shell uname), Linux)
DEL = rm -f
DELDIR = rm -rf
MKDIR = mkdir
TARGET = libplacement3d.so
else
DEL = del
DELDIR = rmdir /s /q
MKDIR = mkdir
TARGET = placement3d.dll
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
	$(DEL) $(TARGET)
	$(DELDIR) $(OBJDIR)

explain:
	@echo "Headers: $(HEADERS)"
	@echo "User Sources: $(SOURCES)"
	@echo "User Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"
