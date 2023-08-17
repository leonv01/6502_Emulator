//
// Created by leonv on 17/08/2023.
//

#include "Memory.h"

Memory::Memory() {
    memory = new uint8_t[0xFFFF];
}
Memory::Memory(size_t size) {
    memory = new uint8_t[size];
}
Memory::~Memory(){
    delete memory;
}

uint8_t Memory::readByte(uint16_t address) {
    return memory[address];
}

uint16_t Memory::readWord(uint16_t address) {
    // TODO Implement Check for Boundaries
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

void Memory::writeByte(uint8_t value, uint16_t address) {
    memory[address] = value;
}

void Memory::writeWord(uint16_t value, uint16_t address) {
    uint8_t lowByte = value & 0xFF;
    uint8_t highByte = value >> 8;
    memory[address] = lowByte;
    memory[address + 1] = highByte;
}
