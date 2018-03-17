.pos 0x800
          ld $0x2000, r2      # r2 = 0x2000
          ld $5, r3           # r3 = 5
          j  *(r2, r3, 4)     # goto 0x2020

.pos 0x2000
          .long 0x100
          .long 0x100
          .long 0x100
          .long 0x100
          .long 0x100
          .long 0x3000

.pos 0x3000
          ld $8, r5           # r5 = 8
          halt
          
