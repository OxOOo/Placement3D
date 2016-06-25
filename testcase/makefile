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
export LD_LIBRARY_PATH=$(LD_LIBRARY)
else
DEL = del
MKDIR = mkdir
DLL = $(LD_LIBRARY)/placement3d.dll
endif

all: $(OBJDIR) $(DLL) main demo

$(DLL):
	cd $(LD_LIBRARY) && make

main: $(OBJDIR)/main.o
	@echo "Now Generating $< ..."
	g++ -I$(INCLUDE) -L$(LD_LIBRARY) $^ -o $@ $(CXXFLAGS) $(LIB)

debug: $(OBJDIR)/debug.o
	@echo "Now Generating $< ..."
	g++ -I$(INCLUDE) -L$(LD_LIBRARY) $^ -o $@ $(CXXFLAGS) $(LIB)

run-debug:
	./debug

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
