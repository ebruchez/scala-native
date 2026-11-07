#if defined(SCALANATIVE_FREESTANDING)

#include "../unwind.h"
#include <stddef.h>

__attribute__((weak)) int scalanative_unwind_get_context(void *context) {
    (void)context;
    return -1;
}

__attribute__((weak)) int scalanative_unwind_init_local(void *cursor,
                                                        void *context) {
    (void)cursor;
    (void)context;
    return -1;
}

__attribute__((weak)) int scalanative_unwind_step(void *cursor) {
    (void)cursor;
    return 0;
}

__attribute__((weak)) int scalanative_unwind_get_proc_name(void *cursor,
                                                           char *buffer,
                                                           size_t length,
                                                           void *offset) {
    (void)cursor;
    (void)buffer;
    (void)length;
    (void)offset;
    return -1;
}

__attribute__((weak)) int scalanative_unwind_get_proc_name_by_ip(
    size_t ip, char *buffer, size_t length, size_t *offset) {
    (void)ip;
    (void)buffer;
    (void)length;
    (void)offset;
    return -1;
}

__attribute__((weak)) int scalanative_unwind_get_reg(void *cursor, int regnum,
                                                     size_t *valp) {
    (void)cursor;
    (void)regnum;
    (void)valp;
    return -1;
}

__attribute__((weak)) int scalanative_unw_reg_ip(void) { return 0; }

__attribute__((weak)) size_t scalanative_unwind_sizeof_context(void) {
    return 0;
}

__attribute__((weak)) size_t scalanative_unwind_sizeof_cursor(void) {
    return 0;
}

#endif
