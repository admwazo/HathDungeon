#creating object variable
OBJECTS = Ammunition.o Armor.o Consumable.o Creature.o Entity.o Gold.o Item.o Potion.o Scroll.o Weapon.o XMLSerializable.o main.o
HEADERS = Ammunition.h Armor.h Consumable.h Creature.h Entity.h Gold.h Item.h Potion.h Scroll.h Weapon.h XMLSerializable.h Parser.h

all: prog1cons prog1cl

prog1cons: $(OBJECTS) main_console.o
	g++ $^ -o prog1cons

prog1cl: $(OBJECTS) main_cl.o
	g++ $^ -o prog1cl

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
clean:
	rm -f *.o prog1cons prog1cl 

test: prog1cl
	./prog1cl test.xml out2.xml
	diff -s out2.xml out.xml
