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

};

#endif