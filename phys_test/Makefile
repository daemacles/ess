CC = g++-4.7
CFLAGS = $(OPTIMIZE) -std=c++11 -Wall -g -I. $(shell pkg-config bullet --cflags)
CLIBS = -L. -lOpenGLSupport $(shell pkg-config bullet --libs) \
        -lm -lGL -lGLU -lglut 
OBJS = main.o CcdPhysicsDemo.o
EXE = demo

all: $(EXE)

run: $(EXE)
	./$(EXE)

main.o: main.cpp *.h
	$(CC) $(CFLAGS) -c $<

CcdPhysicsDemo.o: CcdPhysicsDemo.cpp *.h
	$(CC) $(CFLAGS) -c $<

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean:
	rm -f *.o
	rm -f $(EXE)
