//
// Created by leonv on 17/08/2023.
//

#include "Register.h"

Register::Register() {
    A = 0;
    X = 0;
    Y = 0;
    SP = 0;
    PC = 0;

    Flags.C = 0x00;
    Flags.Z = 0x01;
    Flags.I = 0x00;
    Flags.D = 0x00;
    Flags.B = 0x00;
    Flags._ = 0x01;
    Flags.V = 0x00;
    Flags.N = 0x01;
}

std::string Register::toString() const {
    std::ostringstream oss;
    oss <<
        "PC: 0x" << std::hex << static_cast<uint16_t>(PC) << " " <<
        "SP: 0x" << std::hex << static_cast<uint8_t>(SP)  << " " <<
        "A: 0x" << std::hex << static_cast<uint8_t>(A) << " " <<
        "X: 0x" << std::hex << static_cast<uint8_t>(X) << " " <<
        "Y: 0x" << std::hex << static_cast<uint8_t>(Y) << std::endl <<
        "Flags: " <<
        "C: " << std::hex << static_cast<uint8_t>(Flags.C) << " " <<
        "Z: " << std::hex << static_cast<uint8_t>(Flags.Z) << " " <<
        "I: " << std::hex << static_cast<uint8_t>(Flags.I) << " " <<
        "D: " << std::hex << static_cast<uint8_t>(Flags.D) << " " <<
        "B: " << std::hex << static_cast<uint8_t>(Flags.B) << " " <<
        "_: " << std::hex << static_cast<uint8_t>(Flags._) << " " <<
        "V: " << std::hex << static_cast<uint8_t>(Flags.V) << " " <<
        "N: " << std::hex << static_cast<uint8_t>(Flags.N) << " " <<
        std::endl;
    return oss.str();
}
