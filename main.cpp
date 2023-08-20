#include "System/CPU/CPU.h"

int main() {
    Memory memory;
    CPU cpu(&memory);

    // Load accumulator with zero
    memory.writeByte(0xA9, 0x0000);
    memory.writeByte(0xFF, 0x0001);

    memory.writeByte(0x30, 0x0002);
    memory.writeByte(0x02, 0x0003);

    cpu.cpuRun();
    cpu.printStatus();
}