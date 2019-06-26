#include "CPU.h"

u8 *CPU::get_address(u16 code, int mode, int place) {      
    u16 reg_num = code;         
    switch (mode) {
    case DRD:
        // reg_num = reg_num >> place;
        // reg_num = reg_num ^ 0b0000000000000111;
        // reg_num *= 4;
        return &(this->dreg[0]);

    default:
        exit(0);
        break;
    }
}