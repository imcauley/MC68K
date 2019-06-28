#ifndef MC68K_H
#define MC68K_H

#include <iostream>
#include "types.h"

class MC68K {
    private: 
    u16 PC;

    public:
    u8 RAM[256];
    u8 dreg[64];
    u8 areg[64];

    int get_EAM(u16 code, int place);
    u16 get_PC();
    u8 *get_address(u16 code, int mode, int place);
    void perform_unary_op(std::function<u8(u8)> func, u8 *address, int size);

    u16 get_word(u8 *address);
    u32 get_long(u8 *address);
};

#endif