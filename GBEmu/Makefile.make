PATH = /Users/mihail/Desktop/C++/GBEmu/GBEmu/

INCLUDE = $(PATH)
RESOURCES = $(PATH)
FRAMEWORK = /Library/Frameworks/SDL2.framework/Headers
OUT = $(PATH)out/


.PHONY: all


all: $(OUT)GBEmu
	rm -rf $(OUT)Memory.o
	rm -rf $(OUT)LCD.o
	rm -rf $(OUT)CPU.o
	rm -rf $(OUT)Timer.o
	rm -rf $(OUT)Interrupts.o
	rm -rf $(OUT)Background.o
	rm -rf $(OUT)ALU.o
	rm -rf $(OUT)GameBoy.o


$(OUT)GBEmu: $(OUT)Memory.o $(OUT)LCD.o $(OUT)CPU.o $(OUT)Timer.o $(OUT)Interrupts.o $(OUT)Background.o $(OUT)ALU.o $(OUT)GameBoy.o
	clang++ -o $(OUT)GBEmu$(OUT)Background.o $(OUT)ALU.o $(OUT)Memory.o $(OUT)LCD.o $(OUT)CPU.o $(OUT)Timer.o $(OUT)Interrupts.o $(OUT)GameBoy.o -framework SDL2


$(OUT)GameBoy.o:
	clang++ -o $(OUT)GameBoy.o -c $(RESOURCES)GameBoy.cpp -I$(INCLUDE) -F$(FRAMEWORK)


$(OUT)Background.o:
	clang++ -o $(OUT)Background.o -c $(RESOURCES)Background.cpp -I$(INCLUDE)


$(OUT)ALU.o:
	clang++ -o $(OUT)ALU.o -c  $(RESOURCES)ALU.cpp -I$(INCLUDE)


$(OUT)LCD.o: 
	clang++ -o $(OUT)LCD.o -c $(RESOURCES)LCD.cpp -I$(INCLUDE)


$(OUT)CPU.o:
	clang++ -o $(OUT)CPU.o -c  $(RESOURCES)CPU.cpp -I$(INCLUDE)


$(OUT)Memory.o:
	clang++ -o $(OUT)Memory.o -c $(RESOURCES)Memory.cpp -I$(INCLUDE)


$(OUT)Timer.o:
	clang++ -o $(OUT)Timer.o -c $(RESOURCES)Timer.cpp -I$(INCLUDE)


$(OUT)Interrupts.o:
	clang++ -o $(OUT)Interrupts.o -c  $(RESOURCES)Interrupts.cpp -I$(INCLUDE)
