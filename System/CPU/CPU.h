//
// Created by leonv on 17/08/2023.
//

#ifndef INC_6502_EMULATOR_CPU_H
#define INC_6502_EMULATOR_CPU_H

#include <unordered_map>
#include <functional>
#include "Register.h"
#include "../Memory/Memory.h"

class CPU {
public:
    CPU();
    explicit CPU(Memory* memory);

    ~CPU();

    void cpuStep();
    void parseOpcode();


private:
    typedef std::function<void()> InstructionFunction;

    Register* reg;
    Memory* memory;

    uint8_t currentOpcode;
    std::unordered_map<uint8_t, InstructionFunction> opcodeTable;

    uint8_t readNextByte();
    uint16_t readNextWord();

    uint16_t indirectAddressing(uint8_t value, uint8_t reg);

    void handleGroupOneInstructions();

    void ORA(uint8_t bbb);
    void AND(uint8_t bbb);
    void EOR(uint8_t bbb);
    void ADC(uint8_t bbb);
    void STA(uint8_t bbb);
    void LDA(uint8_t bbb);
    void CMP(uint8_t bbb);
    void SBC(uint8_t bbb);

};


#endif //INC_6502_EMULATOR_CPU_H
