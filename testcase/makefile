SOURCES = $(wildcard *.cpp)
OBJDIR = objs
OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:%.cpp=%.o))
INCLUDE = ../src
LD_LIBRARY = ../src
LIB = -lplacement3d
CXXFLAGS = -Wall -std=c++11

ifeq ($(shell uname), Linux)
DEL = rm -f
MKDIR = mkdir
DLL = $(LD_LIBRARY)/libplacement3d.so
LIBDEMO = $(LIB) -lGL -lGLU -lglut
export LD_LIBRARY_PATH=../src
else
DEL = del
MKDIR = mkdir
DLL = $(LD_LIBRARY)/placement3d.dll
LIBDEMO = $(LIB) -lopengl32 -lglu32 -lglut32
endif

all: $(OBJDIR) $(DLL) main demo

$(DLL):
	cd $(LD_LIBRARY) && make

main: $(OBJDIR)/main.o
	@echo "Now Generating $< ..."
	g++ -I$(INCLUDE) -L$(LD_LIBRARY) $< -o $@ $(CXXFLAGS) $(LIB)

demo: $(OBJDIR)/demo.o
	@echo "Now Generating $< ..."
	g++ -I$(INCLUDE) -L$(LD_LIBRARY) $< -o $@ $(CXXFLAGS) $(LIBDEMO)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	@echo "Now Compiling $< ..."
	g++ -I$(INCLUDE) -c $< -o $@ $(CXXFLAGS)

clean:
	$(DEL) $(OBJDIR)/*.o main demo

explain:
	@echo "User Sources: $(SOURCES)"
	@echo "User Objects: $(OBJECTS)"

run:
	./main

DEMO_ARGS ?= -s sol.txt
run-demo:
	./demo $(DEMO_ARGS)
