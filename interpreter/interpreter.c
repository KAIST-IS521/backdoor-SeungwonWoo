// This is where you put your VM code.
// I am trying to follow the coding style of the original.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minivm.h"

#define NUM_REGS   (256)
#define NUM_FUNCS  (256)
#define HEAP_SIZE 8192

bool is_running = true;
uint8_t* heap;

void halt(struct VMContext* ctx, const uint32_t instr) {

}

void load(struct VMContext* ctx, const uint32_t instr) {

}

void store(struct VMContext* ctx, const uint32_t instr) {

}

void move(struct VMContext* ctx, const uint32_t instr) {

}

void puti(struct VMContext* ctx, const uint32_t instr) {

}

void add(struct VMContext* ctx, const uint32_t instr) {

}

void sub(struct VMContext* ctx, const uint32_t instr) {

}

void gt(struct VMContext* ctx, const uint32_t instr) {

}

void ge(struct VMContext* ctx, const uint32_t instr) {

}

void eq(struct VMContext* ctx, const uint32_t instr) {

}

void ite(struct VMContext* ctx, const uint32_t instr) {

}

void jump(struct VMContext* ctx, const uint32_t instr) {

}

void mini_puts(struct VMContext* ctx, const uint32_t instr) {

}

void mini_gets(struct VMContext* ctx, const uint32_t instr) {

}

void usageExit() {
    // TODO: show usage
    exit(1);
}

void initFuncs(FunPtr *f, uint32_t cnt) {
    uint32_t i;
    for (i = 0; i < cnt; i++) {
        f[i] = NULL;
    }

    // TODO: initialize function pointers
    f[0x00] = halt;
    f[0x10] = load;
    f[0x20] = store;
    f[0x30] = move;
    f[0x40] = puti;
    f[0x50] = add;
    f[0x60] = sub;
    f[0x70] = gt;
    f[0x80] = ge;
    f[0x90] = eq;
    f[0xa0] = ite;
    f[0xb0] = jump;
    f[0xc0] = mini_puts;
    f[0xd0] = mini_gets;
}

void initRegs(Reg *r, uint32_t cnt)
{
    uint32_t i;
    for (i = 0; i < cnt; i++) {
        r[i].type = 0;
        r[i].value = 0;
    }
}

int main(int argc, char** argv) {
    VMContext vm;
    Reg r[NUM_REGS];
    FunPtr f[NUM_FUNCS];
    FILE* bytecode;
    uint32_t pc;
    uint32_t* content;
    uint32_t content_size;

    // There should be at least one argument.
    if (argc < 2) usageExit();

    // Initialize registers.
    initRegs(r, NUM_REGS);
    // Initialize interpretation functions.
    initFuncs(f, NUM_FUNCS);
    // Initialize VM context.
    initVMContext(&vm, NUM_REGS, NUM_FUNCS, r, f);

    // Load bytecode file
    bytecode = fopen(argv[1], "rb");
    if (bytecode == NULL) {
        perror("fopen");
        return 1;
    }

    // Initialize pc
    pc = 0;
    // Initialize heap
    heap = (uint8_t*)malloc(HEAP_SIZE);
    // Initialize content_size
    fseek(bytecode, 0, SEEK_END);
    content_size = ftell(bytecode);
    fseek(bytecode, 0, SEEK_SET);
    // Initialize content
    content = (uint32_t*)malloc(content_size);
    fread(content, 1, content_size, bytecode);

    while (is_running) {
        // TODO: Read 4-byte bytecode, and set the pc accordingly
        stepVMContext(&vm, &pc, content);
    }

    free(heap);
    free(content);
    fclose(bytecode);

    // Zero indicates normal termination.
    return 0;
}
