#creating object variable
OBJECTS = DungeonLevel.o main.o
HEADERS = DungeonLevel.h

all: pa2 pa2test

pa2: $(OBJECTS) main_console.o
	g++ $^ -o pa2

pa2test: $(OBJECTS) main_test.o
	g++ $^ -o pa2test

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@ -std=c++0x

clean:
	rm -f *.o pa2 pa2test 

test: pa2test
	./pa2test
