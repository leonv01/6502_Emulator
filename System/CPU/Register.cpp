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
        "PC: 0x" << std::hex << static_cast<unsigned int>(PC) << " " <<
        "SP: 0x" << std::hex << static_cast<unsigned int>(SP)  << " " <<
        "A: 0x" << std::hex << static_cast<unsigned int>(A) << " " <<
        "X: 0x" << std::hex << static_cast<unsigned int>(X) << " " <<
        "Y: 0x" << std::hex << static_cast<unsigned int>(Y) << std::endl <<
        "Flags: " <<
        "C: " << std::hex << static_cast<unsigned int>(Flags.C) << " " <<
        "Z: " << std::hex << static_cast<unsigned int>(Flags.Z) << " " <<
        "I: " << std::hex << static_cast<unsigned int>(Flags.I) << " " <<
        "D: " << std::hex << static_cast<unsigned int>(Flags.D) << " " <<
        "B: " << std::hex << static_cast<unsigned int>(Flags.B) << " " <<
        "_: " << std::hex << static_cast<unsigned int>(Flags._) << " " <<
        "V: " << std::hex << static_cast<unsigned int>(Flags.V) << " " <<
        "N: " << std::hex << static_cast<unsigned int>(Flags.N) << " " <<
        std::endl;
    return oss.str();
}
