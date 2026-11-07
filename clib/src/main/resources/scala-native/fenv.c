#if defined(SCALANATIVE_COMPILE_ALWAYS) || defined(__SCALANATIVE_C_FENV)
#include <fenv.h>

#ifdef FE_DIVBYZERO
int scalanative_fe_divbyzero() { return FE_DIVBYZERO; }
#else
int scalanative_fe_divbyzero() { return 0; }
#endif

#ifdef FE_INEXACT
int scalanative_fe_inexact() { return FE_INEXACT; }
#else
int scalanative_fe_inexact() { return 0; }
#endif

#ifdef FE_INVALID
int scalanative_fe_invalid() { return FE_INVALID; }
#else
int scalanative_fe_invalid() { return 0; }
#endif

#ifdef FE_OVERFLOW
int scalanative_fe_overflow() { return FE_OVERFLOW; }
#else
int scalanative_fe_overflow() { return 0; }
#endif

#ifdef FE_UNDERFLOW
int scalanative_fe_underflow() { return FE_UNDERFLOW; }
#else
int scalanative_fe_underflow() { return 0; }
#endif

#ifdef FE_ALL_EXCEPT
int scalanative_fe_all_except() { return FE_ALL_EXCEPT; }
#else
int scalanative_fe_all_except() { return 0; }
#endif

#ifdef FE_DOWNWARD
int scalanative_fe_downward() { return FE_DOWNWARD; }
#else
int scalanative_fe_downward() { return 0; }
#endif

#ifdef FE_TONEAREST
int scalanative_fe_tonearest() { return FE_TONEAREST; }
#else
int scalanative_fe_tonearest() { return 0; }
#endif

#ifdef FE_TOWARDZERO
int scalanative_fe_towardzero() { return FE_TOWARDZERO; }
#else
int scalanative_fe_towardzero() { return 0; }
#endif

#ifdef FE_UPWARD
int scalanative_fe_upward() { return FE_UPWARD; }
#else
int scalanative_fe_upward() { return 0; }
#endif
#endif