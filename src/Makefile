CC = g++-4.7
CFLAGS = $(OPTIMIZE) -std=c++11 -Wall -g -I. -I../src \
         $(shell pkg-config bullet --cflags)
CLIBS = -L. -lOpenGLSupport $(shell pkg-config bullet --libs) \
        -lm -lGL -lGLU -lglut 
SRCS =  phys_main.cpp \
	CcdPhysicsDemo.cpp \
	stlmesh.cpp \
	simulator.cpp \
	entityhandler.cpp \
	entity.cpp \
	pose.cpp \
	sensor.cpp \
	shapehandler.cpp \
	rocket.cpp \
	ground.cpp
OBJS =  phys_main.o \
	CcdPhysicsDemo.o \
	stlmesh.o \
	simulator.o \
	entityhandler.o \
	entity.o \
	pose.o \
	sensor.o \
	shapehandler.o \
	rocket.o \
	ground.o

MAKEDEPEND = gcc -M $(CFLAGS) -o $*.d $<

EXE = phys_demo

all: $(EXE)
	global -u # run incremental update

run: $(EXE)
	./$(EXE)

%.P: %.cpp
	$(MAKEDEPEND)
	@sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' < $*.d > $@; \
             rm -f $*.d; [ -s $@ ] || rm -f $@

include $(SRCS:.cpp=.P)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean:
	rm -f *.o
	rm -f $(EXE)
# DO NOT DELETE
