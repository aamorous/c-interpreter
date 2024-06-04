#ifndef cin_chunk_h
#define cin_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {  // array of bytes
    int count;    // it's used as code[count]
    int capacity;
    uint8_t* code;  // pointer to an array
    int* line; // not very efficient
    ValueArray constants;  // constant pool known at compile-time
} Chunk;

void chunk_init(Chunk* chunk);
void chunk_write(Chunk* chunk, uint8_t byte);
int chunk_add_constant(Chunk* chunk, Value value);
void chunk_free(Chunk* chunk);

#endif