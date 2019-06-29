#include "MC68K.h"
#include <cmath>

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
    for(int i = 0; i < size+1; i++) {
        *(address + i) = func(*(address + i));
    }
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

u16 MC68K::get_word(u8 *address) {
    return(*address + (*(address + 1) * 256));
}


//where start is the rightmost position of the binary number
int MC68K::mask_bits(u32 num, int start, int num_bits) {
    num >>= start;
    u32 mask = (std::pow(2, num_bits)) - 1;
    num &= mask;
    return num;
}

void MC68K::decode(u16 code) {

    // CLR
    if((code & 0b1111111100000000) == 0b0100001000000000) {
        int size = this->mask_bits(u32(code), 6, 2);
        u8* address = this->get_address(code, -1, 0);
        this->perform_unary_op([](u8 i) -> u8 {return 0;}, address, size);
    }
}