#include <iostream>
#include "System/CPU/CPU.h"

int main() {
    Memory memory;
    CPU cpu(&memory);

    memory.writeByte(0xFF, 0x00FF);

    memory.writeByte(0xA5, 0x0000);
    memory.writeByte(0xFF, 0x0001);
    cpu.cpuStep();
    cpu.printStatus();
}
