#creating object variable
OBJECTS = Ammunition.o Armor.o Consumable.o Creature.o DungeonLevel.o Entity.o Gold.o Item.o Potion.o Scroll.o Weapon.o XMLSerializable.o main.o
HEADERS = Ammunition.h Armor.h Consumable.h Creature.h DungeonLevel.h Entity.h Gold.h Item.h Potion.h Scroll.h Weapon.h XMLSerializable.h Parser.h

all: game game-test

game: $(OBJECTS) main_console.o
	g++ $^ -o game

game-test: $(OBJECTS) main_test.o
	g++ $^ -o game-test

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@ -std=c++0x

clean:
	rm -f *.o game game-test

test: game-test
	./game-test
