#include "MC68K.h"

u8 *MC68K::get_address(u16 code, int mode, int place) {      
    if(mode < 0) {
        mode = this->get_EAM(code, place);
    }
    
    u16 address;
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
        address = this->areg[reg_num];
        return &(this->RAM[address]);

    default:
        exit(0);
        break;
    }
}

void MC68K::perform_unary_op(std::function<u8(u8)> func, u8 *address, int size) {
    *address = func(*address);
    return;
}

int MC68K::get_EAM(u16 code, int place) {
    int mode = code;
    mode >>= (place + 3);
    mode &= 0b111;
    return mode;
}

u16 MC68K::get_PC() {
    return this->PC;
}