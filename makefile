#creating object variable
OBJECTS = Ammunition.o Armor.o Consumable.o Creature.o DungeonLevel.o Entity.o Factory.o Game.o Gold.o Item.o Parser.o Player.o Potion.o Scroll.o Tile.o Weapon.o XMLSerializable.o main.o
HEADERS = Ammunition.h Armor.h Consumable.h Creature.h DungeonLevel.h Entity.h Factory.h Game.h Gold.h Item.h Parser.h Player.h Potion.h Scroll.h Tile.h Weapon.h XMLSerializable.h

all: game game-test

game: $(OBJECTS) main_console.o
	g++ $^ -o game -lncurses

game-test: $(OBJECTS) main_test.o
	g++ $^ -o game-test -lncurses

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@ -std=c++0x

clean:
	rm -f *.o game game-test

test: game-test
	./game-test
