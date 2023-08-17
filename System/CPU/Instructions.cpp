//
// Created by leonv on 17/08/2023.
//

#include "CPU.h"

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

            reg->A |= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readWord(zeroPageAddress);

            reg->A |= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // immediate
        case 0x2:
            value = readNextByte();
            reg->A |= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            reg->A |= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->A |= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->A |= value;

            reg->Flags.setN(reg->A);
            reg->Flags.setZ(reg->A);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            effectiveAddress = address + reg->Y;
            value = memory->readByte(effectiveAddress);

            reg->A |= value;

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            effectiveAddress = address + reg->X;
            value = memory->readByte(effectiveAddress);

            reg->A |= value;

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

        default:
            break;
    }
}

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

            reg->A &= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readWord(zeroPageAddress);

            reg->A &= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // immediate
        case 0x2:
            value = readNextByte();
            reg->A &= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            reg->A &= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->A &= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->A &= value;

            reg->Flags.setN(reg->A);
            reg->Flags.setZ(reg->A);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            effectiveAddress = address + reg->Y;
            value = memory->readByte(effectiveAddress);

            reg->A &= value;

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            effectiveAddress = address + reg->X;
            value = memory->readByte(effectiveAddress);

            reg->A &= value;

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

        default:
            break;
    }
}

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

            reg->A ^= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readWord(zeroPageAddress);

            reg->A ^= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // immediate
        case 0x2:
            value = readNextByte();
            reg->A ^= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            reg->A ^= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->A ^= value;

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            reg->A ^= value;

            reg->Flags.setN(reg->A);
            reg->Flags.setZ(reg->A);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            effectiveAddress = address + reg->Y;
            value = memory->readByte(effectiveAddress);

            reg->A ^= value;

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            effectiveAddress = address + reg->X;
            value = memory->readByte(effectiveAddress);

            reg->A ^= value;

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

        default:
            break;
    }
}

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

            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            value = memory->readWord(zeroPageAddress);

            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // immediate
        case 0x2:
            value = readNextByte();

            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);
            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);

            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setZ(reg->A);
            reg->Flags.setN(reg->A);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setN(reg->A);
            reg->Flags.setZ(reg->A);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            effectiveAddress = address + reg->Y;
            value = memory->readByte(effectiveAddress);

            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            effectiveAddress = address + reg->X;
            value = memory->readByte(effectiveAddress);

            sum = reg->A + value + reg->Flags.C;
            reg->Flags.C = (sum > 0xFF);

            reg->A = static_cast<uint8_t>(sum & 0xFF);

            reg->Flags.setZ(value);
            reg->Flags.setN(value);
            break;

        default:
            break;
    }
}

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

            memory->writeByte(reg->A, effectiveAddress);
            break;

            // zero page
        case 0x1:
            zeroPageAddress = readNextByte();
            memory->writeByte(reg->A, zeroPageAddress);
            break;

            // absolute
        case 0x3:
            address = readNextWord();
            value = memory->readByte(address);

            memory->writeByte(reg->A,value);
            break;

            // (zero page), Y
        case 0x4:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->Y) & 0xFF;
            value = memory->readByte(effectiveAddress);

            memory->writeByte(reg->A, value);
            break;

            // zero page, X
        case 0x5:
            zeroPageAddress = readNextByte();
            effectiveAddress = (zeroPageAddress + reg->X) & 0xFF;
            value = memory->readByte(effectiveAddress);

            memory->writeByte(reg->A, value);
            break;

            // absolute, Y
        case 0x6:
            address = readNextWord();
            effectiveAddress = address + reg->Y;
            value = memory->readByte(effectiveAddress);

            memory->writeByte(reg->A, value);
            break;

            // absolute, X
        case 0x7:
            address = readNextWord();
            effectiveAddress = address + reg->X;
            value = memory->readByte(effectiveAddress);

            memory->writeByte(reg->A, value);
            break;

        default:
            break;
    }
}

void CPU::LDA(uint8_t bbb) {

}

void CPU::CMP(uint8_t bbb) {

}

void CPU::SBC(uint8_t bbb) {

}