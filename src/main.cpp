#include "MC68K.h"

int main() {
    u16 code = 0b1101000100010000;
    MC68K *proc = new MC68K();
    proc->dreg[0] = 12;

    u8 *add = proc->get_address(code, DRD, 0);
    std::cout << int(*add) << "\n";
}