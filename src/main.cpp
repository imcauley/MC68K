#include "MC68K.h"

int main() {
    u16 code = 0b1101000100010000;
    MC68K *proc = new MC68K();
    proc->dreg[0] = 255;
    proc->dreg[1] = 12;

    u8 *add = proc->get_address(code, DRD, 0);
    std::cout << proc->get_word(add) << "\n";

    proc->perform_unary_op([](u8 i) -> u8 {return 0;}, add, WORD);
    std::cout << proc->get_word(add) << "\n";
}