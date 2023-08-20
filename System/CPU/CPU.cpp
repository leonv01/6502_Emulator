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
    enableTestPageExceed = false;
    systemRun = true;
    cycles = 0;
}
CPU::CPU(Memory *memory) {
    currentOpcode = 0;
    reg = new Register();
    this->memory = memory;
    instructions = std::unordered_map<uint8_t, std::function<void()>>(256);
    defineInstructions();
    enableTestPageExceed = false;
    systemRun = true;
    cycles = 0;
}

CPU::~CPU(){
    delete reg;
}

void CPU::cpuRun() {
    uint8_t opcode;

    while(systemRun) {
        uint32_t remaining = 500000;
        auto startTime = std::chrono::high_resolution_clock::now();
        while (remaining > 0) {

            // Fetch next instruction
            opcode = readNextByte();

            // Execute instruction
            instructions[opcode]();
            remaining -= cycles;
            reg->PC++;
            cycles = 0;
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        std::cout << "Time taken: " << duration << " microseconds" << std::endl;
    }
}

void CPU::cpuStep() {
    currentOpcode = readNextByte();
    instructions[currentOpcode]();
    reg->PC++;
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

void CPU::pushByte(uint8_t value) {
    if(reg->SP <= 0x00) reg->SP = 0xFF;
    else reg->SP--;
    memory->writeByte(reg->SP + 0x0100, value);
}
void CPU::pushWord(uint16_t value) {
    pushByte((value >> 8) & 0xFF);
    pushByte(value & 0xFF);
}

uint8_t CPU::popByte() {
    if(reg->SP >= 0xFF) reg->SP = 0x00;
    else reg->SP++;
    return memory->readByte(reg->SP + 0x0100);
}
uint16_t CPU::popWord() {
    uint8_t lowByte = popByte();
    uint8_t highByte = popByte();
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}



void CPU::printStatus() {
    std::cout << reg->toString() << "Cycle: " << static_cast<int>(cycles) << std::endl;
}








