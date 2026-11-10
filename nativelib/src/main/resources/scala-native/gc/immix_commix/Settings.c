#if defined(SCALANATIVE_GC_IMMIX) || defined(SCALANATIVE_GC_COMMIX)

#ifdef _WIN32
// sscanf and getEnv is deprecated in WinCRT, disable warnings
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include "immix_commix/Settings.h"
#include "immix_commix/CollectorState.h"
#include "shared/Parsing.h"
#include "shared/Settings.h"
#include "shared/MemoryInfo.h"
#include "immix_commix/Constants.h"
#include "shared/Log.h"

// =============================================================================
// Heap Settings
// =============================================================================
size_t Settings_MinHeapSize(void) {
#ifdef SCALANATIVE_FREESTANDING
    return Parse_Env_Or_Default("GC_INITIAL_HEAP_SIZE",
                                __scalanative_initial_memory_size());
#else
    return Parse_Env_Or_Default("GC_INITIAL_HEAP_SIZE", DEFAULT_MIN_HEAP_SIZE);
#endif
}

size_t Settings_MaxHeapSize(void) {
    return Parse_Env_Or_Default("GC_MAXIMUM_HEAP_SIZE", UNLIMITED_HEAP_SIZE);
}

char *Settings_StatsFileName(void) {
#ifdef SCALANATIVE_FREESTANDING
    return NULL;
#else
    return getenv(GC_STATS_FILE_SETTING);
#endif
}

// =============================================================================
// Settings Initialization
// =============================================================================
void Settings_Init(void) {

    // Initialize sync timeout settings
    SharedSettings_Init();
}

#endif // SCALANATIVE_GC_IMMIX || SCALANATIVE_GC_COMMIX
