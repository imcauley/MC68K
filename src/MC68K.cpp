#include "MC68K.h"

u8 *MC68K::get_address(u16 code, int mode, int place) {      
    u16 reg_num = code;         
    switch (mode) {
    case DRD:
        reg_num = reg_num >> place;
        reg_num = reg_num & 0b0000000000000111;
        reg_num *= 4;
        return &(this->dreg[reg_num]);

    case ARD:
        reg_num = reg_num >> place;
        reg_num = reg_num & 0b0000000000000111;
        reg_num *= 4;
        return &(this->areg[reg_num]);

    case RI:
        reg_num = reg_num >> place;
        reg_num = reg_num & 0b0000000000000111;
        reg_num *= 4;
        u16 address = this->areg[reg_num];
        return &(this->RAM[address]);

    default:
        exit(0);
        break;
    }
}

u16 MC68K::get_PC() {
    return this->PC;
}