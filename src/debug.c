#include "debug.h"

#include <stdio.h>

#include "value.h"

void disassemble_chunk(Chunk* chunk, const char* name) {
    printf("=== %s ===\n", name);
    for (int offset = 0; offset < chunk->count;) {
        offset = disassemble_instruction(chunk, offset);
    }
}

static int simple_instruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constant_instruction(const char* name, Chunk* chunk,
                                int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);           // constant specifies index before actual value
    value_print(chunk->constants.values[constant]);  // uses constant from chunk->code. If not managed properly, can access any value outside of array bounds(UB)
    printf("'\n");
    return offset + 2;
}

int disassemble_instruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);


       case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}