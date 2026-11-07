#if defined(SCALANATIVE_FREESTANDING) &&                                       \
    !defined(SCALANATIVE_MULTITHREADING_ENABLED)

#include <stdbool.h>
#include <stdint.h>

// Single-threaded weak fallbacks for compiler __atomic_* builtins on
// freestanding targets whose toolchain omits libatomic (e.g., 32-bit ARMv6-M
// and 64-bit atomics on 32-bit microcontrollers).

#define DEFINE_FREESTANDING_ATOMICS(N, TYPE)                                   \
    __attribute__((weak)) TYPE __atomic_load_##N(const volatile void *ptr,     \
                                                 int memorder) {               \
        (void)memorder;                                                        \
        return *(const volatile TYPE *)ptr;                                    \
    }                                                                          \
                                                                               \
    __attribute__((weak)) void __atomic_store_##N(volatile void *ptr,          \
                                                  TYPE val, int memorder) {    \
        (void)memorder;                                                        \
        *(volatile TYPE *)ptr = val;                                           \
    }                                                                          \
                                                                               \
    __attribute__((weak)) TYPE __atomic_exchange_##N(volatile void *ptr,       \
                                                     TYPE val, int memorder) { \
        (void)memorder;                                                        \
        volatile TYPE *p = (volatile TYPE *)ptr;                               \
        TYPE old = *p;                                                         \
        *p = val;                                                              \
        return old;                                                            \
    }                                                                          \
                                                                               \
    __attribute__((weak)) bool __atomic_compare_exchange_##N(                  \
        volatile void *ptr, void *expected, TYPE desired, bool weak,           \
        int success_memorder, int failure_memorder) {                          \
        (void)weak;                                                            \
        (void)success_memorder;                                                \
        (void)failure_memorder;                                                \
        volatile TYPE *p = (volatile TYPE *)ptr;                               \
        TYPE *exp = (TYPE *)expected;                                          \
        TYPE cur = *p;                                                         \
        if (cur == *exp) {                                                     \
            *p = desired;                                                      \
            return true;                                                       \
        } else {                                                               \
            *exp = cur;                                                        \
            return false;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    __attribute__((weak)) TYPE __atomic_fetch_add_##N(                         \
        volatile void *ptr, TYPE val, int memorder) {                          \
        (void)memorder;                                                        \
        volatile TYPE *p = (volatile TYPE *)ptr;                               \
        TYPE old = *p;                                                         \
        *p = old + val;                                                        \
        return old;                                                            \
    }                                                                          \
                                                                               \
    __attribute__((weak)) TYPE __atomic_fetch_sub_##N(                         \
        volatile void *ptr, TYPE val, int memorder) {                          \
        (void)memorder;                                                        \
        volatile TYPE *p = (volatile TYPE *)ptr;                               \
        TYPE old = *p;                                                         \
        *p = old - val;                                                        \
        return old;                                                            \
    }                                                                          \
                                                                               \
    __attribute__((weak)) TYPE __atomic_fetch_and_##N(                         \
        volatile void *ptr, TYPE val, int memorder) {                          \
        (void)memorder;                                                        \
        volatile TYPE *p = (volatile TYPE *)ptr;                               \
        TYPE old = *p;                                                         \
        *p = old & val;                                                        \
        return old;                                                            \
    }                                                                          \
                                                                               \
    __attribute__((weak)) TYPE __atomic_fetch_or_##N(                          \
        volatile void *ptr, TYPE val, int memorder) {                          \
        (void)memorder;                                                        \
        volatile TYPE *p = (volatile TYPE *)ptr;                               \
        TYPE old = *p;                                                         \
        *p = old | val;                                                        \
        return old;                                                            \
    }                                                                          \
                                                                               \
    __attribute__((weak)) TYPE __atomic_fetch_xor_##N(                         \
        volatile void *ptr, TYPE val, int memorder) {                          \
        (void)memorder;                                                        \
        volatile TYPE *p = (volatile TYPE *)ptr;                               \
        TYPE old = *p;                                                         \
        *p = old ^ val;                                                        \
        return old;                                                            \
    }

DEFINE_FREESTANDING_ATOMICS(1, uint8_t)
DEFINE_FREESTANDING_ATOMICS(2, uint16_t)
DEFINE_FREESTANDING_ATOMICS(4, uint32_t)
DEFINE_FREESTANDING_ATOMICS(8, uint64_t)

#endif // SCALANATIVE_FREESTANDING && !SCALANATIVE_MULTITHREADING_ENABLED
