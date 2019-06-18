all:
	rm -rf GBEmu
	clang++ -o GBEmu GameBoy.cpp CPU.cpp LCD.cpp Background.cpp Memory.cpp Timer.cpp Interrupts.cpp main.cpp -I./ -framework SDL2 --std=c++11
	mv GBEmu ../out/GBEmu