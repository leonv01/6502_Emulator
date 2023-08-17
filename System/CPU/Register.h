//
// Created by leonv on 17/08/2023.
//

#ifndef INC_6502_EMULATOR_REGISTER_H
#define INC_6502_EMULATOR_REGISTER_H


#include <cstdint>

class Register {
private:

public:
    uint16_t PC;    // Program Counter
    uint8_t A;      // Accumulator
    uint8_t X;      // X Register
    uint8_t Y;      // Y Register
    uint8_t SP;     // Stack Pointer
    struct {
        uint8_t C; // Carry Flag
        uint8_t Z; // Zero Flag
        uint8_t I; // Interrupt Disable
        uint8_t D; // Decimal Mode
        uint8_t B; // Break Command
        uint8_t _; // Unused
        uint8_t V; // Overflow Flag
        uint8_t N; // Negative Flag

        // If value is Zero, Zero-Flag is set
        void setZ(uint8_t value){
            Z = value == 0x00 ? 0x01 : 0x00;
        }

        // If value is Negative, Negative-Flag is set
        void setN(uint8_t value){
            N = value & 0x80;
        }
    } Flags{};

    Register();

    ~Register() = default;
};


#endif //INC_6502_EMULATOR_REGISTER_H
