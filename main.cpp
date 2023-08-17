#include <iostream>
#include "System/CPU/CPU.h"

int main() {
    Memory memory;
    CPU cpu(&memory);

    memory.writeByte(0x09, 0x0000);
    memory.writeByte(0x11, 0x0001);
    cpu.cpuStep();
}
