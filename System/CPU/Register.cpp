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
