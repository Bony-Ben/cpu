#include <iostream>

const int MAX_MEM = 256;

struct RAM {
    uint8_t data[MAX_MEM];
    void program() {
        for (int i = 0; i < MAX_MEM; i++) {
            data[i] = 0;
        }
        data[255] = 1;

        data[0] = 10;
        data[1] = 254;

        data[2] = 2;
        data[3] = 254;

        data[4] = 5;
        data[5] = 255;

        data[6] = 3;
        data[7] = 253;

        data[8] = 2;
        data[9] = 255;

        data[10] = 3;
        data[11] = 254;

        data[12] = 2;
        data[13] = 253;

        data[14] = 3;
        data[15] = 255;

        data[16] = 8;
        data[17] = 0;
    }
};

class InvalidInstruction {};

struct CPU {
    uint8_t PC;
    uint8_t A;
    RAM ram;

    void reset() {
        PC = 0;
        A = 0;
        ram.program();
    }

    void execute() {
        int instr = ram.data[PC];
        PC++;
        int x = ram.data[PC];
        PC++;
        switch (instr) {
            case 1:
                A = x;
                break;
            case 2:
                A = ram.data[x];
                break;
            case 3:
                ram.data[x] = A;
                break;
            case 4:
                A += x;
                break;
            case 5:
                A += ram.data[x];
                break;
            case 6:
                A -= x;
                break;
            case 7:
                A -= ram.data[x];
                break;
            case 8:
                PC = x;
                break;
            case 9:
                if (A == 0) {
                    PC = x;
                }
                break;
            case 10:
                std::cout << (int)ram.data[x] << std::endl;
                break;
            default:
                throw InvalidInstruction{};
        }
    }

    CPU() {
        reset();
    }
};

int main() {
    CPU cpu;
    try {
        while (true) {
            cpu.execute();
        }
    } catch (InvalidInstruction) {
        std::cout << "Done" << std::endl;
    }
}