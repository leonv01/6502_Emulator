//
// Created by leonv on 17/08/2023.
//

#include <iostream>
#include "CPU.h"

uint16_t CPU::immMode() {
    return reg->PC;
}

uint16_t CPU::absMode() {
    return readNextWord();
}

uint16_t CPU::accMode(){

}

uint16_t CPU::absxMode(){
    uint16_t address = readNextWord();
    return address + reg->X;
}
uint16_t CPU::absyMode(){
    uint16_t address = readNextWord();
    return address + reg->Y;
}
uint16_t CPU::absiMode(){

}
uint16_t CPU::zpMode(){
    uint8_t zeroPageAddress = readNextByte();
    return (zeroPageAddress + reg->X) & 0xFF;
}
uint8_t zpyMode();
uint8_t zpxMode();
uint8_t zpxiMode();
uint8_t zpyiMode();
uint8_t relMode();



void CPU::defineInstructions() {
    instructions[0x00] = [this](){ BRK(0);};

    instructions[0x01] = [this](){ ORA(zpMode());};
    instructions[0x09] = [this](){ORA(immMode());};
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
    uint16_t sum;
    uint8_t value = memory->readByte(addr);
    uint16_t address;
  /*  switch (bbb) {

        // (zero page, X)
        case 0x0:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readWord(zeroPageAddress);
            break;

            // immediate
        case 0x2:
            value = readNextByte();
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            effectiveAddress = address + reg->Y;
            value = memory->readByte(effectiveAddress);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            effectiveAddress = address + reg->X;
            value = memory->readByte(effectiveAddress);
            break;

        default:
            return;
    }
    */
    sum = reg->A + value + reg->Flags.C;
    reg->Flags.C = (sum > 0xFF);

    reg->A = static_cast<uint8_t>(sum & 0xFF);

    reg->Flags.setZ(reg->A);
    reg->Flags.setN(reg->A);
}

/*
 * Store Accumulator in Memory
 */
void CPU::STA(uint16_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

    uint16_t absolute;
    uint16_t address;
    switch (bbb) {

        // (zero page, X)
        case 0x0:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            absolute = address + reg->Y;
            value = memory->readByte(absolute);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            absolute = address + reg->X;
            value = memory->readByte(absolute);
            break;

        default:
            return;
    }
    memory->writeByte(reg->A, value);
}

/*
 * Load Accumulator with Memory
 * Flags affected: N, Z
 * Z: Is set when result in accumulator is 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::LDA(uint16_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

    uint16_t absolute;
    uint16_t address;
    switch (bbb) {

        // (zero page, X)
        case 0x0:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);
            break;

            //immediate
        case 0x2:
            value = readNextByte();
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            absolute = address + reg->Y;
            value = memory->readByte(absolute);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            absolute = address + reg->X;
            value = memory->readByte(absolute);
            break;

        default:
            return;
    }
    reg->A = value;

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
void CPU::CMP(uint16_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

    uint16_t absolute;
    uint16_t address;
    uint16_t result;
    switch (bbb) {

        // (zero page, X)
        case 0x0:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);
            break;

            //immediate
        case 0x2:
            value = readNextByte();
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            absolute = address + reg->Y;
            value = memory->readByte(absolute);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            absolute = address + reg->X;
            value = memory->readByte(absolute);
            break;

        default:
            return;
    }
    result = static_cast<uint16_t>(reg->A) - static_cast<uint16_t>(value);

    reg->Flags.C = (reg->A >= value);
    reg->Flags.Z = result == 0;
    reg->Flags.N = result & 0x80;
}

/*
 * Subtract Memory from Accumulator with Borrow
 * Flags affected: V, Z, C, N
 * V: Is set when result exceeds +127 or -127, otherwise reset
 * Z: Is set when result in accumulator is 0
 * C: Is set when result is greater than or equal to 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::SBC(uint16_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

    uint16_t absolute;
    uint16_t address;
    uint16_t diff;
    switch (bbb) {

        // (zero page, X)
        case 0x0:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);
            break;

            //immediate
        case 0x2:
            value = readNextByte();
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            absolute = address + reg->Y;
            value = memory->readByte(absolute);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            absolute = address + reg->X;
            value = memory->readByte(absolute);
            break;

        default:
            return;
    }
    diff = static_cast<uint16_t>(reg->A) - static_cast<uint16_t>(value) - ~reg->Flags.C;

    reg->A = static_cast<uint8_t>(diff & 0xFF);

    reg->Flags.C = (diff <= 0xFF);
    reg->Flags.V = ((reg->A ^ value) & 0x80) && ((reg->A ^ diff) &  0x80);
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
void CPU::ASL(uint16_t bbb){
    uint8_t value;
    uint8_t zeroPageAddress;

    uint16_t address;
    uint16_t absolute;
    uint16_t effectiveAddress;
    switch(bbb){

            // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);

            reg->Flags.C = (value & 0x80);
            value <<= 1;

            memory->writeByte(value, zeroPageAddress);
            break;

            // accumulator
        case 0x02:
            value = reg->A;
            reg->Flags.C = (value & 0x80);
            value <<= 1;
            reg->A = value;
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            value = memory->readByte(address);
            reg->Flags.C = (value & 0x80);
            value <<= 1;
            memory->writeByte(value, address);
            break;

            // zero page, X
        case 0x05:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->Flags.C = (value & 0x80);
            value <<= 1;
            memory->writeByte(value, effectiveAddress);
            break;

            // absolute, X
        case 0x07:
            address = readNextWord();
            absolute = (address + reg->X);
            value = memory->readByte(absolute);

            reg->Flags.C = (value & 0x80);
            value <<= 1;
            memory->writeByte(value, absolute);
            break;
        default:
            return;
    }
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
void CPU::ROL(uint16_t bbb){
    uint8_t value;
    uint8_t zeroPageAddress;
    uint8_t carry;

    uint16_t absolute;
    uint16_t address;
    uint16_t effectiveAddress;
    switch(bbb){

            // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);

            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x80);
            value = (value << 1) | carry;

            memory->writeByte(value, zeroPageAddress);
            break;

            // accumulator
        case 0x02:
            value = reg->A;
            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x80);
            value = (value << 1) | carry;
            reg->A = value;
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            value = memory->readByte(address);
            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x80);
            value = (value << 1) | carry;
            memory->writeByte(value, address);
            break;

            // zero page, X
        case 0x05:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x80);
            value = (value << 1) | carry;
            memory->writeByte(value, effectiveAddress);
            break;

            // absolute, X
        case 0x07:
            address = readNextWord();
            absolute = (address + reg->X);
            value = memory->readByte(absolute);
            carry = reg->Flags.C;

            reg->Flags.C = (value & 0x80);
            value = (value << 1) | carry;
            memory->writeByte(value, absolute);
            break;
        default:
            return;
    }
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
void CPU::LSR(uint16_t bbb){
    uint8_t value;
    uint8_t zeroPageAddress;

    uint16_t absolute;
    uint16_t address;
    uint16_t effectiveAddress;
    switch(bbb){

            // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);

            reg->Flags.C = (value & 0x01);
            value >>= 1;

            memory->writeByte(value, zeroPageAddress);
            break;

            // accumulator
        case 0x02:
            value = reg->A;
            reg->Flags.C = (value & 0x01);
            value >>= 1;
            reg->A = value;
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            value = memory->readByte(address);
            reg->Flags.C = (value & 0x01);
            value >>= 1;
            memory->writeByte(value, address);
            break;

            // zero page, X
        case 0x05:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->Flags.C = (value & 0x01);
            value >>= 1;
            memory->writeByte(value, effectiveAddress);
            break;

            // absolute, X
        case 0x07:
            address = readNextWord();
            absolute = (address + reg->X);
            value = memory->readByte(absolute);

            reg->Flags.C = (value & 0x01);
            value >>= 1;
            memory->writeByte(value, absolute);
            break;
        default:
            return;
    }
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
void CPU::ROR(uint16_t bbb){
    uint8_t value;
    uint8_t zeroPageAddress;
    uint8_t carry;

    uint16_t absolute;
    uint16_t address;
    uint16_t effectiveAddress;
    switch(bbb){

            // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);

            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x01);
            value = (value >> 1) | (carry << 7);

            memory->writeByte(value, zeroPageAddress);
            break;

            // accumulator
        case 0x02:
            value = reg->A;
            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x01);
            value = (value >> 1) | (carry << 7);
            reg->A = value;
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            value = memory->readByte(address);
            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x01);
            value = (value >> 1) | (carry << 7);
            memory->writeByte(value, address);
            break;

            // zero page, X
        case 0x05:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x01);
            value = (value >> 1) | (carry << 7);
            memory->writeByte(value, effectiveAddress);
            break;

            // absolute, X
        case 0x07:
            address = readNextWord();
            absolute = (address + reg->X);
            value = memory->readByte(absolute);

            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x01);
            value = (value >> 1) | (carry << 7);

            memory->writeByte(value, absolute);
            break;
        default:
            return;
    }
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}

/*
 * Store Index Register X in Memory
 */
void CPU::STX(uint16_t bbb){
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;

    uint16_t address;
    switch (bbb) {

            // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            memory->writeByte(reg->X, zeroPageAddress);
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            memory->writeByte(reg->X, address);
            break;

            // zero page, Y
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            memory->writeByte(reg->X, effectiveAddress);
            break;
        default:
            break;
    }
}

/*
 * Load Index Register X From Memory
 * Flags affected: N, Z
 *
 */
void CPU::LDX(uint16_t bbb){
    uint8_t value;
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;

    uint16_t absolute;
    uint16_t address;
    switch (bbb) {

            // immediate
        case 0x00:
            value = readNextByte();
            reg->X = value;
            break;

            // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            reg->X = memory->readByte(zeroPageAddress);
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            reg->X = memory->readByte(address);
            break;

            // zero page, Y
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            reg->X = memory->readByte(effectiveAddress);
            break;

            // absolute, Y
        case 0x07:
            address = readNextWord();
            absolute = address + reg->Y;
            reg->X = memory->readByte(absolute);
            break;

        default:
            return;
    }
    reg->Flags.setN(reg->X);
    reg->Flags.setZ(reg->X);
}

/*
 * Decrement Memory By One
 * Flags affected: N, Z
 */
void CPU::DEC(uint16_t bbb){
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

    uint16_t absolute;
    uint16_t address;
    switch(bbb){

            // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);
            value--;
            memory->writeByte(value, zeroPageAddress);
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            value = memory->readByte(address);
            value--;
            memory->writeByte(value, address);
            break;

            // zero page, X
        case 0x05:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            value--;
            memory->writeByte(value, effectiveAddress);
            break;

            // absolute, X
        case 0x07:
            address = readNextWord();
            absolute = (address + reg->X);
            value = memory->readByte(absolute);
            value--;
            memory->writeByte(value, absolute);
            break;
        default:
            return;
    }
    reg->Flags.setZ(value);
    reg->Flags.setN(value);
}

/*
 * Increment Memory By One
 * Flags affected: N, Z
 */
void CPU::INC(uint16_t bbb){
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

    uint16_t absolute;
    uint16_t address;
    switch(bbb){

        // zero page
        case 0x01:
            zeroPageAddress = readNextByte();
            value = memory->readByte(zeroPageAddress);
            value++;
            memory->writeByte(value, zeroPageAddress);
            break;

            // absolute
        case 0x03:
            address = readNextWord();
            value = memory->readByte(address);
            value++;
            memory->writeByte(value, address);
            break;

            // zero page, X
        case 0x05:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);
            value++;
            memory->writeByte(value, effectiveAddress);
            break;

            // absolute, X
        case 0x07:
            address = readNextWord();
            absolute = (address + reg->X);
            value = memory->readByte(absolute);
            value++;
            memory->writeByte(value, absolute);
            break;
        default:
            return;
    }
    reg->Flags.setZ(value);
    reg->Flags.setN(value);
}