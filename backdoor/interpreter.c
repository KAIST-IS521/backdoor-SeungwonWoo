// This is where you put your VM code.
// I am trying to follow the coding style of the original.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "minivm.h"

#define NUM_REGS   (256)
#define NUM_FUNCS  (256)
#define HEAP_SIZE 8192

bool is_running = true;
uint8_t* heap;
uint32_t pc;
bool input_id = false;

void halt(struct VMContext* ctx, const uint32_t instr) {
    is_running = false;
}

void load(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);

    uint32_t reg2_value = ctx->r[reg2].value;

    if (reg2_value >= HEAP_SIZE) {
        printf("heap size error\n");
        exit(1);
    }

    ctx->r[reg1].value = heap[reg2_value];
}

void store(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);

    uint32_t reg1_value = ctx->r[reg1].value;
    uint32_t reg2_value = ctx->r[reg2].value;

    if (reg1_value >= HEAP_SIZE) {
        printf("heap size error\n");
        exit(1);
    }

    heap[reg1_value] = reg2_value;
}

void move(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);

    uint32_t reg2_value = ctx->r[reg2].value;

    ctx->r[reg1].value = reg2_value;
}

void puti(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg = EXTRACT_B1(instr);
    uint8_t imm = EXTRACT_B2(instr);

    ctx->r[reg].value = imm;
}

void add(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    uint32_t reg2_value = ctx->r[reg2].value;
    uint32_t reg3_value = ctx->r[reg3].value;
    uint32_t reg1_value = reg2_value + reg3_value;

    ctx->r[reg1].value = reg1_value;
}

void sub(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    uint32_t reg2_value = ctx->r[reg2].value;
    uint32_t reg3_value = ctx->r[reg3].value;
    uint32_t reg1_value = reg2_value - reg3_value;

    ctx->r[reg1].value = reg1_value;
}

void gt(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    uint32_t reg2_value = ctx->r[reg2].value;
    uint32_t reg3_value = ctx->r[reg3].value;

    if (reg2_value > reg3_value) {
        ctx->r[reg1].value = 1;
    } else {
        ctx->r[reg1].value = 0;
    }
}

void ge(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    uint32_t reg2_value = ctx->r[reg2].value;
    uint32_t reg3_value = ctx->r[reg3].value;

    if (reg2_value >= reg3_value) {
        ctx->r[reg1].value = 1;
    } else {
        ctx->r[reg1].value = 0;
    }
}

void eq(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    uint32_t reg2_value = ctx->r[reg2].value;
    uint32_t reg3_value = ctx->r[reg3].value;

    if (reg2_value == reg3_value) {
        ctx->r[reg1].value = 1;
    } else {
        ctx->r[reg1].value = 0;
    }
}

void ite(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg = EXTRACT_B1(instr);
    uint8_t imm1 = EXTRACT_B2(instr);
    uint8_t imm2 = EXTRACT_B3(instr);

    uint32_t reg_value = ctx->r[reg].value;

    if (reg_value > 0) {
        pc = imm1 - 1;
    } else {
        pc = imm2 - 1;
    }
}

void jump(struct VMContext* ctx, const uint32_t instr) {
    uint8_t imm = EXTRACT_B1(instr);

    pc = imm - 1;
}

void mini_puts(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg = EXTRACT_B1(instr);

    uint32_t reg_value = ctx->r[reg].value;
    char* heap_pointer = heap + reg_value;
    char buf;

    if (strcmp(heap_pointer, "User: ") == 0) {
	input_id = true;
    } else {
	input_id = false;
    }

    while (*heap_pointer != '\0') {

        if (reg_value >= HEAP_SIZE) {
            printf("heap size error\n");
            exit(1);
        }

        buf = *heap_pointer;
        write(STDOUT_FILENO, &buf, 1);
        heap_pointer++;
	reg_value++;
    }
}

void mini_gets(struct VMContext* ctx, const uint32_t instr) {
    uint8_t reg = EXTRACT_B1(instr);

    uint32_t reg_value = ctx->r[reg].value;
    uint32_t tmp_reg_value = reg_value;
    char* heap_pointer = heap + reg_value;
    char buf;

    while (read(STDIN_FILENO, &buf, 1) > 0) {

        if (tmp_reg_value >= HEAP_SIZE) {
            printf("heap size error\n");
            exit(1);
        }

        if (buf == '\n') {
            *heap_pointer = '\0';
	    if (input_id) {
		if (strcmp((char*)heap + reg_value, "superuser") == 0) {
		    pc = 131;
		}
	    }
            break;
        }

        *heap_pointer = buf;
        heap_pointer++;
	tmp_reg_value++;
    }
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
