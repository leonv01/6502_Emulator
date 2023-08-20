//
// Created by leonv on 17/08/2023.
//

#include "CPU.h"

bool CPU::checkPageExceed(uint16_t addr1, uint16_t addr2){
    enableTestPageExceed = false;
    return ((addr1 & 0xFF00) != (addr2 & 0xFF00));
}

uint16_t CPU::immMode() {
    return reg->PC;
}

uint16_t CPU::absMode() {
    return readNextWord();
}

uint16_t CPU::accMode() {
    return 0;
}

uint16_t CPU::absxMode() {
    uint16_t address = readNextWord();
    uint16_t output = address + reg->X;

    if(enableTestPageExceed)
        if(checkPageExceed(address, output)) cycles++;
    return output;
}

uint16_t CPU::absyMode() {
    uint16_t address = readNextWord();
    uint16_t output = address + reg->Y;

    if(enableTestPageExceed)
        if(checkPageExceed(address, output)) cycles++;
    return output;
}

uint16_t CPU::absiMode() {
    return 0;
}

uint16_t CPU::zpMode() {
    return readNextByte();
}

uint16_t CPU::zpyMode() {
    uint8_t zeroPageAddress = readNextByte();
    uint16_t output = (zeroPageAddress + reg->Y) & 0xFF;
    if(enableTestPageExceed)
        checkPageExceed(zeroPageAddress, output);
    return output;
}

uint16_t CPU::zpxMode() {
    uint8_t zeroPageAddress = readNextByte();
    return (zeroPageAddress + reg->X) & 0xFF;
}

uint16_t CPU::zpxiMode() {
    uint8_t zeroPageAddress = readNextByte();
    uint8_t effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
    return memory->readWord(effectiveAddress);
}

uint16_t CPU::zpyiMode() {
    uint8_t zeroPageAddress = readNextByte();
    uint8_t effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
    return memory->readWord(effectiveAddress);
}

uint16_t CPU::relMode() {
    auto offset = static_cast<int8_t>(readNextByte());
    return static_cast<uint16_t>(reg->PC + offset);
}


void CPU::defineInstructions() {
    // ORA Instructions
    instructions[0x09] = [this]() { cycles += 2; ORA(immMode()); };
    instructions[0x0D] = [this]() { cycles += 4;ORA(absMode()); };
    instructions[0x1D] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        ORA(absxMode()); };
    instructions[0x19] = [this]() { cycles += 4;
        enableTestPageExceed = true; ORA(absyMode()); };
    instructions[0x05] = [this]() { cycles += 3; ORA(zpMode()); };
    instructions[0x15] = [this]() { cycles += 4; ORA(zpxMode()); };
    instructions[0x01] = [this]() { cycles += 6; ORA(zpxiMode()); };
    instructions[0x11] = [this]() { cycles += 5;
        enableTestPageExceed = true;
        ORA(zpyiMode()); };

    // AND Instructions
    instructions[0x29] = [this]() { cycles += 2; AND(immMode()); };
    instructions[0x2D] = [this]() { cycles += 4; AND(absMode()); };
    instructions[0x3D] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        AND(absxMode()); };
    instructions[0x39] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        AND(absyMode()); };
    instructions[0x25] = [this]() { cycles += 3; AND(zpMode()); };
    instructions[0x35] = [this]() { cycles += 4; AND(zpxMode()); };
    instructions[0x21] = [this]() { cycles += 6; AND(zpxiMode()); };
    instructions[0x31] = [this]() { cycles += 5;
        enableTestPageExceed = true;
        AND(zpyiMode()); };

    // BIT Instructions
    instructions[0x2C] = [this]() { cycles += 4; BIT(absMode()); };
    instructions[0x24] = [this]() { cycles += 3; BIT(zpMode()); };

    // EOR Instructions
    instructions[0x49] = [this]() { cycles += 2; EOR(immMode()); };
    instructions[0x4D] = [this]() { cycles += 4; EOR(absMode()); };
    instructions[0x5D] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        EOR(absxMode()); };
    instructions[0x59] = [this]() {  cycles += 4;
        enableTestPageExceed = true;
        EOR(absyMode()); };
    instructions[0x45] = [this]() { cycles += 3; EOR(zpMode()); };
    instructions[0x55] = [this]() { cycles += 4; EOR(zpxMode()); };
    instructions[0x41] = [this]() { cycles += 6; EOR(zpxiMode()); };
    instructions[0x51] = [this]() { cycles += 5;
        enableTestPageExceed = true;
        EOR(zpyiMode()); };

    // ADC Instructions
    instructions[0x69] = [this]() { cycles += 2; ADC(immMode()); };
    instructions[0x6D] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        ADC(absMode()); };
    instructions[0x7D] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        ADC(absxMode()); };
    instructions[0x79] = [this]() { cycles += 4; ADC(absyMode()); };
    instructions[0x65] = [this]() { cycles += 3; ADC(zpMode()); };
    instructions[0x75] = [this]() { cycles += 4; ADC(zpxMode()); };
    instructions[0x61] = [this]() { cycles += 6; ADC(zpxiMode()); };
    instructions[0x71] = [this]() { cycles += 5;
        enableTestPageExceed = true;
        ADC(zpyiMode()); };

    // STA Instructions
    instructions[0x8D] = [this]() { cycles += 4; STA(absMode()); };
    instructions[0x9D] = [this]() { cycles += 5; STA(absxMode()); };
    instructions[0x99] = [this]() { cycles += 5; STA(absyMode()); };
    instructions[0x85] = [this]() { cycles += 3; STA(zpMode()); };
    instructions[0x95] = [this]() { cycles += 4; STA(zpxMode()); };
    instructions[0x81] = [this]() { cycles += 6; STA(zpxiMode()); };
    instructions[0x91] = [this]() { cycles += 6; STA(zpyiMode()); };

    // LDA Instructions
    instructions[0xA9] = [this]() { cycles += 2; LDA(immMode()); };
    instructions[0xAD] = [this]() { cycles += 4; LDA(absMode()); };
    instructions[0xBD] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        LDA(absxMode()); };
    instructions[0xB9] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        LDA(absyMode()); };
    instructions[0xA5] = [this]() { cycles += 3; LDA(zpMode()); };
    instructions[0xB5] = [this]() { cycles += 4; LDA(zpxMode()); };
    instructions[0xA1] = [this]() { cycles += 6; LDA(zpxiMode()); };
    instructions[0xB1] = [this]() { cycles += 5;
        enableTestPageExceed = true;
        LDA(zpyiMode()); };

    // CMP Instructions
    instructions[0xC9] = [this]() { cycles += 2; CMP(immMode()); };
    instructions[0xCD] = [this]() { cycles += 4; CMP(absMode()); };
    instructions[0xDD] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        CMP(absxMode()); };
    instructions[0xD9] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        CMP(absyMode()); };
    instructions[0xC5] = [this]() { cycles += 3; CMP(zpMode()); };
    instructions[0xD5] = [this]() { cycles += 4; CMP(zpxMode()); };
    instructions[0xC1] = [this]() { cycles += 6; CMP(zpxiMode()); };
    instructions[0xD1] = [this]() { cycles += 5;
        enableTestPageExceed = true;
        CMP(zpyiMode()); };

    // CPX Instructions
    instructions[0xE0] = [this]() { cycles += 2; CPX(immMode()); };
    instructions[0xEC] = [this]() { cycles += 4; CPX(absMode()); };
    instructions[0xE4] = [this]() { cycles += 3; CPX(zpMode()); };

    // CPY Instructions
    instructions[0xC0] = [this]() { cycles += 2; CPY(immMode()); };
    instructions[0xCC] = [this]() { cycles += 4; CPY(absMode()); };
    instructions[0xC4] = [this]() { cycles += 3; CPY(zpMode()); };

    // SBC Instructions
    instructions[0xE9] = [this]() { cycles += 2; SBC(immMode()); };
    instructions[0xED] = [this]() { cycles += 4; SBC(absMode()); };
    instructions[0xFD] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        SBC(absxMode()); };
    instructions[0xF9] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        SBC(absyMode()); };
    instructions[0xE5] = [this]() { cycles += 3; SBC(zpMode()); };
    instructions[0xF5] = [this]() { cycles += 4; SBC(zpxMode()); };
    instructions[0xE1] = [this]() { cycles += 6; SBC(zpxiMode()); };
    instructions[0xF1] = [this]() { cycles += 5;
        enableTestPageExceed = true;
        SBC(zpyiMode()); };

    // ASL Instructions
    instructions[0x0A] = [this]() { cycles += 2; ASL_A(); };
    instructions[0x0E] = [this]() { cycles += 6; ASL(absMode()); };
    instructions[0x1E] = [this]() { cycles += 7; ASL(absxMode()); };
    instructions[0x06] = [this]() { cycles += 5; ASL(zpMode()); };
    instructions[0x16] = [this]() { cycles += 6; ASL(zpxMode()); };

    // ROL Instructions
    instructions[0x2A] = [this]() { cycles += 2; ROL_A(); };
    instructions[0x2E] = [this]() { cycles += 6; ROL(absMode()); };
    instructions[0x3E] = [this]() { cycles += 7; ROL(absxMode()); };
    instructions[0x26] = [this]() { cycles += 5; ROL(zpMode()); };
    instructions[0x36] = [this]() { cycles += 6; ROL(zpxMode()); };

    // LSR Instructions
    instructions[0x4A] = [this]() { cycles += 2; LSR_A(); };
    instructions[0x4E] = [this]() { cycles += 6; LSR(absMode()); };
    instructions[0x5E] = [this]() { cycles += 7; LSR(absxMode()); };
    instructions[0x46] = [this]() { cycles += 5; LSR(zpMode()); };
    instructions[0x56] = [this]() { cycles += 6; LSR(zpxMode()); };

    // ROR Instructions
    instructions[0x6A] = [this]() { cycles += 2; ROR_A(); };
    instructions[0x6E] = [this]() { cycles += 6; ROR(absMode()); };
    instructions[0x7E] = [this]() { cycles += 7; ROR(absxMode()); };
    instructions[0x66] = [this]() { cycles += 5; ROR(zpMode()); };
    instructions[0x76] = [this]() { cycles += 6; ROR(zpxMode()); };

    // STX Instructions
    instructions[0x8E] = [this]() { cycles += 4; STX(absMode()); };
    instructions[0x86] = [this]() { cycles += 3; STX(zpMode()); };
    instructions[0x96] = [this]() { cycles += 4; STX(zpyMode()); };

    // STY Instructions
    instructions[0x8C] = [this]() { cycles += 4; STY(absMode()); };
    instructions[0x84] = [this]() { cycles += 3; STY(zpMode()); };
    instructions[0x94] = [this]() { cycles += 4; STY(zpxMode()); };

    // LDX Instructions
    instructions[0xA2] = [this]() { cycles += 2; LDX(immMode()); };
    instructions[0xAE] = [this]() { cycles += 4; LDX(absMode()); };
    instructions[0xBE] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        LDX(absyMode()); };
    instructions[0xA6] = [this]() { cycles += 3; LDX(zpMode()); };
    instructions[0xB6] = [this]() { cycles += 4; LDX(zpyMode()); };

    // LDY Instructions
    instructions[0xA0] = [this]() { cycles += 2; LDY(immMode()); };
    instructions[0xAC] = [this]() { cycles += 4; LDY(absMode()); };
    instructions[0xBC] = [this]() { cycles += 4;
        enableTestPageExceed = true;
        LDY(absxMode()); };
    instructions[0xA4] = [this]() { cycles += 3; LDY(zpMode()); };
    instructions[0xB4] = [this]() { cycles += 4; LDY(zpxMode()); };

    // DEC Instructions
    instructions[0xCE] = [this]() { cycles += 6; DEC(absMode()); };
    instructions[0xD6] = [this]() { cycles += 7; DEC(absxMode()); };
    instructions[0xC6] = [this]() { cycles += 5; DEC(zpMode()); };
    instructions[0xD6] = [this]() { cycles += 6; DEC(zpxMode()); };
    instructions[0xCA] = [this]() { cycles += 2; DEX(); };
    instructions[0x88] = [this]() { cycles += 2; DEY(); };

    // INC Instructions
    instructions[0xEE] = [this]() { cycles += 6; INC(absMode()); };
    instructions[0xFE] = [this]() { cycles += 7; INC(absxMode()); };
    instructions[0xE6] = [this]() { cycles += 5; INC(zpMode()); };
    instructions[0xF6] = [this]() { cycles += 6; INC(zpxMode()); };
    instructions[0xE8] = [this]() { cycles += 2; INX(); };
    instructions[0xC8] = [this]() { cycles += 2; INY(); };

    // Transfer Instructions
    instructions[0xAA] = [this]() { cycles += 2; TAX(); };
    instructions[0xA8] = [this]() { cycles += 2; TAY(); };
    instructions[0xBA] = [this]() { cycles += 2; TSX(); };
    instructions[0x8A] = [this]() { cycles += 2; TXA(); };
    instructions[0x9A] = [this]() { cycles += 2; TXS(); };
    instructions[0x98] = [this]() { cycles += 2; TYA(); };

    // Stack Instructions
    instructions[0x48] = [this]() { cycles += 3; PHA(); };
    instructions[0x08] = [this]() { cycles += 3; PHP(); };
    instructions[0x68] = [this]() { cycles += 4; PLA(); };
    instructions[0x28] = [this]() { cycles += 4; PLP(); };

    // Branch Instructions
    instructions[0x90] = [this]() { cycles += 2; BCC(relMode()); };
    instructions[0xB0] = [this]() { cycles += 2; BCS(relMode()); };
    instructions[0xF0] = [this]() { cycles += 2; BEQ(relMode()); };
    instructions[0x30] = [this]() { cycles += 2; BMI(relMode()); };
    instructions[0xD0] = [this]() { cycles += 2; BNE(relMode()); };
    instructions[0xD0] = [this]() { cycles += 2; BPL(relMode()); };
    instructions[0x00] = [this]() { cycles += 2; BRK(); };
    instructions[0x50] = [this]() { cycles += 2; BVC(relMode()); };
    instructions[0x70] = [this]() { cycles += 2; BVS(relMode()); };

    // Jump Instructions
    instructions[0x4C] = [this]() { cycles += 3; JMP(absMode()); };
    instructions[0x6C] = [this]() { cycles += 5; JMP(absiMode()); };
    instructions[0x20] = [this]() { cycles += 6; JSR(absMode()); };
    instructions[0x40] = [this]() { cycles += 6; RTI(); };
    instructions[0x90] = [this]() { cycles += 6; RTS(); };

    // Flag Instructions
    instructions[0x18] = [this]() { cycles += 2; CLC(); };
    instructions[0xD8] = [this]() { cycles += 2; CLD(); };
    instructions[0x58] = [this]() { cycles += 2; CLI(); };
    instructions[0xB8] = [this]() { cycles += 2; CLV(); };
    instructions[0x38] = [this]() { cycles += 2; SEC(); };
    instructions[0xF8] = [this]() { cycles += 2; SED(); };
    instructions[0x78] = [this]() { cycles += 2; SEI(); };

    // No operation
    instructions[0xEA] = [this]() { cycles += 2; NOP(); };
}

/*
 * OR; Memory with Accumulator
 * Flags affected: N, Z
 * Z: Is set when result in accumulator is 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::ORA(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    reg->A |= value;
    reg->Flags.setZ(value);
    reg->Flags.setN(value);
}

/*
 * AND; Memory with Accumulator
 * Flags affected: N, Z
 * Z: Is set when result in accumulator is 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::AND(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    reg->A &= value;

    reg->Flags.setZ(value);
    reg->Flags.setN(value);
}

/*
 * Exclusive OR; Memory with Accumulator
 * Flags affected: N, Z
 * Z: Is set when result in accumulator is 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::EOR(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    reg->A ^= value;

    reg->Flags.setZ(reg->A);
    reg->Flags.setN(reg->A);
}

/*
 * Add Memory to Accumulator with Carry
 * Flags affected: N, V, Z, C
 * V: Is set when result exceeds +127 or -127, otherwise reset
 * Z: Is set when result in accumulator is 0
 * C: Is set when result is greater than or equal to 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::ADC(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    uint16_t sum = reg->A + value + reg->Flags.C;
    reg->Flags.C = (sum > 0xFF);

    reg->A = static_cast<uint8_t>(sum & 0xFF);

    reg->Flags.setZ(reg->A);
    reg->Flags.setN(reg->A);
}

/*
 * Store Accumulator in Memory
 */
void CPU::STA(uint16_t addr) {
    memory->writeByte(reg->A, addr);
}

/*
 * Load Accumulator with Memory
 * Flags affected: N, Z
 * Z: Is set when result in accumulator is 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::LDA(uint16_t addr) {
    reg->A = memory->readByte(addr);

    reg->Flags.setN(reg->A);
    reg->Flags.setZ(reg->A);
}

/*
 * Compare Instruction
 * Flags affected: Z, C, N
 * Z: Is set on an equal comparison, otherwise reset
 * C: If value is less or equal to the accumulator
 * N: If result bit 7 is set
 */
void CPU::CMP(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    uint16_t result = static_cast<uint16_t>(reg->A) - static_cast<uint16_t>(value);

    reg->Flags.C = (reg->A >= value);
    reg->Flags.Z = result == 0;
    reg->Flags.N = result & 0x80;
}

void CPU::CPX(uint16_t addr) {
    uint8_t value = memory->readByte(addr);

    reg->Flags.C = (reg->X >= value);
    reg->Flags.Z = (reg->X == value);
    reg->Flags.N = (reg->X - value) & 0x80;
}

void CPU::CPY(uint16_t addr) {
    uint8_t value = memory->readByte(addr);

    reg->Flags.C = (reg->Y >= value);
    reg->Flags.Z = (reg->Y == value);
    reg->Flags.N = (reg->Y - value) & 0x80;
}

/*
 * Subtract Memory from Accumulator with Borrow
 * Flags affected: V, Z, C, N
 * V: Is set when result exceeds +127 or -127, otherwise reset
 * Z: Is set when result in accumulator is 0
 * C: Is set when result is greater than or equal to 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::SBC(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    uint16_t diff = static_cast<uint16_t>(reg->A) - static_cast<uint16_t>(value) - ~reg->Flags.C;

    reg->A = static_cast<uint8_t>(diff & 0xFF);

    reg->Flags.C = (diff <= 0xFF);
    reg->Flags.V = ((reg->A ^ value) & 0x80) && ((reg->A ^ diff) & 0x80);
    reg->Flags.setZ(reg->A);
    reg->Flags.setN(reg->A);
}

/*
 * Arithmetic Shift Left
 * Flags affected: N, Z, C
 * Z: Is set when result in accumulator is 0
 * C: Stores bit 7 before shift
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::ASL(uint16_t addr) {
    uint8_t value = memory->readByte(addr);

    reg->Flags.C = (value & 0x80);
    value <<= 1;
    memory->writeByte(value, addr);
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}

void CPU::ASL_A() {
    uint8_t value = reg->A;
    reg->Flags.C = (value & 0x80);
    value <<= 1;
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}

/*
 * Rotate Left
 * Flags affected: N, Z, C
 * Z: Is set when result in accumulator is 0
 * C: Stores bit 7 before shift
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::ROL(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    uint8_t carry = reg->Flags.C;

    reg->Flags.C = (value & 0x80);
    value = (value << 1) | carry;
    memory->writeByte(value, addr);
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}

void CPU::ROL_A() {
    uint8_t value = reg->A;
    uint8_t carry = reg->Flags.C;

    reg->Flags.C = (value & 0x80);
    value = (value << 1) | carry;
    reg->A = value;
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}

/*
 * Logical Shift Right
 * Flags affected:
 * Z: Is set when result in accumulator is 0
 * C: Stores bit 0 before shift
 * N: Is set when the result in the accumulator has bit 7 set (basically 0)
 */
void CPU::LSR(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    reg->Flags.C = (value & 0x01);
    value >>= 1;
    memory->writeByte(value, addr);
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}

void CPU::LSR_A() {
    uint8_t value = reg->A;
    reg->Flags.C = (value & 0x01);
    value >>= 1;
    reg->A = value;
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}


/*
 * Rotate Right
 * Flags affected: N, Z, C
 * Z: Is set when result in accumulator is 0
 * C: Stores bit 7 before shift
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::ROR(uint16_t addr) {
    uint8_t value = memory->readByte(addr);

    uint8_t carry = reg->Flags.C;
    reg->Flags.C = (value & 0x01);
    value = (value >> 1) | (carry << 7);

    memory->writeByte(value, addr);
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}

void CPU::ROR_A(){
    uint8_t value = reg->A;

    uint8_t carry = reg->Flags.C;
    reg->Flags.C = (value & 0x01);
    value = (value >> 1) | (carry << 7);
    reg->A = value;
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}
/*
 * Store Index Register X in Memory
 */
void CPU::STX(uint16_t addr) {
    memory->writeByte(reg->X, addr);
}

/*
 * Store Index Register Y in Memory
 */
void CPU::STY(uint16_t addr) {
    memory->writeByte(reg->Y, addr);
}

/*
 * Load Index Register X From Memory
 * Flags affected: N, Z
 *
 */
void CPU::LDX(uint16_t addr) {
    reg->X = memory->readByte(addr);
    reg->Flags.setN(reg->X);
    reg->Flags.setZ(reg->X);
}

/*
 * Load Index Register Y From Memory
 * Flags affected: N, Z
 *
 */
void CPU::LDY(uint16_t addr){
    reg->Y = memory->readByte(addr);
    reg->Flags.setN(reg->Y);
    reg->Flags.setZ(reg->Y);
}

/*
 * Decrement Memory By One
 * Flags affected: N, Z
 */
void CPU::DEC(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    value--;
    memory->writeByte(value, addr);
    reg->Flags.setZ(value);
    reg->Flags.setN(value);
}

void CPU::DEX() {
    reg->X--;
}

void CPU::DEY(){
    reg->Y--;
}

/*
 * Increment Memory By One
 * Flags affected: N, Z
 */
void CPU::INC(uint16_t addr) {
    uint8_t value = memory->readByte(addr);
    value++;
    memory->writeByte(value, addr);
    reg->Flags.setZ(value);
    reg->Flags.setN(value);
}

void CPU::INX() {
    reg->X++;
}

void CPU::INY() {
    reg->Y++;
}

/*
 * Test Bits in Memory with Accumulator
 * Flags affected: N, V, Z
 */
void CPU::BIT(uint16_t addr) {
    uint8_t value = memory->readByte(addr);

    reg->Flags.Z = ((reg->A & value) == 0);
    reg->Flags.V = (value & 0x40);
    reg->Flags.N = (value & 0x80);
}

/*
 * Transfer value from register 1 to 2
 * Flags affected: N, Z
 */
void CPU::TAX() {
    reg->X = reg->A;
    reg->Flags.setZ(reg->X);
    reg->Flags.setN(reg->X);
}

void CPU::TAY() {
    reg->Y = reg->A;
    reg->Flags.setN(reg->Y);
    reg->Flags.setZ(reg->Y);
}

void CPU::TSX() {
    reg->X = reg->SP;
    reg->Flags.setZ(reg->X);
    reg->Flags.setN(reg->X);
}

void CPU::TXA() {
    reg->A = reg->X;
    reg->Flags.setZ(reg->A);
    reg->Flags.setN(reg->A);
}

void CPU::TXS() {
    reg->SP = reg->X;
}

void CPU::TYA() {
    reg->A = reg->Y;
    reg->Flags.setZ(reg->A);
    reg->Flags.setN(reg->A);
}

/*
 * Push value from Register on Stack
 */
void CPU::PHA() {
    pushByte(reg->A);
}
void CPU::PHP() {
    pushByte(reg->Flags.getStatus());
}

/*
 * Pop value from Stack to Register
 */
void CPU::PLA() {
    reg->A = popByte();
}
void CPU::PLP() {
    reg->Flags.setStatus(popByte());
}

/*
 * Break Command
 * Flags affected: I
 */
void CPU::BRK() {
    pushWord(reg->PC);
    pushByte(reg->Flags.getStatus());

    reg->Flags.I = 0x01;
    // TODO Set PC to Interrupt vector address
}

/*
 * JMP Indirect
 */
void CPU::JMP(uint16_t addr) {
    reg->PC = addr;
}

/*
 * Jump to Subroutine
 */
void CPU::JSR(uint16_t addr) {
    // TODO CHECK IF CORRECT
    pushWord(reg->PC);
    reg->PC = addr;
}

/*
 * Return From Interrupt
 */
void CPU::RTI() {
    uint8_t status = popByte();
    reg->Flags.setStatus(status);
    reg->PC = popWord();
}

/*
 * Return From Subroutine
 */
void CPU::RTS() {
    reg->PC = popWord();
    reg->PC++;
}

/*
 * Clear Carry Flag
 * Flags affected: C
 */
void CPU::CLC() {
    reg->Flags.C = 0x00;
}

/*
 * Clear Decimal Mode
 * Flags affected: D
 */
void CPU::CLD() {
    reg->Flags.D = 0x00;
}

/*
 * Clear Interrupt Disable
 * Flags affected: I
 */
void CPU::CLI() {
    reg->Flags.I = 0x00;
}

/*
 *  Clear Overflow Flag
 *  Flags affected: V
 */
void CPU::CLV() {
    reg->Flags.V = 0x00;
}

/*
 * Set Carry Flag
 * Flags affected: C
 */
void CPU::SEC() {
    reg->Flags.C = 0x01;
}

/*
 * Set Decimal Flag
 * Flags affected: D
 */
void CPU::SED() {
    reg->Flags.D = 0x01;
}

/*
 * Set Interrupt Disable
 * Flags affected: I
 */
void CPU::SEI() {
    reg->Flags.I = 0x01;
}

/*
 * Branch on Carry Clear
 */
void CPU::BCC(uint16_t addr) {
    if(!reg->Flags.C){
        cycles++;
        // TODO Check Boundary
        if (checkPageExceed(addr, reg->PC))
            cycles++;

        reg->PC = addr;
    }
}

/*
 * Branch on Carry Set
 */
void CPU::BCS(uint16_t addr) {
    if(!reg->Flags.C){
        cycles++;
        // TODO Check Boundary
        if (checkPageExceed(addr, reg->PC))
            cycles++;

        reg->PC = addr;
    }
}

/*
 * Branch on Result Zero
 */
void CPU::BEQ(uint16_t addr) {
    if(reg->Flags.Z){
        cycles++;
        if(checkPageExceed(addr, reg->PC))
            cycles++;
        reg->PC = addr;
    }
}

/*
 * Branch on Result Minus
 */
void CPU::BMI(uint16_t addr) {
    if(reg->Flags.N){
        cycles++;
        if(checkPageExceed(addr, reg->PC))
            cycles++;

        reg->PC = addr;
    }
}

/*
 * Branch on Result Not Zero
 */
void CPU::BNE(uint16_t addr) {
    if(!reg->Flags.Z){
        cycles++;
        if(checkPageExceed(addr, reg->PC))
            cycles++;

        reg->PC = addr;
    }
}

/*
 * Branch on Result Plus
 */
void CPU::BPL(uint16_t addr) {
    if(!reg->Flags.N){
        cycles++;
        if(checkPageExceed(addr, reg->PC))
            cycles++;
        reg->PC = addr;
    }
}

/*
 * Branch on Overflow Clear
 */
void CPU::BVC(uint16_t addr) {
    if(!reg->Flags.V){
        cycles++;
        if(checkPageExceed(addr, reg->PC))
            cycles++;
        reg->PC = addr;
    }
}

/*
 * Branch on Overflow Set
 */
void CPU::BVS(uint16_t addr) {
    if(reg->Flags.V){
        cycles++;
        if(checkPageExceed(addr, reg->PC))
            cycles++;
        reg->PC = addr;
    }
}

/*
 * No Operation
 */
void CPU::NOP() {
    // 💥╾━╤デ╦︻ඞා
}