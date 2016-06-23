SOURCES = $(wildcard *.cpp)
OBJDIR = objs
OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:%.cpp=%.o))
CXXFLAGS = -Wall -std=c++11 -I../src -L../src -lplacement3d

ifeq ($(shell uname), Linux)
TARGET = libplacement3d.so
DEL = rm -f
MKDIR = mkdir
COPY = cp
LD_LIBRARY = LD_LIBRARY_PATH=./
else
TARGET = libplacement3d.dll
DEL = del.exe
MKDIR = mkdir.exe
COPY = copy.exe
LD_LIBRARY =
endif

all: $(OBJDIR) main.exe
	$(COPY) ../src/$(TARGET) ./

main.exe: $(OBJDIR)/main.o
	@echo "Now Generating $< ..."
	g++ $< -o $@ $(CXXFLAGS)

run:
	$(LD_LIBRARY) ./main.exe

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	@echo "Now Compiling $< ..."
	g++ -I. -c $< -o $@ $(CXXFLAGS)

clean:
	$(DEL) $(OBJDIR)/*.o *.exe $(TARGET)

explain:
	@echo "User Sources: $(SOURCES)"
	@echo "User Objects: $(OBJECTS)"
