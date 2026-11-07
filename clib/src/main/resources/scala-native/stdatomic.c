// clang-format off
#if defined(SCALANATIVE_COMPILE_ALWAYS) || defined(__SCALANATIVE_C_STDATOMIC)
#include <stdbool.h>
#include <stdint.h>
#include <stdatomic.h>

memory_order scalanative_atomic_memory_order_relaxed() { return memory_order_relaxed;}
memory_order scalanative_atomic_memory_order_consume() { return memory_order_consume;}
memory_order scalanative_atomic_memory_order_acquire() { return memory_order_acquire;}
memory_order scalanative_atomic_memory_order_release() { return memory_order_release;}
memory_order scalanative_atomic_memory_order_acq_rel() { return memory_order_acq_rel;}
memory_order scalanative_atomic_memory_order_seq_cst() { return memory_order_seq_cst;}

void scalanative_atomic_thread_fence(memory_order order) { atomic_thread_fence(order);}
void scalanative_atomic_signal_fence(memory_order order) { atomic_signal_fence(order);}

#if defined(SCALANATIVE_FREESTANDING) && !defined(SCALANATIVE_MULTITHREADING_ENABLED)
#define SN_ATOMIC(T) T
#define SN_ATOMIC_INIT(atm, val) (*(atm) = (val))
#define SN_ATOMIC_LOAD(atm) (*(atm))
#define SN_ATOMIC_LOAD_EXPLICIT(atm, order) ((void)(order), *(atm))
#define SN_ATOMIC_STORE(atm, val) (*(atm) = (val))
#define SN_ATOMIC_STORE_EXPLICIT(atm, val, order) ((void)(order), *(atm) = (val))
#define SN_ATOMIC_EXCHANGE(T, atm, val) ({ T _old = *(atm); *(atm) = (val); _old; })
#define SN_ATOMIC_EXCHANGE_EXPLICIT(T, atm, val, order) ((void)(order), SN_ATOMIC_EXCHANGE(T, atm, val))
#define SN_ATOMIC_CAS(atm, exp, des) (*(atm) == *(exp) ? (*(atm) = (des), true) : (*(exp) = *(atm), false))
#define SN_ATOMIC_CAS_EXPLICIT(atm, exp, des, s, f) ((void)(s), (void)(f), SN_ATOMIC_CAS(atm, exp, des))
#define SN_ATOMIC_FETCH_add(T, atm, val) ({ T _old = *(atm); *(atm) = _old + (val); _old; })
#define SN_ATOMIC_FETCH_sub(T, atm, val) ({ T _old = *(atm); *(atm) = _old - (val); _old; })
#define SN_ATOMIC_FETCH_and(T, atm, val) ({ T _old = *(atm); *(atm) = _old & (val); _old; })
#define SN_ATOMIC_FETCH_or(T, atm, val) ({ T _old = *(atm); *(atm) = _old | (val); _old; })
#define SN_ATOMIC_FETCH_xor(T, atm, val) ({ T _old = *(atm); *(atm) = _old ^ (val); _old; })
#define SN_ATOMIC_FETCH_EXPLICIT(op, T, atm, val, order) ((void)(order), SN_ATOMIC_FETCH_##op(T, atm, val))
#else
#define SN_ATOMIC(T) _Atomic(T)
#define SN_ATOMIC_INIT(atm, val) atomic_init(atm, val)
#define SN_ATOMIC_LOAD(atm) atomic_load(atm)
#define SN_ATOMIC_LOAD_EXPLICIT(atm, order) atomic_load_explicit(atm, order)
#define SN_ATOMIC_STORE(atm, val) atomic_store(atm, val)
#define SN_ATOMIC_STORE_EXPLICIT(atm, val, order) atomic_store_explicit(atm, val, order)
#define SN_ATOMIC_EXCHANGE(T, atm, val) atomic_exchange(atm, val)
#define SN_ATOMIC_EXCHANGE_EXPLICIT(T, atm, val, order) atomic_exchange_explicit(atm, val, order)
#define SN_ATOMIC_CAS(atm, exp, des) atomic_compare_exchange_strong(atm, exp, des)
#define SN_ATOMIC_CAS_EXPLICIT(atm, exp, des, s, f) atomic_compare_exchange_strong_explicit(atm, exp, des, s, f)
#define SN_ATOMIC_FETCH_add(T, atm, val) atomic_fetch_add(atm, val)
#define SN_ATOMIC_FETCH_sub(T, atm, val) atomic_fetch_sub(atm, val)
#define SN_ATOMIC_FETCH_and(T, atm, val) atomic_fetch_and(atm, val)
#define SN_ATOMIC_FETCH_or(T, atm, val) atomic_fetch_or(atm, val)
#define SN_ATOMIC_FETCH_xor(T, atm, val) atomic_fetch_xor(atm, val)
#define SN_ATOMIC_FETCH_EXPLICIT(op, T, atm, val, order) atomic_fetch_##op##_explicit(atm, val, order)
#endif

void scalanative_atomic_init_bool(SN_ATOMIC(bool)* atm, bool init_value) { SN_ATOMIC_INIT(atm, init_value);}
bool scalanative_atomic_load_bool(SN_ATOMIC(bool)* atm) { return SN_ATOMIC_LOAD(atm);}
bool scalanative_atomic_load_explicit_bool(SN_ATOMIC(bool)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_bool(SN_ATOMIC(bool)* atm, bool val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_bool(SN_ATOMIC(bool)* atm, bool val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
bool scalanative_atomic_exchange_bool(SN_ATOMIC(bool)* atm, bool val) { return SN_ATOMIC_EXCHANGE(bool, atm, val);}
bool scalanative_atomic_exchange_explicit_bool(SN_ATOMIC(bool)* atm, bool val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(bool, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_bool(SN_ATOMIC(bool)* atm, bool* expected, bool desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_bool(SN_ATOMIC(bool)* atm, bool* expected, bool desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_bool(SN_ATOMIC(bool)* atm, bool* expected, bool desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_bool(SN_ATOMIC(bool)* atm, bool* expected, bool desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_fetch_add_bool(SN_ATOMIC(bool)* atm, bool val) { return SN_ATOMIC_FETCH_add(bool, atm, val);}
bool scalanative_atomic_fetch_add_explicit_bool(SN_ATOMIC(bool)* atm, bool val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, bool, atm, val, memoryOrder);}
bool scalanative_atomic_fetch_sub_bool(SN_ATOMIC(bool)* atm, bool val) { return SN_ATOMIC_FETCH_sub(bool, atm, val);}
bool scalanative_atomic_fetch_sub_explicit_bool(SN_ATOMIC(bool)* atm, bool val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, bool, atm, val, memoryOrder);}
bool scalanative_atomic_fetch_and_bool(SN_ATOMIC(bool)* atm, bool val) { return SN_ATOMIC_FETCH_and(bool, atm, val);}
bool scalanative_atomic_fetch_and_explicit_bool(SN_ATOMIC(bool)* atm, bool val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, bool, atm, val, memoryOrder);}
bool scalanative_atomic_fetch_or_bool(SN_ATOMIC(bool)* atm, bool val) { return SN_ATOMIC_FETCH_or(bool, atm, val);}
bool scalanative_atomic_fetch_or_explicit_bool(SN_ATOMIC(bool)* atm, bool val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, bool, atm, val, memoryOrder);}
bool scalanative_atomic_fetch_xor_bool(SN_ATOMIC(bool)* atm, bool val) { return SN_ATOMIC_FETCH_xor(bool, atm, val);}
bool scalanative_atomic_fetch_xor_explicit_bool(SN_ATOMIC(bool)* atm, bool val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, bool, atm, val, memoryOrder);}

void scalanative_atomic_init_byte(SN_ATOMIC(char)* atm, char init_value) { SN_ATOMIC_INIT(atm, init_value);}
char scalanative_atomic_load_byte(SN_ATOMIC(char)* atm) { return SN_ATOMIC_LOAD(atm);}
char scalanative_atomic_load_explicit_byte(SN_ATOMIC(char)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_byte(SN_ATOMIC(char)* atm, char val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_byte(SN_ATOMIC(char)* atm, char val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
char scalanative_atomic_exchange_byte(SN_ATOMIC(char)* atm, char val) { return SN_ATOMIC_EXCHANGE(char, atm, val);}
char scalanative_atomic_exchange_explicit_byte(SN_ATOMIC(char)* atm, char val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(char, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_byte(SN_ATOMIC(char)* atm, char* expected, char desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_byte(SN_ATOMIC(char)* atm, char* expected, char desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_byte(SN_ATOMIC(char)* atm, char* expected, char desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_byte(SN_ATOMIC(char)* atm, char* expected, char desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
char scalanative_atomic_fetch_add_byte(SN_ATOMIC(char)* atm, char val) { return SN_ATOMIC_FETCH_add(char, atm, val);}
char scalanative_atomic_fetch_add_explicit_byte(SN_ATOMIC(char)* atm, char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, char, atm, val, memoryOrder);}
char scalanative_atomic_fetch_sub_byte(SN_ATOMIC(char)* atm, char val) { return SN_ATOMIC_FETCH_sub(char, atm, val);}
char scalanative_atomic_fetch_sub_explicit_byte(SN_ATOMIC(char)* atm, char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, char, atm, val, memoryOrder);}
char scalanative_atomic_fetch_and_byte(SN_ATOMIC(char)* atm, char val) { return SN_ATOMIC_FETCH_and(char, atm, val);}
char scalanative_atomic_fetch_and_explicit_byte(SN_ATOMIC(char)* atm, char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, char, atm, val, memoryOrder);}
char scalanative_atomic_fetch_or_byte(SN_ATOMIC(char)* atm, char val) { return SN_ATOMIC_FETCH_or(char, atm, val);}
char scalanative_atomic_fetch_or_explicit_byte(SN_ATOMIC(char)* atm, char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, char, atm, val, memoryOrder);}
char scalanative_atomic_fetch_xor_byte(SN_ATOMIC(char)* atm, char val) { return SN_ATOMIC_FETCH_xor(char, atm, val);}
char scalanative_atomic_fetch_xor_explicit_byte(SN_ATOMIC(char)* atm, char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, char, atm, val, memoryOrder);}

void scalanative_atomic_init_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char init_value) { SN_ATOMIC_INIT(atm, init_value);}
unsigned char scalanative_atomic_load_ubyte(SN_ATOMIC(unsigned char)* atm) { return SN_ATOMIC_LOAD(atm);}
unsigned char scalanative_atomic_load_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
unsigned char scalanative_atomic_exchange_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val) { return SN_ATOMIC_EXCHANGE(unsigned char, atm, val);}
unsigned char scalanative_atomic_exchange_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(unsigned char, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char* expected, unsigned char desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char* expected, unsigned char desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char* expected, unsigned char desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char* expected, unsigned char desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
unsigned char scalanative_atomic_fetch_add_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val) { return SN_ATOMIC_FETCH_add(unsigned char, atm, val);}
unsigned char scalanative_atomic_fetch_add_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, unsigned char, atm, val, memoryOrder);}
unsigned char scalanative_atomic_fetch_sub_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val) { return SN_ATOMIC_FETCH_sub(unsigned char, atm, val);}
unsigned char scalanative_atomic_fetch_sub_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, unsigned char, atm, val, memoryOrder);}
unsigned char scalanative_atomic_fetch_and_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val) { return SN_ATOMIC_FETCH_and(unsigned char, atm, val);}
unsigned char scalanative_atomic_fetch_and_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, unsigned char, atm, val, memoryOrder);}
unsigned char scalanative_atomic_fetch_or_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val) { return SN_ATOMIC_FETCH_or(unsigned char, atm, val);}
unsigned char scalanative_atomic_fetch_or_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, unsigned char, atm, val, memoryOrder);}
unsigned char scalanative_atomic_fetch_xor_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val) { return SN_ATOMIC_FETCH_xor(unsigned char, atm, val);}
unsigned char scalanative_atomic_fetch_xor_explicit_ubyte(SN_ATOMIC(unsigned char)* atm, unsigned char val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, unsigned char, atm, val, memoryOrder);}

void scalanative_atomic_init_short(SN_ATOMIC(short)* atm, short init_value) { SN_ATOMIC_INIT(atm, init_value);}
short scalanative_atomic_load_short(SN_ATOMIC(short)* atm) { return SN_ATOMIC_LOAD(atm);}
short scalanative_atomic_load_explicit_short(SN_ATOMIC(short)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_short(SN_ATOMIC(short)* atm, short val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_short(SN_ATOMIC(short)* atm, short val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
short scalanative_atomic_exchange_short(SN_ATOMIC(short)* atm, short val) { return SN_ATOMIC_EXCHANGE(short, atm, val);}
short scalanative_atomic_exchange_explicit_short(SN_ATOMIC(short)* atm, short val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(short, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_short(SN_ATOMIC(short)* atm, short* expected, short desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_short(SN_ATOMIC(short)* atm, short* expected, short desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_short(SN_ATOMIC(short)* atm, short* expected, short desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_short(SN_ATOMIC(short)* atm, short* expected, short desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
short scalanative_atomic_fetch_add_short(SN_ATOMIC(short)* atm, short val) { return SN_ATOMIC_FETCH_add(short, atm, val);}
short scalanative_atomic_fetch_add_explicit_short(SN_ATOMIC(short)* atm, short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, short, atm, val, memoryOrder);}
short scalanative_atomic_fetch_sub_short(SN_ATOMIC(short)* atm, short val) { return SN_ATOMIC_FETCH_sub(short, atm, val);}
short scalanative_atomic_fetch_sub_explicit_short(SN_ATOMIC(short)* atm, short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, short, atm, val, memoryOrder);}
short scalanative_atomic_fetch_and_short(SN_ATOMIC(short)* atm, short val) { return SN_ATOMIC_FETCH_and(short, atm, val);}
short scalanative_atomic_fetch_and_explicit_short(SN_ATOMIC(short)* atm, short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, short, atm, val, memoryOrder);}
short scalanative_atomic_fetch_or_short(SN_ATOMIC(short)* atm, short val) { return SN_ATOMIC_FETCH_or(short, atm, val);}
short scalanative_atomic_fetch_or_explicit_short(SN_ATOMIC(short)* atm, short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, short, atm, val, memoryOrder);}
short scalanative_atomic_fetch_xor_short(SN_ATOMIC(short)* atm, short val) { return SN_ATOMIC_FETCH_xor(short, atm, val);}
short scalanative_atomic_fetch_xor_explicit_short(SN_ATOMIC(short)* atm, short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, short, atm, val, memoryOrder);}

void scalanative_atomic_init_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short init_value) { SN_ATOMIC_INIT(atm, init_value);}
unsigned short scalanative_atomic_load_ushort(SN_ATOMIC(unsigned short)* atm) { return SN_ATOMIC_LOAD(atm);}
unsigned short scalanative_atomic_load_explicit_ushort(SN_ATOMIC(unsigned short)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
unsigned short scalanative_atomic_exchange_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val) { return SN_ATOMIC_EXCHANGE(unsigned short, atm, val);}
unsigned short scalanative_atomic_exchange_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(unsigned short, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short* expected, unsigned short desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short* expected, unsigned short desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short* expected, unsigned short desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short* expected, unsigned short desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
unsigned short scalanative_atomic_fetch_add_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val) { return SN_ATOMIC_FETCH_add(unsigned short, atm, val);}
unsigned short scalanative_atomic_fetch_add_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, unsigned short, atm, val, memoryOrder);}
unsigned short scalanative_atomic_fetch_sub_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val) { return SN_ATOMIC_FETCH_sub(unsigned short, atm, val);}
unsigned short scalanative_atomic_fetch_sub_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, unsigned short, atm, val, memoryOrder);}
unsigned short scalanative_atomic_fetch_and_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val) { return SN_ATOMIC_FETCH_and(unsigned short, atm, val);}
unsigned short scalanative_atomic_fetch_and_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, unsigned short, atm, val, memoryOrder);}
unsigned short scalanative_atomic_fetch_or_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val) { return SN_ATOMIC_FETCH_or(unsigned short, atm, val);}
unsigned short scalanative_atomic_fetch_or_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, unsigned short, atm, val, memoryOrder);}
unsigned short scalanative_atomic_fetch_xor_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val) { return SN_ATOMIC_FETCH_xor(unsigned short, atm, val);}
unsigned short scalanative_atomic_fetch_xor_explicit_ushort(SN_ATOMIC(unsigned short)* atm, unsigned short val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, unsigned short, atm, val, memoryOrder);}

void scalanative_atomic_init_int(SN_ATOMIC(int)* atm, int init_value) { SN_ATOMIC_INIT(atm, init_value);}
int scalanative_atomic_load_int(SN_ATOMIC(int)* atm) { return SN_ATOMIC_LOAD(atm);}
int scalanative_atomic_load_explicit_int(SN_ATOMIC(int)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_int(SN_ATOMIC(int)* atm, int val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_int(SN_ATOMIC(int)* atm, int val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
int scalanative_atomic_exchange_int(SN_ATOMIC(int)* atm, int val) { return SN_ATOMIC_EXCHANGE(int, atm, val);}
int scalanative_atomic_exchange_explicit_int(SN_ATOMIC(int)* atm, int val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(int, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_int(SN_ATOMIC(int)* atm, int* expected, int desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_int(SN_ATOMIC(int)* atm, int* expected, int desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_int(SN_ATOMIC(int)* atm, int* expected, int desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_int(SN_ATOMIC(int)* atm, int* expected, int desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
int scalanative_atomic_fetch_add_int(SN_ATOMIC(int)* atm, int val) { return SN_ATOMIC_FETCH_add(int, atm, val);}
int scalanative_atomic_fetch_add_explicit_int(SN_ATOMIC(int)* atm, int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, int, atm, val, memoryOrder);}
int scalanative_atomic_fetch_sub_int(SN_ATOMIC(int)* atm, int val) { return SN_ATOMIC_FETCH_sub(int, atm, val);}
int scalanative_atomic_fetch_sub_explicit_int(SN_ATOMIC(int)* atm, int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, int, atm, val, memoryOrder);}
int scalanative_atomic_fetch_and_int(SN_ATOMIC(int)* atm, int val) { return SN_ATOMIC_FETCH_and(int, atm, val);}
int scalanative_atomic_fetch_and_explicit_int(SN_ATOMIC(int)* atm, int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, int, atm, val, memoryOrder);}
int scalanative_atomic_fetch_or_int(SN_ATOMIC(int)* atm, int val) { return SN_ATOMIC_FETCH_or(int, atm, val);}
int scalanative_atomic_fetch_or_explicit_int(SN_ATOMIC(int)* atm, int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, int, atm, val, memoryOrder);}
int scalanative_atomic_fetch_xor_int(SN_ATOMIC(int)* atm, int val) { return SN_ATOMIC_FETCH_xor(int, atm, val);}
int scalanative_atomic_fetch_xor_explicit_int(SN_ATOMIC(int)* atm, int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, int, atm, val, memoryOrder);}

void scalanative_atomic_init_uint(SN_ATOMIC(unsigned int)* atm, unsigned int init_value) { SN_ATOMIC_INIT(atm, init_value);}
unsigned int scalanative_atomic_load_uint(SN_ATOMIC(unsigned int)* atm) { return SN_ATOMIC_LOAD(atm);}
unsigned int scalanative_atomic_load_explicit_uint(SN_ATOMIC(unsigned int)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
unsigned int scalanative_atomic_exchange_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val) { return SN_ATOMIC_EXCHANGE(unsigned int, atm, val);}
unsigned int scalanative_atomic_exchange_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(unsigned int, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_uint(SN_ATOMIC(unsigned int)* atm, unsigned int* expected, unsigned int desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int* expected, unsigned int desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_uint(SN_ATOMIC(unsigned int)* atm, unsigned int* expected, unsigned int desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int* expected, unsigned int desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
unsigned int scalanative_atomic_fetch_add_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val) { return SN_ATOMIC_FETCH_add(unsigned int, atm, val);}
unsigned int scalanative_atomic_fetch_add_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, unsigned int, atm, val, memoryOrder);}
unsigned int scalanative_atomic_fetch_sub_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val) { return SN_ATOMIC_FETCH_sub(unsigned int, atm, val);}
unsigned int scalanative_atomic_fetch_sub_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, unsigned int, atm, val, memoryOrder);}
unsigned int scalanative_atomic_fetch_and_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val) { return SN_ATOMIC_FETCH_and(unsigned int, atm, val);}
unsigned int scalanative_atomic_fetch_and_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, unsigned int, atm, val, memoryOrder);}
unsigned int scalanative_atomic_fetch_or_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val) { return SN_ATOMIC_FETCH_or(unsigned int, atm, val);}
unsigned int scalanative_atomic_fetch_or_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, unsigned int, atm, val, memoryOrder);}
unsigned int scalanative_atomic_fetch_xor_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val) { return SN_ATOMIC_FETCH_xor(unsigned int, atm, val);}
unsigned int scalanative_atomic_fetch_xor_explicit_uint(SN_ATOMIC(unsigned int)* atm, unsigned int val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, unsigned int, atm, val, memoryOrder);}

void scalanative_atomic_init_long(SN_ATOMIC(long)* atm, long init_value) { SN_ATOMIC_INIT(atm, init_value);}
long scalanative_atomic_load_long(SN_ATOMIC(long)* atm) { return SN_ATOMIC_LOAD(atm);}
long scalanative_atomic_load_explicit_long(SN_ATOMIC(long)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_long(SN_ATOMIC(long)* atm, long val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_long(SN_ATOMIC(long)* atm, long val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
long scalanative_atomic_exchange_long(SN_ATOMIC(long)* atm, long val) { return SN_ATOMIC_EXCHANGE(long, atm, val);}
long scalanative_atomic_exchange_explicit_long(SN_ATOMIC(long)* atm, long val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(long, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_long(SN_ATOMIC(long)* atm, long* expected, long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_long(SN_ATOMIC(long)* atm, long* expected, long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_long(SN_ATOMIC(long)* atm, long* expected, long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_long(SN_ATOMIC(long)* atm, long* expected, long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
long scalanative_atomic_fetch_add_long(SN_ATOMIC(long)* atm, long val) { return SN_ATOMIC_FETCH_add(long, atm, val);}
long scalanative_atomic_fetch_add_explicit_long(SN_ATOMIC(long)* atm, long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, long, atm, val, memoryOrder);}
long scalanative_atomic_fetch_sub_long(SN_ATOMIC(long)* atm, long val) { return SN_ATOMIC_FETCH_sub(long, atm, val);}
long scalanative_atomic_fetch_sub_explicit_long(SN_ATOMIC(long)* atm, long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, long, atm, val, memoryOrder);}
long scalanative_atomic_fetch_and_long(SN_ATOMIC(long)* atm, long val) { return SN_ATOMIC_FETCH_and(long, atm, val);}
long scalanative_atomic_fetch_and_explicit_long(SN_ATOMIC(long)* atm, long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, long, atm, val, memoryOrder);}
long scalanative_atomic_fetch_or_long(SN_ATOMIC(long)* atm, long val) { return SN_ATOMIC_FETCH_or(long, atm, val);}
long scalanative_atomic_fetch_or_explicit_long(SN_ATOMIC(long)* atm, long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, long, atm, val, memoryOrder);}
long scalanative_atomic_fetch_xor_long(SN_ATOMIC(long)* atm, long val) { return SN_ATOMIC_FETCH_xor(long, atm, val);}
long scalanative_atomic_fetch_xor_explicit_long(SN_ATOMIC(long)* atm, long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, long, atm, val, memoryOrder);}

void scalanative_atomic_init_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long init_value) { SN_ATOMIC_INIT(atm, init_value);}
unsigned long scalanative_atomic_load_ulong(SN_ATOMIC(unsigned long)* atm) { return SN_ATOMIC_LOAD(atm);}
unsigned long scalanative_atomic_load_explicit_ulong(SN_ATOMIC(unsigned long)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
unsigned long scalanative_atomic_exchange_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val) { return SN_ATOMIC_EXCHANGE(unsigned long, atm, val);}
unsigned long scalanative_atomic_exchange_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(unsigned long, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long* expected, unsigned long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long* expected, unsigned long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long* expected, unsigned long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long* expected, unsigned long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
unsigned long scalanative_atomic_fetch_add_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val) { return SN_ATOMIC_FETCH_add(unsigned long, atm, val);}
unsigned long scalanative_atomic_fetch_add_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, unsigned long, atm, val, memoryOrder);}
unsigned long scalanative_atomic_fetch_sub_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val) { return SN_ATOMIC_FETCH_sub(unsigned long, atm, val);}
unsigned long scalanative_atomic_fetch_sub_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, unsigned long, atm, val, memoryOrder);}
unsigned long scalanative_atomic_fetch_and_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val) { return SN_ATOMIC_FETCH_and(unsigned long, atm, val);}
unsigned long scalanative_atomic_fetch_and_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, unsigned long, atm, val, memoryOrder);}
unsigned long scalanative_atomic_fetch_or_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val) { return SN_ATOMIC_FETCH_or(unsigned long, atm, val);}
unsigned long scalanative_atomic_fetch_or_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, unsigned long, atm, val, memoryOrder);}
unsigned long scalanative_atomic_fetch_xor_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val) { return SN_ATOMIC_FETCH_xor(unsigned long, atm, val);}
unsigned long scalanative_atomic_fetch_xor_explicit_ulong(SN_ATOMIC(unsigned long)* atm, unsigned long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, unsigned long, atm, val, memoryOrder);}

void scalanative_atomic_init_llong(SN_ATOMIC(long long)* atm, long long init_value) { SN_ATOMIC_INIT(atm, init_value);}
long long scalanative_atomic_load_llong(SN_ATOMIC(long long)* atm) { return SN_ATOMIC_LOAD(atm);}
long long scalanative_atomic_load_explicit_llong(SN_ATOMIC(long long)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_llong(SN_ATOMIC(long long)* atm, long long val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_llong(SN_ATOMIC(long long)* atm, long long val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
long long scalanative_atomic_exchange_llong(SN_ATOMIC(long long)* atm, long long val) { return SN_ATOMIC_EXCHANGE(long long, atm, val);}
long long scalanative_atomic_exchange_explicit_llong(SN_ATOMIC(long long)* atm, long long val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(long long, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_llong(SN_ATOMIC(long long)* atm, long long* expected, long long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_llong(SN_ATOMIC(long long)* atm, long long* expected, long long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_llong(SN_ATOMIC(long long)* atm, long long* expected, long long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_llong(SN_ATOMIC(long long)* atm, long long* expected, long long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
long long scalanative_atomic_fetch_add_llong(SN_ATOMIC(long long)* atm, long long val) { return SN_ATOMIC_FETCH_add(long long, atm, val);}
long long scalanative_atomic_fetch_add_explicit_llong(SN_ATOMIC(long long)* atm, long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, long long, atm, val, memoryOrder);}
long long scalanative_atomic_fetch_sub_llong(SN_ATOMIC(long long)* atm, long long val) { return SN_ATOMIC_FETCH_sub(long long, atm, val);}
long long scalanative_atomic_fetch_sub_explicit_llong(SN_ATOMIC(long long)* atm, long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, long long, atm, val, memoryOrder);}
long long scalanative_atomic_fetch_and_llong(SN_ATOMIC(long long)* atm, long long val) { return SN_ATOMIC_FETCH_and(long long, atm, val);}
long long scalanative_atomic_fetch_and_explicit_llong(SN_ATOMIC(long long)* atm, long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, long long, atm, val, memoryOrder);}
long long scalanative_atomic_fetch_or_llong(SN_ATOMIC(long long)* atm, long long val) { return SN_ATOMIC_FETCH_or(long long, atm, val);}
long long scalanative_atomic_fetch_or_explicit_llong(SN_ATOMIC(long long)* atm, long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, long long, atm, val, memoryOrder);}
long long scalanative_atomic_fetch_xor_llong(SN_ATOMIC(long long)* atm, long long val) { return SN_ATOMIC_FETCH_xor(long long, atm, val);}
long long scalanative_atomic_fetch_xor_explicit_llong(SN_ATOMIC(long long)* atm, long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, long long, atm, val, memoryOrder);}

void scalanative_atomic_init_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long init_value) { SN_ATOMIC_INIT(atm, init_value);}
unsigned long long scalanative_atomic_load_ullong(SN_ATOMIC(unsigned long long)* atm) { return SN_ATOMIC_LOAD(atm);}
unsigned long long scalanative_atomic_load_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
unsigned long long scalanative_atomic_exchange_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val) { return SN_ATOMIC_EXCHANGE(unsigned long long, atm, val);}
unsigned long long scalanative_atomic_exchange_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(unsigned long long, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long* expected, unsigned long long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long* expected, unsigned long long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long* expected, unsigned long long desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long* expected, unsigned long long desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
unsigned long long scalanative_atomic_fetch_add_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val) { return SN_ATOMIC_FETCH_add(unsigned long long, atm, val);}
unsigned long long scalanative_atomic_fetch_add_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, unsigned long long, atm, val, memoryOrder);}
unsigned long long scalanative_atomic_fetch_sub_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val) { return SN_ATOMIC_FETCH_sub(unsigned long long, atm, val);}
unsigned long long scalanative_atomic_fetch_sub_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, unsigned long long, atm, val, memoryOrder);}
unsigned long long scalanative_atomic_fetch_and_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val) { return SN_ATOMIC_FETCH_and(unsigned long long, atm, val);}
unsigned long long scalanative_atomic_fetch_and_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, unsigned long long, atm, val, memoryOrder);}
unsigned long long scalanative_atomic_fetch_or_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val) { return SN_ATOMIC_FETCH_or(unsigned long long, atm, val);}
unsigned long long scalanative_atomic_fetch_or_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, unsigned long long, atm, val, memoryOrder);}
unsigned long long scalanative_atomic_fetch_xor_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val) { return SN_ATOMIC_FETCH_xor(unsigned long long, atm, val);}
unsigned long long scalanative_atomic_fetch_xor_explicit_ullong(SN_ATOMIC(unsigned long long)* atm, unsigned long long val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, unsigned long long, atm, val, memoryOrder);}

void scalanative_atomic_init_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t init_value) { SN_ATOMIC_INIT(atm, init_value);}
intptr_t scalanative_atomic_load_intptr(SN_ATOMIC(intptr_t)* atm) { return SN_ATOMIC_LOAD(atm);}
intptr_t scalanative_atomic_load_explicit_intptr(SN_ATOMIC(intptr_t)* atm, memory_order memoryOrder) { return SN_ATOMIC_LOAD_EXPLICIT(atm, memoryOrder);}
void scalanative_atomic_store_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val) {SN_ATOMIC_STORE(atm, val);}
void scalanative_atomic_store_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val, memory_order memoryOrder) { SN_ATOMIC_STORE_EXPLICIT(atm, val, memoryOrder);}
intptr_t scalanative_atomic_exchange_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val) { return SN_ATOMIC_EXCHANGE(intptr_t, atm, val);}
intptr_t scalanative_atomic_exchange_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val, memory_order memoryOrder) { return SN_ATOMIC_EXCHANGE_EXPLICIT(intptr_t, atm, val, memoryOrder);}
bool scalanative_atomic_compare_exchange_strong_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t* expected, intptr_t desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_strong_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t* expected, intptr_t desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
bool scalanative_atomic_compare_exchange_weak_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t* expected, intptr_t desired) { return SN_ATOMIC_CAS(atm, expected, desired);}
bool scalanative_atomic_compare_exchange_weak_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t* expected, intptr_t desired, memory_order onSucc, memory_order onFail) { return SN_ATOMIC_CAS_EXPLICIT(atm, expected, desired, onSucc, onFail);}
intptr_t scalanative_atomic_fetch_add_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val) { return SN_ATOMIC_FETCH_add(intptr_t, atm, val);}
intptr_t scalanative_atomic_fetch_add_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(add, intptr_t, atm, val, memoryOrder);}
intptr_t scalanative_atomic_fetch_sub_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val) { return SN_ATOMIC_FETCH_sub(intptr_t, atm, val);}
intptr_t scalanative_atomic_fetch_sub_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(sub, intptr_t, atm, val, memoryOrder);}
intptr_t scalanative_atomic_fetch_and_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val) { return SN_ATOMIC_FETCH_and(intptr_t, atm, val);}
intptr_t scalanative_atomic_fetch_and_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(and, intptr_t, atm, val, memoryOrder);}
intptr_t scalanative_atomic_fetch_or_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val) { return SN_ATOMIC_FETCH_or(intptr_t, atm, val);}
intptr_t scalanative_atomic_fetch_or_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(or, intptr_t, atm, val, memoryOrder);}
intptr_t scalanative_atomic_fetch_xor_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val) { return SN_ATOMIC_FETCH_xor(intptr_t, atm, val);}
intptr_t scalanative_atomic_fetch_xor_explicit_intptr(SN_ATOMIC(intptr_t)* atm, intptr_t val, memory_order memoryOrder) { return SN_ATOMIC_FETCH_EXPLICIT(xor, intptr_t, atm, val, memoryOrder);}
#endif // defined(SCALANATIVE_COMPILE_ALWAYS) || defined(__SCALANATIVE_C_STDATOMIC)
