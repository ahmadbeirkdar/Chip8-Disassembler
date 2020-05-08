#include <iostream>
#include "Chip8.hpp"

int main() {
    std::cout << "CHIP8 DIASSEMBLER!!!" << std::endl;
    Chip8 chip;

    chip.LoadROM("Pong.ch8");
    chip.Diassemble();
    return 0;
}
