CC = g++-4.7
CFLAGS = $(OPTIMIZE) -std=c++11 -Wall -g -I. -I../src $(shell pkg-config bullet --cflags)
CLIBS = -L. -lOpenGLSupport $(shell pkg-config bullet --libs) \
        -lm -lGL -lGLU -lglut 
OBJS =  main.o \
	CcdPhysicsDemo.o \
	StlLoader.o \
	simulator.o \
	entityhandler.o \
	entity.o \
	pose.o \
	sensor.o

EXE = demo

all: $(EXE)

run: $(EXE)
	./$(EXE)

%.P: %.cpp
	$(MAKEDEPEND)
	@sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' < $*.d > $@; \
             rm -f $*.d; [ -s $@ ] || rm -f $@

include $(SRCS.cpp=.P)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean:
	rm -f *.o
	rm -f $(EXE)
