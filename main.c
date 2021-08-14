#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];

// Register list:
uint32_t pc = 0, ri = 0, sp = 0x00003ffc, gp = 0x00001800;
int32_t opcode, rs1, rs2, rd, shamt, funct3, funct7;

// Memory access func
int32_t lw(uint32_t address, int32_t kte);
int32_t lb(uint32_t address, int32_t kte);
int32_t lb(uint32_t address, int32_t kte);
int32_t lbu(uint32_t address, int32_t kte);
void sw(uint32_t address, int32_t kte, int32_t dado);
void sb(uint32_t address, int32_t kte, int8_t dado);

// Binary convert func
int load_mem();

// Dump func
void dump_mem(int start, int end, char format);
void dump_reg(char format);

// Execute func
void fetch();


int main() {
    int load_mem_status = load_mem();
    printf("Load_mem returned status code: %i \n\n", load_mem_status);

    printf("Registers list:\n");
    dump_reg('h');

    printf("Memory dump:\n");
    dump_mem(0, 4096, 'h');

    return 0;
}

void fetch(){
    ri = lw(pc,0);
    pc += 4;
}


void dump_mem(int start, int end, char format){
    for(int i=start; i<end+1; i++){
        if(format == 'h')
            printf("%X  ",mem[i]);
        if(format == 'd')
            printf("%d  ",mem[i]);
    }
    printf("\n");
    printf("\n");
}

void dump_reg(char format){
    if(format == 'h'){
        printf("PC => %X \n", pc);
        printf("RI => %X \n", ri);
        printf("SP => %X \n", sp);
        printf("GP => %X \n", gp);
    }
    if(format == 'd'){
        printf("PC => %d \n", pc);
        printf("RI => %d \n", ri);
        printf("SP => %d \n", sp);
        printf("GP => %d \n", gp);
    }
    printf("\n");
}

int load_mem(){
    const char* file_name_code = "C:\\Users\\pedro\\Documents\\RiscV_Sim\\code.bin";
    const char* file_name_data = "C:\\Users\\pedro\\Documents\\RiscV_Sim\\data.bin";
    FILE* ptr = fopen(file_name_code,"rb");
    FILE* ptr2 = fopen(file_name_data,"rb");
    if(!ptr){
        printf("code.bin open error \n");
        return 1;
    }
    if(!ptr2){
        printf("data.bin open error \n");
        return 2;
    }
    fread(mem, sizeof(int32_t),0x55, ptr);
    fclose(ptr);
    fread(&mem[85], sizeof(int32_t),0xffd, ptr2);
    fclose(ptr2);
    return 0;
}

int32_t lw(uint32_t address, int32_t kte){
    uint32_t add = address+kte;
    if(add % 4 == 0)
        return mem[add/4];
    else{
        printf("O valor de Address + Kte deve ser um multiplo de 4\n");
        return 0;
    }
}

int32_t lb(uint32_t address, int32_t kte){
    char *ponteiro;
    uint32_t add;
    int8_t value;

    add = address + kte;
    ponteiro = mem;
    value = *(ponteiro+add);
    value = value & 0x000f;
    return value;
}

int32_t lbu(uint32_t address, int32_t kte){
    char *ponteiro;
    uint32_t add;
    int8_t value;

    add = address + kte;
    ponteiro = mem;

    value = *(ponteiro+add);
    value = value & 0x000f;
    if(value > 0)
        return value;
    else
        return -1*value;
}

void sw(uint32_t address, int32_t kte, int32_t dado){
    uint32_t add = address+kte;
    if(add % 4 != 0){
        printf("O valor de Address + Kte deve ser um multiplo de 4\n");
        return;
    }
    else{
        mem[add/4] = dado;
        return;
    }
}

void sb(uint32_t address, int32_t kte, int8_t dado){
    uint32_t add;
    char *ponteiro;

    ponteiro = mem;
    add = address+kte;

    *(ponteiro+add) = dado;
}