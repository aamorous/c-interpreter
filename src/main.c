#include "chunk.c"  // +
#include "chunk.h"
#include "common.h"
#include "debug.c"  // +
#include "debug.h"
#include "memory.c"  // +
#include "value.c"   // +

int main(int argc, const char* argv[]) {
    Chunk chunk;

    chunk_init(&chunk);

    int constant_index = chunk_add_constant(&chunk, 1.22);
    chunk_write(&chunk, OP_CONSTANT);
    chunk_write(&chunk, constant_index);
    chunk_write(&chunk, OP_RETURN);

    disassemble_chunk(&chunk, "test");

    chunk_free(&chunk);
    return 0;
}