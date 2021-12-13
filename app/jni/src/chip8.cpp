//
// Created by kingpin on 12/11/2021.
//

#include "chip8.h"

#include <chrono>

Chip8::Chip8() :
        randGen(std::chrono::system_clock::now().time_since_epoch().count()),
        fontset
                {
                        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                        0x20, 0x60, 0x20, 0x20, 0x70, // 1
                        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
                }
{
    // Initialize PC
    pc = START_ADDRESS;

    // Initialize RNG
    randByte = std::uniform_int_distribution<uint16_t>
            (0U, std::numeric_limits<uint8_t>::max());

    // Load fonts into memory
    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
        memory[FONTSET_START_ADDRESS + i] = fontset[i];

    table[0x0] = std::bind(&Chip8::Table0, this);
    table[0x1] = std::bind(&Chip8::OP_1nnn,this);
    table[0x2] = std::bind(&Chip8::OP_2nnn,this);
    table[0x3] = std::bind(&Chip8::OP_3xkk,this);
    table[0x4] = std::bind(&Chip8::OP_4xkk,this);
    table[0x5] = std::bind(&Chip8::OP_5xy0,this);
    table[0x6] = std::bind(&Chip8::OP_6xkk,this);
    table[0x7] = std::bind(&Chip8::OP_7xkk,this);
    table[0x8] = std::bind(&Chip8::Table8, this);
    table[0x9] = std::bind(&Chip8::OP_9xy0,this);
    table[0xA] = std::bind(&Chip8::OP_Annn,this);
    table[0xB] = std::bind(&Chip8::OP_Bnnn,this);
    table[0xC] = std::bind(&Chip8::OP_Cxkk,this);
    table[0xD] = std::bind(&Chip8::OP_Dxyn,this);
    table[0xE] = std::bind(&Chip8::TableE, this);
    table[0xF] = std::bind(&Chip8::TableF, this);

    table0[0x0] =std::bind(&Chip8::OP_00E0,this);
    table0[0xE] =std::bind(&Chip8::OP_00EE,this);

    table8[0x0] =std::bind(&Chip8::OP_8xy0,this);
    table8[0x1] =std::bind(&Chip8::OP_8xy1,this);
    table8[0x2] =std::bind(&Chip8::OP_8xy2,this);
    table8[0x3] =std::bind(&Chip8::OP_8xy3,this);
    table8[0x4] =std::bind(&Chip8::OP_8xy4,this);
    table8[0x5] =std::bind(&Chip8::OP_8xy5,this);
    table8[0x6] =std::bind(&Chip8::OP_8xy6,this);
    table8[0x7] =std::bind(&Chip8::OP_8xy7,this);
    table8[0xE] =std::bind(&Chip8::OP_8xyE,this);

    tableE[0x1] = std::bind(&Chip8::OP_ExA1, this);
    tableE[0xE] = std::bind(&Chip8::OP_Ex9E, this);

    tableF[0x07] =std::bind( &Chip8::OP_Fx07,this);
    tableF[0x0A] =std::bind( &Chip8::OP_Fx0A,this);
    tableF[0x15] =std::bind( &Chip8::OP_Fx15,this);
    tableF[0x18] =std::bind( &Chip8::OP_Fx18,this);
    tableF[0x1E] =std::bind( &Chip8::OP_Fx1E,this);
    tableF[0x29] =std::bind( &Chip8::OP_Fx29,this);
    tableF[0x33] =std::bind( &Chip8::OP_Fx33,this);
    tableF[0x55] =std::bind( &Chip8::OP_Fx55,this);
    tableF[0x65] =std::bind( &Chip8::OP_Fx65,this);

}

void Chip8::Cycle()
{
    // Fetch
    opcode = (memory[pc] << 8u) | memory[pc + 1];

    // Increment the PC before we execute anything
    pc += 2;

    //((*this).*(table[(opcode & 0xF000u) >> 12u]))();

    // Decode and Execute
    table[(opcode & 0xF000u) >> 12u]();

    // Decrement the delay timer if it's been set
    if (delayTimer > 0)
    {
        --delayTimer;
    }

    // Decrement the sound timer if it's been set
    if (soundTimer > 0)
    {
        --soundTimer;
    }
}