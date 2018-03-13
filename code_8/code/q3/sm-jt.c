#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int           reg[8];
unsigned char mem[10000*4];
int           pc = -1;
unsigned char insOpCode;
unsigned char insOp0;
unsigned char insOp1;
unsigned char insOp2;
char          insOpImm;
int           insOpExt;

void fetch() {
  insOpCode = mem [pc] >> 4;
  insOp0    = mem [pc] & 0xf;
  insOp1    = mem [pc+1] >> 4;
  insOp2    = mem [pc+1] & 0xf;
  insOpImm  = mem [pc+1];
  pc += 2;
  switch (insOpCode) {
      case 0x0:
      case 0xb:
        insOpExt = mem [pc] << 24 | mem [pc+1] << 16 | mem [pc+2] << 8 | mem [pc+3];
        pc += 4;
        break;
      default:
        ;
  }
}

int exec() {
	static const void* jumpTable[16] = {&&L0, &&L1, &&L2, &&L3, &&L4, &&DEFAULT, &&L5, &&L6, &&L7,
		&&L8, &&L9, &&L10, &&L11, &&L12, &&L13, &&L14};
	static const void* jumpTable2[8] = { &&IL0, &&IL1, &&IL2, &&IL3, &&IL4, &&IL5, &&IL6, &&IL7 };
  int cont = 1;
  int addr, val;

  if (insOpCode == 0x5 || insOpCode > 0xf)
	  goto DEFAULT;

  int remainder = 0;
  int decimal_number = 0;
  for (unsigned count = 0; insOpCode > 0; count++) {
	  remainder = insOpCode % 10;
	  decimal_number += remainder * pow(16, count);
	  insOpCode /= 10;
  }
  goto *jumpTable[insOpCode];
  
  L0:
      // ld $i, d .............. 0d-- iiii iiii
      reg [insOp0] = insOpExt;
	  goto CONT;
  L1:
      // ld o(rs), rd .......... 1osd
        addr = (insOp0 << 2) + reg [insOp1];
        reg [insOp2] = mem [addr] << 24 | mem [addr+1] << 16 | mem [addr+2] << 8 | mem [addr+3];
		goto CONT;
  L2:
      // ld (rs, ri, 2), rd .... 2sid
        addr = reg [insOp0] + (reg [insOp1] << 2);
        reg [insOp2] = mem [addr] << 24 | mem [addr+1] << 16 | mem [addr+2] << 8 | mem [addr+3];
		goto CONT;
  L3:
      // st rs, o(rd) .......... 3sod
        addr = (insOp1 << 2) + reg [insOp2];
        val  = reg [insOp0];
        mem [addr]   = val >> 24 & 0xff;
        mem [addr+1] = val >> 16 & 0xff;
        mem [addr+2] = val >>  8 & 0xff;
        mem [addr+3] = val       & 0xff;
        goto CONT;
  L4:
      // st rs, (rd, ri, 4) .... 4sdi
        addr = reg [insOp1] + (reg [insOp2] << 2);
        val  = reg [insOp0];
        mem [addr]   = val >> 24 & 0xff;
        mem [addr+1] = val >> 16 & 0xff;
        mem [addr+2] = val >>  8 & 0xff;
        mem [addr+3] = val       & 0xff;
        goto CONT;
  L5:
      // ALU ................... 6-sd
		for (unsigned count = 0; insOp0 > 0; count++) {
			remainder = insOp0 % 10;
			decimal_number += remainder * pow(16, count);
			insOp0 /= 10;
		}
		if (insOp0 == 15)
			goto IL15;
		else if (insOp0 < 0 || insOp0 > 7)
			goto I_DEFAULT;
		else
			goto *jumpTable2[insOp0];
        IL0:
            // mov rs, rd ........ 60sd
              reg [insOp2] = reg [insOp1];
              goto CONT;
		IL1:
            // add rs, rd ........ 61sd
              reg [insOp2] = reg [insOp1] + reg [insOp2];
              goto CONT;
		IL2:
			// and rs, rd ........ 62sd
              reg [insOp2] = reg [insOp1] & reg [insOp2];
              goto CONT;
		IL3:
            // inc rr ............ 63-r
              reg [insOp2] = reg [insOp2] + 1;
              goto CONT;
		IL4:
            // inca rr ........... 64-r
              reg [insOp2] = reg [insOp2] + 4;
              goto CONT;
		IL5:
            // dec rr ............ 65-r
              reg [insOp2] = reg [insOp2] - 1;
              goto CONT;
		IL6:
            // deca rr ........... 66-r
              reg [insOp2] = reg [insOp2] -4;
              goto CONT;
		IL7:
            // not ............... 67-r
              reg [insOp2] = ~ reg [insOp2];
              goto CONT;
		IL15:
            // gpc ............... 6f-r
              reg [insOp2] = pc + (insOp1 << 1);
              goto CONT;
		I_DEFAULT:
              printf ("Illegal ALU instruction: pc=0x%x fun=0x%x\n", pc, insOp0);
        goto CONT;

  L6:
      // sh? $i,rd ............. 7dii
        if (insOpImm > 0)
          reg [insOp0] = reg [insOp0] << insOpImm;
        else
          reg [insOp0] = reg [insOp0] >> -insOpImm;
        goto CONT;
  L7:
      // br o .................. 8-oo
        pc += insOpImm << 1;
        goto CONT;
  L8:
      // beq rs, o ............. 9roo
        if (reg [insOp0] == 0)
          pc += insOpImm << 1;
        goto CONT;
  L9:
      // bgt rs, o .............. aroo
        if (reg [insOp0] > 0)
          pc += insOpImm << 1;
        goto CONT;
  L10:
      // j i ................... b--- iiii iiii
        pc = insOpExt;
        goto CONT;
  L11:
      // j o(rr) ............... croo
        pc = (((unsigned short) insOpImm) << 1) + reg [insOp0];
        goto CONT;
  L12:
      // j *o(rr) .............. droo
		  pc = mem[reg[insOp1] + (unsigned short)insOpImm];
        goto CONT;
  L13:
      // j*(rr,ri,4) ............. eri-
		  pc = mem[reg[insOp1] + reg[insOp2] << 2];
        goto CONT;
  L14:
      // halt or nop ............. f?--
        if (insOp0 == 0)
          cont = 0;
        goto CONT;
DEFAULT: 
		printf ("Illegal  instruction: pc=0x%x opCode=0x%x\n", pc, insOpCode);
		goto CONT;
CONT:
  return cont;
}

int loadFile (char* filename) {
  char*  line = NULL;
  size_t len  = 0;
  FILE* f = fopen (filename, "r");
  if (f == NULL)
    return 0;
  while (getline (&line, &len, f) > 0) {
    char* sep = line;
    while (*sep != ':')
      sep++;
    *sep = 0;
    int addr = strtol (line, 0, 16);
    if (pc < 0)
      pc = addr;
    line = sep + 1;
    char v[3] = {0,0,0};
    while (1) {
      while (*line && *line == ' ')
        line ++;
      if (*line == 0 || *(line+1) == 0)
        break;
      v[0] = line[0];
      v[1] = line[1];
      mem [addr] = strtol (v, 0, 16);
      line += 2;
      addr += 1;
    }
    line = NULL;
  }
  fclose (f);
  return 1;
}

void showMem (int start, int count) {
  int i;
  for (i=0; i<count*4; i+=4)
    printf ("0x%08x: %02x %02x %02x %02x\n", start+i, mem [start+i], mem [start+i+1], mem [start+i+2], mem [start+i+3]);
}

void compute() {
  int cont = 0;
  do {
    fetch();
    cont = exec();
  } while (cont);
}

struct showMemList {
  int  len;
  int* addr;
  int* count;
} showMemList;

int showReg;

int parseArgs (int argc, char** argv) {
  if (argc < 2)
    return 0;
  for (int i=1; i<argc; i++)
    if (argv[i][0] == '-') {
      char* op = argv[i] + 1;
      if (strcmp (op, "p") == 0) {
        i += 1;
        pc = strtol (argv[i], 0, 16);
      } else if (strcmp (op, "m") == 0) {
        i += 1;
        char* sep = argv[i];
        while (*sep !=':')
          sep++;
        *sep = 0;
        showMemList.len++;
        showMemList.addr = realloc (showMemList.addr, showMemList.len * sizeof (*showMemList.addr));
        showMemList.addr [showMemList.len-1] = strtol (argv[i], 0, 16);
        showMemList.count = realloc (showMemList.count, showMemList.len * sizeof (*showMemList.count));
        showMemList.count [showMemList.len-1] = strtol (sep+1, 0, 16);
      } else if (strcmp (op, "r") == 0)
        showReg = 1;
      else
        return 0;
    } else if (i != argc-1)
      return 0;
  return 1;
}

int main (int argc, char** argv) {
  if (! parseArgs (argc, argv)) {
    fprintf (stderr, "usage: sm [-p startPC] [-m addr:count]* [-r] filename\n");
    return EXIT_FAILURE;
  }
  int ok = loadFile (argv[argc-1]);
  if (! ok) {
    fprintf (stderr, "error reading input file\n");
    return EXIT_FAILURE;
  }
  compute ();
  for (int i=0; i<showMemList.len; i++)
    showMem (showMemList.addr[i], showMemList.count[i]);
  if (showReg)
    for (int i=0; i<8; i++)
      printf ("r%d: 0x%08x (%d)\n", i, reg[i], reg[i]);
}
