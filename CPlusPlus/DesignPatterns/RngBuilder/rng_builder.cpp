#include "rng_builder.h"

Rng_builder& Rng_builder::reset() {
    _a = _a_default;
    _b = _b_default;
    return *this;
}
