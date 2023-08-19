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

    void printStatus();

private:
    std::unordered_map<uint8_t, std::function<void()>> instructions;

    Register* reg;
    Memory* memory;

    uint8_t currentOpcode;

    uint8_t readNextByte();
    uint16_t readNextWord();

    void handleGroupOneInstructions();
    void handleGroupTwoInstructions();
    void handleGroupThreeInstructions();

    void defineInstructions();

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
    void LDA(uint16_t value);
    void LDX(uint16_t value);
    void LDY(uint16_t value);
    void STA(uint16_t value);
    void STX(uint16_t value);
    void STY(uint16_t value);

    // Transfer Operations
    void TAX(uint16_t value);
    void TAY(uint16_t value);
    void TSX(uint16_t value);
    void TXA(uint16_t value);
    void TXS(uint16_t value);
    void TYA(uint16_t value);

    // Stack Operations
    void PHA(uint16_t value);
    void PHP(uint16_t value);
    void PLA(uint16_t value);
    void PLP(uint16_t value);

    // Shift Operations
    void ASL(uint16_t value);
    void LSR(uint16_t value);
    void ROL(uint16_t value);
    void ROR(uint16_t value);

    // Logic Operations
    void AND(uint16_t value);
    void BIT(uint16_t value);
    void EOR(uint16_t value);
    void ORA(uint16_t value);

    // Arithmetic Operations
    void ADC(uint16_t value);
    void CMP(uint16_t value);
    void CPX(uint16_t value);
    void CPY(uint16_t value);
    void SBC(uint16_t value);

    // Increment Operations
    void DEC(uint16_t value);
    void DEX(uint16_t value);
    void DEY(uint16_t value);
    void INC(uint16_t value);
    void INX(uint16_t value);
    void INY(uint16_t value);

    // Control Operations
    void BRK(uint16_t value);
    void JMP(uint16_t value);
    void JSR(uint16_t value);
    void RTI(uint16_t value);
    void RTS(uint16_t value);

    // Branch Operations
    void BCC(uint16_t value);
    void BCS(uint16_t value);
    void BEQ(uint16_t value);
    void BMI(uint16_t value);
    void BNE(uint16_t value);
    void BPL(uint16_t value);
    void BVC(uint16_t value);
    void BVS(uint16_t value);

    // Flag Operations
    void CLC(uint16_t value);
    void CLD(uint16_t value);
    void CLI(uint16_t value);
    void CLV(uint16_t value);
    void SEC(uint16_t value);
    void SED(uint16_t value);
    void SEI(uint16_t value);

    // No Operation
    void NOP(uint16_t value);

};


#endif //INC_6502_EMULATOR_CPU_H
