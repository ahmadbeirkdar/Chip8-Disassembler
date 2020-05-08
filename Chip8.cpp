//
// Created by Ahmad Beirkdar on 2020-05-08.
//

#include "Chip8.hpp"
#include <fstream>
#include <iostream>

void Chip8::LoadROM(std::string filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    size = file.tellg();
    memory = new uint8_t [size];
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(memory), size);



    file.close();
}

void Chip8::Diassemble() {
    std::cout << std::hex;
    for(unsigned long long i = 0; i < size; i+=2){
        opcode = (memory[i] << 8u)  | memory[i+1];
        ((*this).*(table[(opcode & 0xF000u) >> 12u]))();
    }

}

Chip8::Chip8() {

    table[0x0] = &Chip8::Table0;
    table[0x1] = &Chip8::OP_1NNN;
    table[0x2] = &Chip8::OP_2NNN;
    table[0x3] = &Chip8::OP_3XKK;
    table[0x4] = &Chip8::OP_4XKK;
    table[0x5] = &Chip8::OP_5XY0;
    table[0x6] = &Chip8::OP_6XKK;
    table[0x7] = &Chip8::OP_7XKK;
    table[0x8] = &Chip8::Table8;
    table[0x9] = &Chip8::OP_9XY0;
    table[0xA] = &Chip8::OP_ANNN;
    table[0xB] = &Chip8::OP_BNNN;
    table[0xC] = &Chip8::OP_CXKK;
    table[0xD] = &Chip8::OP_DXYN;
    table[0xE] = &Chip8::TableE;
    table[0xF] = &Chip8::TableF;
    table0[0x0] = &Chip8::OP_00E0;
    table0[0xE] = &Chip8::OP_00EE;
    table8[0x0] = &Chip8::OP_8XY0;
    table8[0x1] = &Chip8::OP_8XY1;
    table8[0x2] = &Chip8::OP_8XY2;
    table8[0x3] = &Chip8::OP_8XY3;
    table8[0x4] = &Chip8::OP_8XY4;
    table8[0x5] = &Chip8::OP_8XY5;
    table8[0x6] = &Chip8::OP_8XY6;
    table8[0x7] = &Chip8::OP_8XY7;
    table8[0xE] = &Chip8::OP_8XYE;
    tableE[0x1] = &Chip8::OP_EXA1;
    tableE[0xE] = &Chip8::OP_EX9E;
    tableF[0x07] = &Chip8::OP_FX07;
    tableF[0x0A] = &Chip8::OP_FX0A;
    tableF[0x15] = &Chip8::OP_FX15;
    tableF[0x18] = &Chip8::OP_FX18;
    tableF[0x1E] = &Chip8::OP_FX1E;
    tableF[0x29] = &Chip8::OP_FX29;
    tableF[0x33] = &Chip8::OP_FX33;
    tableF[0x55] = &Chip8::OP_FX55;
    tableF[0x65] = &Chip8::OP_FX65;
}

void Chip8::OP_00E0() {
    std::cout << "CLS                       "  <<"; Clear the display." << std::endl;

}

// Return
void Chip8::OP_00EE() {
//    pc = stack[--sp];
    std::cout << "RETURN                    " <<"; Return from a subroutine." << std::endl;
}

// goto NNN
void Chip8::OP_1NNN() {
//    pc = opcode & 0x0FFFu;
    std::cout << "JP 0x0"  << (opcode & 0x0FFFu) << "                 ; Jump to location" << std::endl;

}

// Call subroutine at NNN
void Chip8::OP_2NNN() {
//    stack[sp++] = pc;
//    pc = opcode & 0x0FFFu;
    std::cout << "CALL 0x0" << (opcode & 0x0FFFu) << "               ; Call subroutine" << std::endl;

}

// Skips the next instruction if VX equals NN
void Chip8::OP_3XKK() {
//    if(registers[(opcode & 0x0F00u) >> 8u] == (opcode & 0x00FFu))
//        pc+=2;
    std::cout << "SE V"<<((opcode & 0x0F00u) >> 8u) << ", "<<(opcode & 0x00FFu) << "                  ; Skip next instruction if Vx = kk" << std::endl;
}

// Skips the next instruction if VX doesn't equal NN
void Chip8::OP_4XKK() {
//    if(registers[(opcode & 0x0F00u) >> 8u] != (opcode & 0x00FFu))
//        pc+=2;
    std::cout << "SNE V"<<((opcode & 0x0F00u) >> 8u) << ", "<<(opcode & 0x00FFu) << "                 ; Skip next instruction if Vx != kk" << std::endl;

}

// Skips the next instruction if VX equals VY
void Chip8::OP_5XY0() {
//    if(registers[(opcode & 0x0F00u) >> 8u] == registers[(opcode & 0x00F0u) >> 4u])
//        pc+=2;
    std::cout << "SE V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Skip next instruction if Vx = Vy" << std::endl;
}
// Set Vx = kk.
void Chip8::OP_6XKK() {
//    registers[(opcode & 0x0F00u) >> 8u] = (opcode & 0x00FFu);
    std::cout << "LD V"<<((opcode & 0x0F00u) >> 8u) << ", 0x00"<<((opcode & 0x00FFu))<< "              ; Set Vx = kk" << std::endl;
}

// Set Vx = Vx + kk.
void Chip8::OP_7XKK() {
//    registers[(opcode & 0x0F00u) >> 8u] += (opcode & 0x00FFu);
    std::cout << "ADD V"<<((opcode & 0x0F00u) >> 8u) << ", 0x00"<<((opcode & 0x00FFu))<< "             ; Set Vx = Vx + kk" << std::endl;

}

// Set Vx = Vy
void Chip8::OP_8XY0() {
//    registers[(opcode & 0x0F00u) >> 8u] = registers[(opcode & 0x00F0u) >> 4u];
    std::cout << "LD V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Set Vx = Vy" << std::endl;
}

// Set Vx = Vx Or Vy
void Chip8::OP_8XY1() {
//    registers[(opcode & 0x0F00u) >> 8u] |= registers[(opcode & 0x00F0u) >> 4u];
    std::cout << "OR V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Set Vx = Vx OR Vy" << std::endl;

}

// Set Vx = Vx AND Vy
void Chip8::OP_8XY2() {
//    registers[(opcode & 0x0F00u) >> 8u] &= registers[(opcode & 0x00F0u) >> 4u];
    std::cout << "AND V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Set Vx = Vx AND Vy" << std::endl;
}

// Set Vx = Vx XOR Vy
void Chip8::OP_8XY3() {
//    registers[(opcode & 0x0F00u) >> 8u] ^= registers[(opcode & 0x00F0u) >> 4u];
    std::cout << "XOR V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Set Vx = Vx XOR Vy" << std::endl;

}

// Set Vx = Vx + Vy, set VF = carry. V at 0xF. If sum larger than 255, what a 8bit can hold max then it is carried.
void Chip8::OP_8XY4() {
//    if(registers[(opcode & 0x00F0u) >> 4u] > (0xFF - registers[(opcode & 0x0F00u) >> 8u]))
//        registers[0xF] = 1;
//    else
//        registers[0xF] = 0;
//    registers[(opcode & 0x0F00u) >> 8u] += registers[(opcode & 0x00F0u) >> 4u];
    std::cout << "ADD V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Set Vx = Vx + Vy, VF = carry" << std::endl;

}

// Set Vx = Vx - Vy, set VF = NOT borrow.
void Chip8::OP_8XY5() {
//    if(registers[(opcode & 0x00F0u) >> 4u] > registers[(opcode & 0x0F00u) >> 8u])
//        registers[0xF] = 0;
//    else
//        registers[0xF] = 1;
//    registers[(opcode & 0x0F00u) >> 8u] -= registers[(opcode & 0x00F0u) >> 4u];
    std::cout << "SUB V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Set Vx = Vx - Vy, VF = NOT borrow" << std::endl;

}

// Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
void Chip8::OP_8XY6() {
//    registers[0xF] = (registers[(opcode & 0x0F00u) >> 8u] & 0x1u);
//    registers[(opcode & 0x0F00u) >> 8u] >>= 1u;
    std::cout << "SHR V"<<((opcode & 0x0F00u) >> 8u) << "{, V"<<((opcode & 0x00F0u) >> 4u)<< "}                 ; Set Vx = Vx SHR 1" << std::endl;

}

// Set Vx = Vy - Vx, set VF = NOT borrow.
void Chip8::OP_8XY7() {
//    if(registers[(opcode & 0x0F00u) >> 8u] > registers[(opcode & 0x00F0u) >> 4u])
//        registers[0xF] = 0;
//    else
//        registers[0xF] = 1;
//    registers[(opcode & 0x00F0u) >> 4u] -= registers[(opcode & 0x0F00u) >> 8u];
    std::cout << "SUBN V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                ; Set Vx = Vy - Vx, VF = NOT borrow" << std::endl;
}

// Stores the most significant bit of VX in VF and then shifts VX to the left by 1
void Chip8::OP_8XYE() {
//    registers[0xF] = (registers[(opcode & 0x0F00u) >> 8u] >> 7u);
//    registers[(opcode & 0x0F00u) >> 8u] <<= 1u;
    std::cout << "SHL V"<<((opcode & 0x0F00u) >> 8u) << "{, V"<<((opcode & 0x00F0u) >> 4u)<< "}                 ; Set Vx = Vx SHL 1" << std::endl;
}

// Skip next instruction if Vx != Vy.
void Chip8::OP_9XY0() {
//    if(registers[(opcode & 0x0F00u) >> 8u] != registers[(opcode & 0x00F0u) >> 4u])
//        pc+= 2;
    std::cout << "SNE V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<< "                 ; Skip next instruction if Vx != Vy" << std::endl;

}


// Sets I to the address NNN. index
void Chip8::OP_ANNN() {
//    index = (opcode & 0x0FFFu);
    std::cout << "LD I"<<((opcode & 0x0F00u) >> 8u) << ", 0x0"<<((opcode & 0x0FFFu))<< "              ; Set I = nnn" << std::endl;


}

// Jump to location nnn + V0.
void Chip8::OP_BNNN() {
//    pc = registers[0] + (opcode & 0x0FFFu);
    std::cout << "JP V0" << ", 0x0"<<((opcode & 0x0FFFu))<< "              ; Jump to location nnn + V0" << std::endl;

}

// Set Vx = random byte AND kk.
void Chip8::OP_CXKK() {
//    registers[(opcode & 0x0F00u) >> 8u] = ((std::rand() % 0xFFu)&(opcode & 0x00FFu));
    std::cout << "RND V"<<((opcode & 0x0F00u) >> 8u) << ", 0x00"<<((opcode & 0x00FFu))<< "              ; Set Vx = random byte AND kk" << std::endl;
}

// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
// The interpreter reads n bytes from memory, starting at the address stored in I.
// These bytes are then displayed as sprites on screen at coordinates (Vx, Vy).
// Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0.
// If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen.
// See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
void Chip8::OP_DXYN() {
//    uint8_t Vx = registers[(opcode & 0x0F00u) >> 8u];
//    uint8_t Vy = registers[(opcode & 0x00F0u) >> 4u];
//    uint8_t xPos = Vx % VIDEO_WIDTH;
//    uint8_t yPos = Vy % VIDEO_HEIGHT;
//    uint8_t h = (opcode & 0x000Fu);
//    uint8_t pixel;
//    registers[0xF] = 0;
//
//    for(unsigned int y = 0; y < h; y++){
//        pixel = memory[index + y];
//        for(unsigned int x = 0; x < 8; x++){
//            if(pixel & (0x80u >> x)){
//                if(display[(xPos + x) + VIDEO_WIDTH*(yPos + y)] == 0xFFFFFFFF)
//                    registers[0xF] = 1;
//                display[(xPos + x) + VIDEO_WIDTH*(yPos + y)] ^= 0xFFFFFFFF;
//            }
//        }
//    }

    std::cout << "DRW V"<<((opcode & 0x0F00u) >> 8u) << ", V"<<((opcode & 0x00F0u) >> 4u)<<", 0x000"<<(opcode & 0x000Fu)<< "        ; Display draw n-byte sprite" << std::endl;


}

// Skip next instruction if key with the value of Vx is pressed.
void Chip8::OP_EX9E() {
//    if(keys[registers[(opcode & 0x0F00u) >> 8u]])
//        pc+=2;

}

// Skip next instruction if key with the value of Vx is not pressed.
void Chip8::OP_EXA1() {
//    if(!keys[registers[(opcode & 0x0F00u) >> 8u]])
//        pc+=2;

}

// Set Vx = delay timer value.
void Chip8::OP_FX07() {
//    registers[(opcode & 0x0F00u) >> 8u] = DelayTimer;

}

// Wait for a key press, store the value of the key in Vx.
void Chip8::OP_FX0A() {

}

// Set delay timer = Vx.
void Chip8::OP_FX15() {
//    DelayTimer = registers[(opcode & 0x0F00u) >> 8u];

}

// Set sound timer = Vx.
void Chip8::OP_FX18() {
//    SoundTimer = registers[(opcode & 0x0F00u) >> 8u];

}

// Set I = I + Vx.
void Chip8::OP_FX1E() {
//    index += registers[(opcode & 0x0F00u) >> 8u];

}

// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
// See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
void Chip8::OP_FX29() {
//    index = FONT_ADRR + (5*registers[(opcode & 0x0F00u) >> 8u]);

}

// Store BCD representation of Vx in memory locations I, I+1, and I+2.
// The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I,
// the tens digit at location I+1, and the ones digit at location I+2.
void Chip8::OP_FX33() {
//    memory[index] = ((registers[(opcode & 0x0F00u) >> 8u]) / 100);
//    memory[index + 1] = ((registers[(opcode & 0x0F00u) >> 8u]) / 10) % 10;
//    memory[index + 2] = ((registers[(opcode & 0x0F00u) >> 8u]) % 10);

}

// Store registers V0 through Vx in memory starting at location I.
void Chip8::OP_FX55() {
//    for(unsigned int i = 0; i <=  ((opcode & 0x0F00u) >> 8u); i++)
//        memory[index+i] = registers[i];

}

// Read registers V0 through Vx from memory starting at location I.
void Chip8::OP_FX65() {
//    for(unsigned int i = 0; i <=  ((opcode & 0x0F00u) >> 8u); i++)
//        registers[i] = memory[index+i];

}



// Tables
void Chip8::Table0(){
    ((*this).*(table0[opcode & 0x000Fu]))();
}

void Chip8::Table8() {
    ((*this).*(table8[opcode & 0x000Fu]))();
}

void Chip8::TableE() {
    ((*this).*(tableE[opcode & 0x000Fu]))();
}

void Chip8::TableF() {
    ((*this).*(tableF[opcode & 0x00FFu]))();
}


