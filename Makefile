.PHONY: build clean

SRC_PATH=./src
INCLUDE_PATH=./include

build:
	mkdir -p build
	g++ -o ./build/GBEmu -I${INCLUDE_PATH} ${SRC_PATH}/GameBoy.cpp \
		${SRC_PATH}/CPU.cpp ${SRC_PATH}/LCD.cpp ${SRC_PATH}/Background.cpp \
		${SRC_PATH}/Memory.cpp ${SRC_PATH}/Timer.cpp \
		${SRC_PATH}/Interrupts.cpp ${SRC_PATH}/main.cpp -lSDL2
	cp boot.bin ./build

clean:
	rm -rf build
