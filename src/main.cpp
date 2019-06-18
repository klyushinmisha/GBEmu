#include "Main/GameBoy.h"

int main(int argc, char** argv)
{
	GameBoy* gb = GameBoy::getInstance();
	gb->LoadCartridge(argv[1]);
    gb->Run();
	return 0;
}