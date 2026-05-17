#ifndef HELPER
#define HELPER

#include <stddef.h>

/**
 * @brief Computes the next power of two >= v.
 *
 * @param v Input number.
 * @return size_t The next power of two >= v.
 */
static inline size_t next_power_of_two(size_t v) {
    if (v == 0) return 1;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
#if SIZE_MAX > 0xFFFFFFFF
    v |= v >> 32;
#endif
    v++;
    return v;
}

#endif // !HELPER
