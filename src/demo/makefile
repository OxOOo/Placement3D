SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJDIR = objs
OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:%.cpp=%.o))
INCLUDE = ../
LD_LIBRARY = ../
LIB = -lplacement3d
CXXFLAGS = -Wall -std=c++11

ifeq ($(shell uname), Linux)
DEL = rm -f
DELDIR = rm -rf
MKDIR = mkdir
TARGET = demo
DLL = $(LD_LIBRARY)/libplacement3d.so
LIBDEMO = $(LIB) -lGL -lGLU -lglut
export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(LD_LIBRARY)
else
DEL = del
DELDIR = rmdir /s /q
MKDIR = mkdir
TARGET = demo.exe
DLL = $(LD_LIBRARY)/placement3d.dll
LIBDEMO = $(LIB) -lopengl32 -lglu32 -lglut32
export PATH := $(PATH);$(LD_LIBRARY)
endif

all: $(OBJDIR) $(DLL) $(TARGET)

$(DLL):
	cd $(LD_LIBRARY) && make

$(TARGET): $(OBJECTS)
	@echo $(OBJECTS)
	@echo "Now Generating $< ..."
	g++ -I$(INCLUDE) -L$(LD_LIBRARY) $^ -o $@ $(CXXFLAGS) $(LIBDEMO)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	@echo "Now Compiling $< ..."
	g++ -I$(INCLUDE) -c $< -o $@ $(CXXFLAGS)

clean:
	$(DEL) $(TARGET)
	$(DELDIR) $(OBJDIR)

explain:
	@echo "User Sources: $(SOURCES)"
	@echo "User Objects: $(OBJECTS)"

DEMO_ARGS ?= -s sol.txt
run:
	./$(TARGET) $(DEMO_ARGS)
