#ifndef IMMIX_COMMIX_STACK_H
#define IMMIX_COMMIX_STACK_H

#include "shared/GCTypes.h"
#include "immix_commix/headers/ObjectHeader.h"

#ifdef SCALANATIVE_FREESTANDING
#ifndef INITIAL_STACK_SIZE
#define INITIAL_STACK_SIZE 1024
#endif
#else
#define INITIAL_STACK_SIZE (256 * 1024)
#endif

typedef Object *Stack_Type;

typedef struct {
    Stack_Type *bottom;
    size_t nb_words;
    uint32_t current;
} Stack;

void Stack_Init(Stack *stack, size_t size);

void Stack_Push(Stack *stack, Stack_Type word);

Stack_Type Stack_Pop(Stack *stack);

bool Stack_IsEmpty(Stack *stack);

#endif // IMMIX_COMMIX_STACK_H
