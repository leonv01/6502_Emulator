//
// Created by leonv on 17/08/2023.
//

#include "CPU.h"

CPU::CPU() {
    currentOpcode = 0;
    reg = new Register();
    memory = new Memory();
    opcodeTable = {
            {0x01, std::bind(&CPU::handleGroupOneInstructions, this)}
    };
}
CPU::CPU(Memory *memory) {
    currentOpcode = 0;
    reg = new Register();
    this->memory = memory;
}

CPU::~CPU(){
    delete reg;
}

void CPU::cpuStep() {
    currentOpcode = readNextByte();
    parseOpcode();
}

void CPU::parseOpcode() {
    uint8_t cc = (currentOpcode & 0x03);
    switch (cc) {
        case 0x00:
            break;
        case 0x01:
            handleGroupOneInstructions();
            break;
        case 0x02:
            break;
        case 0x03:
            break;
        default:
            break;
    }
}

void CPU::handleGroupOneInstructions() {
    uint8_t aaa = (currentOpcode & 0xE0) >> 5;
    uint8_t bbb = (currentOpcode & 0x1C) >> 2;

    switch(aaa){
        case 0x00:
            ORA(bbb);
            break;
        case 0x01:
            AND(bbb);
            break;
        case 0x02:
            EOR(bbb);
            break;
        case 0x03:
            ADC(bbb);
            break;
        case 0x04:
            STA(bbb);
            break;
        case 0x05:
            LDA(bbb);
            break;
        case 0x06:
            CMP(bbb);
            break;
        case 0x07:
            SBC(bbb);
            break;
        default:
            break;
    }
}

uint8_t CPU::readNextByte() {
    uint8_t byte = memory->readByte(reg->PC);
    reg->PC++;
    return byte;
}

uint16_t CPU::readNextWord() {
    uint8_t lowByte = readNextByte();
    uint8_t highByte = readNextByte();
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

uint16_t CPU::indirectAddressing(uint8_t value, uint8_t reg) {
    uint16_t indirectAddress = (memory->readByte(value + reg)
            + (memory->readByte(value + reg + 1) << 8));
    return 0;
}


