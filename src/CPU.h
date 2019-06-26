#ifndef MC68K
#define MC68K

#include <iostream>
#include "types.h"

class MC68K {
    public:
    u8 RAM[256];
    u8 dreg[64];
    u8 areg[64];
    u8 *get_address(u16 code, int mode, int place);

};

#endif