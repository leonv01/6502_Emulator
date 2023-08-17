//
// Created by leonv on 17/08/2023.
//

#ifndef INC_6502_EMULATOR_MEMORY_H
#define INC_6502_EMULATOR_MEMORY_H


#include <cstdint>
#include <vector>

class Memory {
private:
    uint8_t* memory;
public:
    Memory();
    explicit Memory(size_t size);

    ~Memory();

    uint8_t readByte(uint16_t address);
    uint16_t readWord(uint16_t address);

    void writeByte(uint8_t value, uint16_t address);
    void writeWord(uint16_t value, uint16_t address);

};


#endif //INC_6502_EMULATOR_MEMORY_H
