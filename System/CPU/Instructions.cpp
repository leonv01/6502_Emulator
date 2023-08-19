//
// Created by leonv on 17/08/2023.
//

#include "CPU.h"

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
    return address + reg->X;
}

uint16_t CPU::absyMode() {
    uint16_t address = readNextWord();
    return address + reg->Y;
}

uint16_t CPU::absiMode() {
    return 0;
}

uint16_t CPU::zpMode() {
    return readNextByte();
}

uint16_t CPU::zpyMode() {
    uint8_t zeroPageAddress = readNextByte();
    return (zeroPageAddress + reg->Y) & 0xFF;
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
    instructions[0x09] = [this]() { ORA(immMode()); };
    instructions[0x0D] = [this]() { ORA(absMode()); };
    instructions[0x1D] = [this]() { ORA(absxMode()); };
    instructions[0x19] = [this]() { ORA(absyMode()); };
    instructions[0x05] = [this]() { ORA(zpMode()); };
    instructions[0x15] = [this]() { ORA(zpxMode()); };
    instructions[0x01] = [this]() { ORA(zpxiMode()); };
    instructions[0x11] = [this]() { ORA(zpyiMode()); };

    // AND Instructions
    instructions[0x29] = [this]() { AND(immMode()); };
    instructions[0x2D] = [this]() { AND(absMode()); };
    instructions[0x3D] = [this]() { AND(absxMode()); };
    instructions[0x39] = [this]() { AND(absyMode()); };
    instructions[0x25] = [this]() { AND(zpMode()); };
    instructions[0x35] = [this]() { AND(zpxMode()); };
    instructions[0x21] = [this]() { AND(zpxiMode()); };
    instructions[0x31] = [this]() { AND(zpyiMode()); };

    // BIT Instructions
    instructions[0x2C] = [this]() { BIT(absMode()); };
    instructions[0x24] = [this]() { BIT(zpMode()); };

    // EOR Instructions
    instructions[0x49] = [this]() { EOR(immMode()); };
    instructions[0x4D] = [this]() { EOR(absMode()); };
    instructions[0x5D] = [this]() { EOR(absxMode()); };
    instructions[0x59] = [this]() { EOR(absyMode()); };
    instructions[0x45] = [this]() { EOR(zpMode()); };
    instructions[0x55] = [this]() { EOR(zpxMode()); };
    instructions[0x41] = [this]() { EOR(zpxiMode()); };
    instructions[0x51] = [this]() { EOR(zpyiMode()); };

    // ADC Instructions
    instructions[0x69] = [this]() { ADC(immMode()); };
    instructions[0x6D] = [this]() { ADC(absMode()); };
    instructions[0x7D] = [this]() { ADC(absxMode()); };
    instructions[0x79] = [this]() { ADC(absyMode()); };
    instructions[0x65] = [this]() { ADC(zpMode()); };
    instructions[0x75] = [this]() { ADC(zpxMode()); };
    instructions[0x61] = [this]() { ADC(zpxiMode()); };
    instructions[0x71] = [this]() { ADC(zpyiMode()); };

    // STA Instructions
    instructions[0x8D] = [this]() { STA(absMode()); };
    instructions[0x9D] = [this]() { STA(absxMode()); };
    instructions[0x99] = [this]() { STA(absyMode()); };
    instructions[0x85] = [this]() { STA(zpMode()); };
    instructions[0x95] = [this]() { STA(zpxMode()); };
    instructions[0x81] = [this]() { STA(zpxiMode()); };
    instructions[0x91] = [this]() { STA(zpyiMode()); };

    // LDA Instructions
    instructions[0xA9] = [this]() { LDA(immMode()); };
    instructions[0xAD] = [this]() { LDA(absMode()); };
    instructions[0xBD] = [this]() { LDA(absxMode()); };
    instructions[0xB9] = [this]() { LDA(absyMode()); };
    instructions[0xA5] = [this]() { LDA(zpMode()); };
    instructions[0xB5] = [this]() { LDA(zpxMode()); };
    instructions[0xA1] = [this]() { LDA(zpxiMode()); };
    instructions[0xB1] = [this]() { LDA(zpyiMode()); };

    // CMP Instructions
    instructions[0xC9] = [this]() { CMP(immMode()); };
    instructions[0xCD] = [this]() { CMP(absMode()); };
    instructions[0xDD] = [this]() { CMP(absxMode()); };
    instructions[0xD9] = [this]() { CMP(absyMode()); };
    instructions[0xC5] = [this]() { CMP(zpMode()); };
    instructions[0xD5] = [this]() { CMP(zpxMode()); };
    instructions[0xC1] = [this]() { CMP(zpxiMode()); };
    instructions[0xD1] = [this]() { CMP(zpyiMode()); };

    // CPX Instructions
    instructions[0xE0] = [this]() { CPX(immMode()); };
    instructions[0xEC] = [this]() { CPX(absMode()); };
    instructions[0xE4] = [this]() { CPX(zpMode()); };

    // CPY Instructions
    instructions[0xC0] = [this]() { CPY(immMode()); };
    instructions[0xCC] = [this]() { CPY(absMode()); };
    instructions[0xC4] = [this]() { CPY(zpMode()); };

    // SBC Instructions
    instructions[0xE9] = [this]() { SBC(immMode()); };
    instructions[0xED] = [this]() { SBC(absMode()); };
    instructions[0xFD] = [this]() { SBC(absxMode()); };
    instructions[0xF9] = [this]() { SBC(absyMode()); };
    instructions[0xE5] = [this]() { SBC(zpMode()); };
    instructions[0xF5] = [this]() { SBC(zpxMode()); };
    instructions[0xE1] = [this]() { SBC(zpxiMode()); };
    instructions[0xF1] = [this]() { SBC(zpyiMode()); };

    // ASL Instructions
    instructions[0x0A] = [this]() { ASL_A(); };
    instructions[0x0E] = [this]() { ASL(absMode()); };
    instructions[0x1E] = [this]() { ASL(absxMode()); };
    instructions[0x06] = [this]() { ASL(zpMode()); };
    instructions[0x16] = [this]() { ASL(zpxMode()); };

    // ROL Instructions
    instructions[0x2A] = [this]() { ROL_A(); };
    instructions[0x2E] = [this]() { ROL(absMode()); };
    instructions[0x3E] = [this]() { ROL(absxMode()); };
    instructions[0x26] = [this]() { ROL(zpMode()); };
    instructions[0x36] = [this]() { ROL(zpxMode()); };

    // LSR Instructions
    instructions[0x4A] = [this]() { LSR_A(); };
    instructions[0x4E] = [this]() { LSR(absMode()); };
    instructions[0x5E] = [this]() { LSR(absxMode()); };
    instructions[0x46] = [this]() { LSR(zpMode()); };
    instructions[0x56] = [this]() { LSR(zpxMode()); };

    // ROR Instructions
    instructions[0x6A] = [this]() { ROR_A(); };
    instructions[0x6E] = [this]() { ROR(absMode()); };
    instructions[0x7E] = [this]() { ROR(absxMode()); };
    instructions[0x66] = [this]() { ROR(zpMode()); };
    instructions[0x76] = [this]() { ROR(zpxMode()); };

    // STX Instructions
    instructions[0x8E] = [this]() { STX(absMode()); };
    instructions[0x86] = [this]() { STX(zpMode()); };
    instructions[0x96] = [this]() { STX(zpyMode()); };

    // STY Instructions
    instructions[0x8C] = [this]() { STY(absMode()); };
    instructions[0x84] = [this]() { STY(zpMode()); };
    instructions[0x94] = [this]() { STY(zpxMode()); };

    // LDX Instructions
    instructions[0xA2] = [this]() { LDX(immMode()); };
    instructions[0xAE] = [this]() { LDX(absMode()); };
    instructions[0xBE] = [this]() { LDX(absyMode()); };
    instructions[0xA6] = [this]() { LDX(zpMode()); };
    instructions[0xB6] = [this]() { LDX(zpyMode()); };

    // LDY Instructions
    instructions[0xA0] = [this]() { LDY(immMode()); };
    instructions[0xAC] = [this]() { LDY(absMode()); };
    instructions[0xBC] = [this]() { LDY(absxMode()); };
    instructions[0xA4] = [this]() { LDY(zpMode()); };
    instructions[0xB4] = [this]() { LDY(zpxMode()); };

    // DEC Instructions
    instructions[0xCE] = [this]() { DEC(absMode()); };
    instructions[0xD6] = [this]() { DEC(absxMode()); };
    instructions[0xC6] = [this]() { DEC(zpMode()); };
    instructions[0xD6] = [this]() { DEC(zpxMode()); };
    instructions[0xCA] = [this]() { DEX(); };
    instructions[0x88] = [this]() { DEY(); };

    // INC Instructions
    instructions[0xEE] = [this]() { INC(absMode()); };
    instructions[0xFE] = [this]() { INC(absxMode()); };
    instructions[0xE6] = [this]() { INC(zpMode()); };
    instructions[0xF6] = [this]() { INC(zpxMode()); };
    instructions[0xE8] = [this]() { INX(); };
    instructions[0xC8] = [this]() { INY(); };

    // Transfer Instructions
    instructions[0xAA] = [this]() { TAX(); };
    instructions[0xA8] = [this]() { TAY(); };
    instructions[0xBA] = [this]() { TSX(); };
    instructions[0x8A] = [this]() { TXA(); };
    instructions[0x9A] = [this]() { TXS(); };
    instructions[0x98] = [this]() { TYA(); };

    // Stack Instructions
    instructions[0x48] = [this]() { PHA(); };
    instructions[0x08] = [this]() { PHP(); };
    instructions[0x68] = [this]() { PLA(); };
    instructions[0x28] = [this]() { PLP(); };

    // Branch Instructions
    instructions[0x90] = [this]() { BCC(relMode()); };
    instructions[0xB0] = [this]() { BCS(relMode()); };
    instructions[0xF0] = [this]() { BEQ(relMode()); };
    instructions[0x30] = [this]() { BMI(relMode()); };
    instructions[0xD0] = [this]() { BNE(relMode()); };
    instructions[0xD0] = [this]() { BPL(relMode()); };
    instructions[0x00] = [this]() { BRK(); };
    instructions[0x50] = [this]() { BVC(relMode()); };
    instructions[0x70] = [this]() { BVS(relMode()); };

    // Jump Instructions
    instructions[0x4C] = [this]() { JMP(absMode()); };
    instructions[0x6C] = [this]() { JMP(absiMode()); };
    instructions[0x20] = [this]() { JSR(absMode()); };
    instructions[0x40] = [this]() { RTI(); };
    instructions[0x90] = [this]() { RTS(); };

    // Flag Instructions
    instructions[0x18] = [this]() { CLC(); };
    instructions[0xD8] = [this]() { CLD(); };
    instructions[0x58] = [this]() { CLI(); };
    instructions[0xB8] = [this]() { CLV(); };
    instructions[0x38] = [this]() { SEC(); };
    instructions[0xF8] = [this]() { SED(); };
    instructions[0x78] = [this]() { SEI(); };

    // No operation
    instructions[0xEA] = [this]() { NOP(); };
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
        if (false){
            cycles++;
        }
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
        if (false){
            cycles++;
        }
        reg->PC = addr;
    }
}

/*
 * Branch on Result Zero
 */
void CPU::BEQ(uint16_t addr) {
    if(reg->Flags.Z){
        cycles++;
        if(false){
            cycles++;
        }
        reg->PC = addr;
    }
}

/*
 * Branch on Result Minus
 */
void CPU::BMI(uint16_t addr) {
    if(reg->Flags.N){
        cycles++;
        if(false){
            cycles++;
        }
        reg->PC = addr;
    }
}

/*
 * Branch on Result Not Zero
 */
void CPU::BNE(uint16_t addr) {
    if(!reg->Flags.Z){
        cycles++;
        if(false){
            cycles++;
        }
        reg->PC = addr;
    }
}