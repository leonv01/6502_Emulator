//
// Created by leonv on 17/08/2023.
//

#ifndef INC_6502_EMULATOR_CPU_H
#define INC_6502_EMULATOR_CPU_H


#include <memory>
#include "Register.h"

class CPU {
private:
    std::unique_ptr<Register> register;

public:
    CPU();
    ~CPU();
};


#endif //INC_6502_EMULATOR_CPU_H
