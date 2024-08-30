#include <cassert>

#include "./worst-fit.h"
int main(int argc, char const *argv[]) {
    assert(bin_packing_worst_fit({300, 400}) == 1);
    assert(bin_packing_worst_fit({300, 400, 300}) == 1);
    assert(bin_packing_worst_fit({300, 400, 300, 400}) == 2);
    assert(bin_packing_worst_fit({300, 400, 300, 400, 300}) == 2);
    assert(bin_packing_worst_fit({300, 400, 300, 400, 300, 400}) == 3);
    assert(bin_packing_worst_fit({501, 501, 501, 501, 249, 249, 249, 249, 250,
                                  250, 250, 250}) == 4);
    assert(bin_packing_worst_fit({501, 501, 501, 501, 249, 250, 249, 250, 249,
                                  250, 249, 250}) == 5);
    return 0;
}
