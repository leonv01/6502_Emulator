//
// Created by leonv on 17/08/2023.
//

#ifndef INC_6502_EMULATOR_CPU_H
#define INC_6502_EMULATOR_CPU_H

#include <unordered_map>
#include <functional>
#include <chrono>
#include "Register.h"
#include "../Memory/Memory.h"

class CPU {
public:
    CPU();
    explicit CPU(Memory* memory);

    ~CPU();

    void cpuStep();
    void cpuRun();

    void printStatus();

private:
    uint8_t currentOpcode;
    uint16_t cycles;
    bool enableTestPageExceed;
    bool systemRun;
    Register* reg;
    Memory* memory;

    std::unordered_map<uint8_t, std::function<void()>> instructions;

    uint8_t readNextByte();
    uint16_t readNextWord();

    void pushByte(uint8_t value);
    void pushWord(uint16_t value);

    uint8_t popByte();
    uint16_t popWord();

    void defineInstructions();
    bool checkPageExceed(uint16_t addr1, uint16_t addr2);

    uint16_t accMode();
    uint16_t immMode();
    uint16_t absMode();
    uint16_t absxMode();
    uint16_t absyMode();
    uint16_t absiMode();
    uint16_t zpMode();
    uint16_t zpyMode();
    uint16_t zpxMode();
    uint16_t zpxiMode();
    uint16_t zpyiMode();
    uint16_t relMode();

    // Load Operations
    void LDA(uint16_t addr);
    void LDX(uint16_t addr);
    void LDY(uint16_t addr);
    void STA(uint16_t addr);
    void STX(uint16_t addr);
    void STY(uint16_t addr);

    // Transfer Operations
    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();

    // Stack Operations
    void PHA();
    void PHP();
    void PLA();
    void PLP();

    // Shift Operations
    void ASL(uint16_t addr);
    void ASL_A();
    void LSR(uint16_t addr);
    void LSR_A();
    void ROL(uint16_t addr);
    void ROL_A();
    void ROR(uint16_t addr);
    void ROR_A();

    // Logic Operations
    void AND(uint16_t addr);
    void BIT(uint16_t addr);
    void EOR(uint16_t addr);
    void ORA(uint16_t addr);

    // Arithmetic Operations
    void ADC(uint16_t addr);
    void CMP(uint16_t addr);
    void CPX(uint16_t addr);
    void CPY(uint16_t addr);
    void SBC(uint16_t addr);

    // Increment Operations
    void DEC(uint16_t addr);
    void DEX();
    void DEY();
    void INC(uint16_t addr);
    void INX();
    void INY();

    // Control Operations
    void BRK();
    void JMP(uint16_t addr);
    void JSR(uint16_t addr);
    void RTI();
    void RTS();

    // Branch Operations
    void BCC(uint16_t addr);
    void BCS(uint16_t addr);
    void BEQ(uint16_t addr);
    void BMI(uint16_t addr);
    void BNE(uint16_t addr);
    void BPL(uint16_t addr);
    void BVC(uint16_t addr);
    void BVS(uint16_t addr);

    // Flag Operations
    void CLC();
    void CLD();
    void CLI();
    void CLV();
    void SEC();
    void SED();
    void SEI();

    // No Operation
    void NOP();

};


#endif //INC_6502_EMULATOR_CPU_H
