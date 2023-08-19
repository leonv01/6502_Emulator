//
// Created by leonv on 17/08/2023.
//

#include <iostream>
#include "CPU.h"

CPU::CPU() {
    currentOpcode = 0;
    reg = new Register();
    memory = new Memory();
    instructions = std::unordered_map<uint8_t, std::function<void()>>(256);
    defineInstructions();
}
CPU::CPU(Memory *memory) {
    currentOpcode = 0;
    reg = new Register();
    this->memory = memory;
    instructions = std::unordered_map<uint8_t, std::function<void()>>(256);
    defineInstructions();
}

CPU::~CPU(){
    delete reg;
}

void CPU::cpuStep() {
    currentOpcode = readNextByte();
    instructions[currentOpcode]();
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
            handleGroupTwoInstructions();
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

void CPU::handleGroupTwoInstructions() {
    uint8_t aaa = (currentOpcode & 0xE0) >> 5;
    uint8_t bbb = (currentOpcode & 0x1C) >> 2;

    switch(aaa){
        case 0x00:
            ASL(bbb);
            break;
        case 0x01:
            ROL(bbb);
            break;
        case 0x02:
            LSR(bbb);
            break;
        case 0x03:
            ROR(bbb);
            break;
        case 0x04:
            STX(bbb);
            break;
        case 0x05:
            LDX(bbb);
            break;
        case 0x06:
            DEC(bbb);
            break;
        case 0x07:
            INC(bbb);
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


void CPU::printStatus() {
    std::cout << reg->toString();
}








