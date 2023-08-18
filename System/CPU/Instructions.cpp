//
// Created by leonv on 17/08/2023.
//

#include "CPU.h"

/*
 * OR; Memory with Accumulator
 * Flags affected: N, Z
 * Z: Is set when result in accumulator is 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::ORA(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

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
void CPU::AND(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

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
void CPU::EOR(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

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
void CPU::ADC(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

    uint16_t sum;

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
    sum = reg->A + value + reg->Flags.C;
    reg->Flags.C = (sum > 0xFF);

    reg->A = static_cast<uint8_t>(sum & 0xFF);

    reg->Flags.setZ(reg->A);
    reg->Flags.setN(reg->A);
}

/*
 * Store Accumulator in Memory
 */
void CPU::STA(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

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
    memory->writeByte(reg->A, value);
}

/*
 * Load Accumulator with Memory
 * Flags affected: N, Z
 * Z: Is set when result in accumulator is 0
 * N: Is set when the result in the accumulator has bit 7 set
 */
void CPU::LDA(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

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
void CPU::CMP(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

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
void CPU::SBC(uint8_t bbb) {
    uint8_t zeroPageAddress;
    uint8_t effectiveAddress;
    uint8_t value;

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
void CPU::ASL(uint8_t bbb){
    uint8_t value;
    uint8_t zeroPageAddress;

    uint16_t address;
    uint16_t effectiveAddress;
    switch(bbb){

            // immediate
        case 0x00:
            value = readNextByte();

            reg->Flags.C = (value & 0x80);
            value <<= 1;
            reg->A = value;
            break;

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
            effectiveAddress = (address + reg->X);
            value = memory->readByte(effectiveAddress);

            reg->Flags.C = (value & 0x80);
            value <<= 1;
            memory->writeByte(value, effectiveAddress);
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
void CPU::ROL(uint8_t bbb){
    uint8_t value;
    uint8_t zeroPageAddress;
    uint8_t carry;

    uint16_t address;
    uint16_t effectiveAddress;
    switch(bbb){

        // immediate
        case 0x00:
            value = readNextByte();

            carry = reg->Flags.C;
            reg->Flags.C = (value & 0x80);
            value = (value << 1) | carry;

            reg->A = value;
            break;

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
            effectiveAddress = (address + reg->X);
            value = memory->readByte(effectiveAddress);
            carry = reg->Flags.C;

            reg->Flags.C = (value & 0x80);
            value = (value << 1) | carry;
            memory->writeByte(value, effectiveAddress);
            break;
        default:
            return;
    }
    reg->Flags.setN(value);
    reg->Flags.setZ(value);
}
void LSR(uint8_t bbb);
void ROR(uint8_t bbb);
void STX(uint8_t bbb);
void LDX(uint8_t bbb);
void DEC(uint8_t bbb);
void INC(uint8_t bbb);