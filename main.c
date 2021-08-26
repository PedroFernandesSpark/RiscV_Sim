/*
 * Pedro Fernandes - 180108069
 * Simulador Risc-V
 * Programa utilizado para codificar : CLion - Jetbeans
 * Compilador utilizado : Microsoft Visual Studio 1019 community
 * Sistema Operacional : Windows 10
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];

// Register list:
uint32_t pc = 0, ri = 0, sp = 0x00003ffc, gp = 0x00001800;
int32_t opcode, rs1, rs2, rd, shamt, funct3, funct7;
int32_t		imm12_i, imm12_s, imm13, imm20_u, imm21;



// Memory access func
int8_t end = 0;
uint32_t lw(uint32_t address, int32_t kte);
int32_t lb(uint32_t address, int32_t kte);
int32_t lb(uint32_t address, int32_t kte);
int32_t lbu(uint32_t address, int32_t kte);
void sw(uint32_t address, int32_t kte, int32_t dado);
void sb(uint32_t address, int32_t kte, int8_t dado);
int32_t imm_format_i(int32_t imm);
int32_t imm_format_s(int32_t imm_1,int32_t imm_2);
int32_t imm_format_sb(int32_t imm_1,int32_t imm_2);
int32_t imm_format_uj(int32_t imm);

// Binary convert func
int load_mem();

// Dump func
void dump_mem(int start, int end, char format);
void dump_reg(char format);

// Execute func
void fetch();
void decode();
void step();
void execute();
void run();

int main() {
    int load_mem_status = load_mem();
    run();
    //printf("Load_mem returned status code: %i \n\n", load_mem_status);

    //printf("Registers list:\n");
    //dump_reg('h');

    //printf("Memory dump:\n");
    //dump_mem(0, 4096, 'h');

    return 0;
}

void fetch(){
    ri = lw(pc, 0);
    pc += 4;
}

void run(){
    while(!end && pc < 20000){
        step();

    }
}

void step(){
    fetch();
    decode();
    execute();
    return;
}

void decode(){
    int32_t buff = ri;
    opcode = buff&0b00000000000000000000000001111111;
    if(opcode < 0b0100011 && opcode > 0000010 || opcode == 1110011 || opcode == 1100111){ // I
        rd     = buff&0b00000000000000000000111110000000;
        rd     = rd >> 7;
        funct3 = buff&0b00000000000000000111000000000000;
        funct3 = funct3 >> 12;
        rs1    = buff&0b00000000000011111000000000000000;
        rs1    = rs1 >> 15;
        imm12_i= buff&0b11111111111100000000000000000000;
        imm12_i= imm_format_i(imm12_i);
    }
    if(opcode < 0111100 && opcode > 00110010 && opcode != 0110111){ // R
        rd     = buff&0b00000000000000000000111110000000;
        rd     = rd >> 7;
        funct3 = buff&0b00000000000000000111000000000000;
        funct3 = funct3 >> 12;
        rs1    = buff&0b00000000000011111000000000000000;
        rs1    = rs1 >> 15;
        rs2    = buff&0b00000001111100000000000000000000;
        rs2    = rs2 >> 20;
        funct7 = buff&0b11111110000000000000000000000000;
    }
    if(opcode == 0100011){ //S
        imm12_s= buff&0b00000000000000000000111110000000;
        funct3 = buff&0b00000000000000000111000000000000;
        funct3 = funct3 >> 12;
        rs1    = buff&0b00000000000011111000000000000000;
        rs1    = rs1 >> 15;
        rs2    = buff&0b00000001111100000000000000000000;
        rs2    = rs2 >> 20;
        imm13  = buff&0b11111110000000000000000000000000;
        imm13  = imm_format_s(imm12_s,imm13);
    }
    if(opcode == 1100011){ //SB
        imm12_s= buff&0b00000000000000000000111110000000;
        funct3 = buff&0b00000000000000000111000000000000;
        funct3 = funct3 >> 12;
        rs1    = buff&0b00000000000011111000000000000000;
        rs1    = rs1 >> 15;
        rs2    = buff&0b00000001111100000000000000000000;
        rs2    = rs2 >> 20;
        imm13 = buff&0b11111110000000000000000000000000;
        imm13 = imm_format_sb(imm12_s,imm13);
    }
    if(opcode == 1101111){ //UJ
        rd     = buff&0b00000000000000000000111110000000;
        rd     = rd >> 7;
        imm21  = buff&0b11111111111111111111000000000000;
        imm21  = imm_format_uj(imm21);
    }
    else{
        rd     = buff&0b00000000000000000000111110000000;
        rd     = rd >> 7;
        imm20_u= buff&0b11111111111111111111000000000000;
    }
}

int32_t imm_format_i(int32_t imm){
    imm = imm & 0xfff00000;
    imm = imm >> 20;
    return imm;
}
int32_t imm_format_uj(int32_t imm){
    int32_t imm_1, imm_2, imm_3, imm_4, imm_full;
    imm_full = 0b11111111111111111111111111111111;
    imm_1 = imm & 0b00000001111000000000000000000000;
    imm_1 = imm_1 >> 21;
    imm_2 = imm & 0b01111110000000000000000000000000;
    imm_2 = imm_2 >> 21;
    imm_3 = imm & 0b00000000000000000001000000000000;
    imm_3 = imm_3 >> 21;
    imm_4 = imm & 0b10000000000000000000000000000000;
    imm_4 = imm_4 >> 21;
    imm_full = imm_full & imm_1;
    imm_full = imm_full & imm_2;
    imm_full = imm_full & imm_3;
    imm_full = imm_full & imm_4;
    return imm_full;
}
int32_t imm_format_s(int32_t imm_1,int32_t imm_2){
    int32_t imm;
    imm = 0b11111111111111111111111111111111;
    imm_1 = imm_1 >> 7;
    imm_2 = imm_2 >> 20;
    imm = imm & imm_1;
    imm = imm & imm_2;
    return imm;
}
int32_t imm_format_sb(int32_t imm_1,int32_t imm_2){
    int32_t imm;
    int32_t imm_3,imm_4;
    imm = 0b11111111111111111111111111111111;
    imm_1 = imm_1 >> 7;
    imm_3 = imm_1 & 0b00000000000000000000000000000001;
    imm_1 = imm_1 & 0b00000000000000000011111111111110;
    imm_2 = imm_2 >> 20;
    imm_4 = imm_2 & 0b00000000000000000001000000000000;
    imm_3 = imm_3 << 10;
    imm_4 = imm_4 << 1;
    imm = imm & imm_1;
    imm = imm & imm_2;
    imm = imm & imm_3;
    imm = imm & imm_4;
    return imm;
}

void execute(){
    if(opcode == 0b0110011 && funct3 == 0b000 & funct7 == 0b000000){ // add
        mem[rd] = mem[rs1] + mem[rs2];
    }
    if(opcode == 0b0110011 && funct3 == 0b000 & funct7 == 0b010000){ // sub
        mem[rd] = mem[rs1] + mem[rs2];
    }
    if(opcode == 0b0010011 && funct3 == 0b000){ // addi
        mem[rd] = mem[rs1] + imm12_i;
    }
    if(opcode == 0b0110011 && funct3 == 0b111 & funct7 == 0b010000){ // and
        mem[rd] = mem[rs1] & mem[rs2];
    }
    if(opcode == 0b0010011 && funct3 == 0b111){ // andi
        mem[rd] = mem[rs1] & imm12_i;
    }
    if(opcode == 0b0010111){ // auipc
        mem[rd] = pc + imm20_u;
    }
    if(opcode == 0b1100011 && funct3 == 0b000){ // beq
        if(mem[rs1] == mem[rs2]){
            pc=pc+imm13;
        }
    }
    if(opcode == 0b1100011 && funct3 == 0b001){ // bne
        if(mem[rs1] != mem[rs2]){
            pc=pc+imm13;
        }
    }
    if(opcode == 0b1100011 && funct3 == 0b101){ // bge
        if(mem[rs1] >= mem[rs2]){
            pc=pc+imm13;
        }
    }
    if(opcode == 0b1100011 && funct3 == 0b111){ // bgeu
        if(mem[rs1] >= mem[rs2]){
            pc=pc+imm13;
        }
    }
    if(opcode == 0b1100011 && funct3 == 0b100){ // blt
        if(mem[rs1] < mem[rs2]){
            pc=pc+imm13;
        }
    }
    if(opcode == 0b1100011 && funct3 == 0b110){ // bltu
        if(mem[rs1] < mem[rs2]){
            pc=pc+imm13;
        }
    }
    if(opcode == 0b1101111){ // jl
        mem[rd] = pc+4;pc=pc+imm21;
    }
    if(opcode == 0b1100111 && funct3 == 0b000){ // jlr
        mem[rd] = pc+4;pc=mem[rs1]+imm12_i;
    }
    if(opcode == 0b0000011 && funct3 == 0b000){ // lb
        mem[rd] = lb(rs1, imm12_i);
    }
    if(opcode == 0b0110011 && funct3 == 0b110 && funct7 == 0b000000){ // or
        mem[rd] = mem[rs1] | mem[rs2];
    }
    if(opcode == 0b0000011 && funct3 == 0b100){ // lbu
        mem[rd] = lbu(rs1, imm12_i);
    }
    if(opcode == 0b0000011 && funct3 == 0b010){ // lw
        mem[rd] = lw(rs1, imm12_i);
    }
    if(opcode == 0b0110111){ // lui
        mem[rd] = lw(imm20_u, 0);
    }
    if(opcode == 0b0110011 && funct3 == 0b011 && funct7 == 0b0000000){ // sltu
        if(mem[rs1] <= mem[rs2]){
            mem[rd] = 1;
        }
        else{
            mem[rd] = 0;
        }
    }
    if(opcode == 0b0010111 && funct3 == 0b110){ // ori
        mem[rd] =  mem[rs1] | imm12_i;
    }
    if(opcode == 0b0100011 && funct3 == 0b000){ // sb
        sb(mem[rs1], imm12_s, mem[rs2]);
    }
    if(opcode == 0b0010011 && funct3 == 0b001 && funct7 == 0b0000000){ // slli

    }
    if(opcode == 0b0010011 && funct3 == 0b001 && funct7 == 0b0000000){ // slt
        if(mem[rs1] < mem[rs2]){
            mem[rd] = 1;
        }
        else{
            mem[rd] = 0;
        }
    }
    if(opcode == 0b0010011 && funct3 == 0b101 && funct7 == 0b0100000){ // srai
        mem[rd] = mem[rs1] >> imm12_i;
    }
    if(opcode == 0b0010011 && funct3 == 0b101 && funct7 == 0b0000000){ // srli
        if(mem[rs1] < imm12_i){
            mem[rd] = 1;
        }
        else{
            mem[rd] = 0;
        }
    }
    if(opcode == 0b0100011 && funct3 == 0b010){ // sw
        sw(mem[rs1], imm12_s, mem[rs2]);
    }
    if(opcode == 0b0110011 && funct3 == 0b100 && funct7 == 0b0000000){ // xor
        mem[rd] = mem[rs1] ^ mem[rs2];
    }
    if(opcode == 0b1110011 && funct3 == 0b000 && funct7 == 0b0000000){ // Syscall
        if(imm12_i == 1){
            printf("%i", mem[0x10]);
            printf("\n");
        }
        if(imm12_i == 8){
            for (int i=0; i < mem[0x11]; i++){
                printf("%c", mem[0x11+i]);
            }
            printf("\n");
        }
        if(imm12_i == 10){
            end = 1;
            printf("Risc-V returned 0");
        }
    }
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
        printf("OPCODE => %X \n", opcode);
        printf("RD => %X \n", rd);
        printf("RS1 => %X \n", rs1);
        printf("RS2 => %X \n", rs2);
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

uint32_t lw(uint32_t address, int32_t kte){
    uint32_t add = address+kte;
    if(add % 4 == 0){
        return mem[add/4];
    }
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