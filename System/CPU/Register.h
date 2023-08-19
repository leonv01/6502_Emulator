//
// Created by leonv on 17/08/2023.
//

#ifndef INC_6502_EMULATOR_REGISTER_H
#define INC_6502_EMULATOR_REGISTER_H


#include <cstdint>
#include <string>
#include <sstream>

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
        void inline setZ(uint8_t value){
            Z = value == 0x00;
        }

        // If value is Negative, Negative-Flag is set
        void inline setN(uint8_t value){
            N = value & 0x80;
        }

        uint8_t getStatus() const {
            return ((C << 7) | (Z << 6) | (I << 5) | (D << 4) | (B << 3) | (_ << 2) | (V << 1) | N);
        }

        void setStatus(uint8_t value){
            C = value & 0x80;
            Z = value & 0x40;
            I = value & 0x20;
            D = value & 0x10;
            B = value & 0x08;
            _ = value & 0x04;
            V = value & 0x02;
            N = value & 0x01;
        }
    } Flags{};

    Register();

    ~Register() = default;

    std::string toString() const;
};


#endif //INC_6502_EMULATOR_REGISTER_H
