SOURCES = $(wildcard *.cpp)
OBJDIR = objs
OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:%.cpp=%.o))
INCLUDE = ../src
LD_LIBRARY = ../src
LIB = -lplacement3d
CXXFLAGS = -Wall -std=c++11

ifeq ($(shell uname), Linux)
DEL = rm -f
DELDIR = rm -rf
MKDIR = mkdir
TARGET = main
DLL = $(LD_LIBRARY)/libplacement3d.so
export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(LD_LIBRARY)
else
DEL = del
DELDIR = rmdir /s /q
MKDIR = mkdir
TARGET = main.exe
DLL = $(LD_LIBRARY)/placement3d.dll
export PATH := $(PATH);$(LD_LIBRARY)
endif

all: $(OBJDIR) $(DLL) $(TARGET)

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
<<<<<<< HEAD
	$(DEL) $(TARGET)
	$(DELDIR) $(OBJDIR)
=======
	$(DEL) $(OBJDIR)/*.o main demo debug
>>>>>>> 436d390e7603794af22b66c8c6997ede502fb0ad

explain:
	@echo "User Sources: $(SOURCES)"
	@echo "User Objects: $(OBJECTS)"

run:
	./$(TARGET)
