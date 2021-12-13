//
// Created by kingpin on 12/11/2021.
//

#ifndef EMU8_CHIP8_H
#define EMU8_CHIP8_H

#include <cstdint>
#include <random>
#include <array>
#include <functional>
class Chip8
{
public:
    const unsigned int START_ADDRESS = 0x200;
    const unsigned int FONTSET_START_ADDRESS = 0x50;
    static const unsigned int FONTSET_SIZE = 80;
    const unsigned int VIDEO_WIDTH = 64;
    const unsigned int VIDEO_HEIGHT = 32;

public:
    uint8_t     registers[16]{};
    uint8_t     memory[4096]{};
    uint16_t    index{};
    uint16_t    pc{};
    uint16_t    stack[16]{};
    uint8_t     sp{};
    uint8_t     delayTimer{};
    uint8_t     soundTimer{};
    uint8_t     keypad[16]{};
    uint32_t    video[64 * 32]{};
    uint16_t    opcode{};
    std::array<uint8_t, FONTSET_SIZE>  fontset;

public:
    Chip8();
    void LoadROM(char const* filename);
    void Cycle();

    // Opcode Instructions
public:
    void OP_00E0(); // Clear the display.
    void OP_00EE(); // Return from a subroutine
    void OP_1nnn(); // Jump to location nnn
    void OP_2nnn(); // Call subroutine at nnn
    void OP_3xkk(); // Skip next instruction if Vx==kk
    void OP_4xkk(); // Skip next instruction if Vx!=kk
    void OP_5xy0(); // Skip next instruction if Vx=Vy
    void OP_6xkk(); // Set Vx=kk
    void OP_7xkk(); // Set Vx=Vx+kk.
    void OP_8xy0(); // Set Vx=Vy
    void OP_8xy1(); // Set Vx= Vx or Vy
    void OP_8xy2(); // Set Vx= Vx and Vy
    void OP_8xy3(); // Set Vx=Vx xor Vy
    void OP_8xy4(); // Set Vx=Vx+Vy, Set VF = carry
    void OP_8xy5(); // Set Vx = Vx - Vy, set VF = NOT borrow
    void OP_8xy6(); // Set Vx=Vx shr 1
    void OP_8xy7(); // Set Vx= Vy - Vx, set VF = NOT borrow
    void OP_8xyE(); // Set Vx= Vx shl 1
    void OP_9xy0(); // Skip next instruction if Vx != Vy
    void OP_Annn(); // Set I=nnn
    void OP_Bnnn(); // Jump to location nnn+V0
    void OP_Cxkk(); // Set Vx=random byte and kk
    void OP_Dxyn(); // Display n-byte sprite starting at //location I at (Vx, Vy), set VF = collision
    void OP_Ex9E(); //Skip next instruction if key with the value //of Vx is pressed
    void OP_ExA1(); // Skip next instruction if key with the value //of Vx is not pressed
    void OP_Fx07(); // Set Vx = delay timer value
    void OP_Fx0A(); // Wait for a key press, store the value of the key in Vx.
    void OP_Fx15(); // Set delay timer = Vx
    void OP_Fx18(); // Set sound timer = Vx
    void OP_Fx1E(); // Set I = I + Vx
    void OP_Fx29(); // Set I = location of sprite for digit Vx
    void OP_Fx33(); // Store BCD representation of Vx in memory locations I, I+1, and I+2
    void OP_Fx55(); // Store registers V0 through Vx in memory starting at location I
    void OP_Fx65(); // Read registers V0 through Vx from memory starting at location


    void Table0()
    {
        table0[opcode & 0x000Fu]();
    }

    void Table8()
    {
        table8[opcode & 0x000Fu]();
    }

    void TableE()
    {
        tableE[opcode & 0x000Fu]();
    }

    void TableF()
    {
        tableF[opcode & 0x00FFu]();
    }

    void OP_NULL()
    {}


    /*typedef void (Chip8::* Chip8Func)();

    Chip8Func table[0xF + 1]{ &Chip8::OP_NULL };
    Chip8Func table0[0xE + 1]{ &Chip8::OP_NULL };
    Chip8Func table8[0xE + 1]{ &Chip8::OP_NULL };
    Chip8Func tableE[0xE + 1]{ &Chip8::OP_NULL };
    Chip8Func tableF[0x65 + 1]{ &Chip8::OP_NULL };*/

    //function type hehe
    std::function<void(void)> table[0xF + 1]    { std::bind(&Chip8::OP_NULL,this) };
    std::function<void(void)> table0[0xE + 1]   { std::bind(&Chip8::OP_NULL,this) };
    std::function<void(void)> table8[0xE + 1]   { std::bind(&Chip8::OP_NULL,this) };
    std::function<void(void)> tableE[0xE + 1]   { std::bind(&Chip8::OP_NULL,this) };
    std::function<void(void)> tableF[0x65 + 1]  { std::bind(&Chip8::OP_NULL,this) };



private:
    std::default_random_engine randGen;
    std::uniform_int_distribution<uint16_t> randByte{};

};

#endif //EMU8_CHIP8_H