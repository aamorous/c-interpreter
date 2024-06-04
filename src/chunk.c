#include "chunk.h"

#include <stdlib.h>

#include "memory.h"

void chunk_init(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    value_array_init(&chunk->constants);
}

void chunk_write(Chunk* chunk, uint8_t byte) {
    if (chunk->capacity == chunk->count) {  // changed from 'x < y + 1' 'to x == y'
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
                                 old_capacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

int chunk_add_constant(Chunk* chunk, Value value) {
    value_array_write(&chunk->constants, value);
    return chunk->constants.count - 1;  // return index for locating constant later
}

void chunk_free(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    value_array_free(&chunk->constants);
    chunk_init(chunk);
}