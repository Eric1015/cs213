.pos 0x100
          ld $0x1000, r1      # r1 = 0x1000
          j  *4(r1)           # goto 0x1004


.pos 0x1000
          .long 0x100
          .long 0x2000


.pos 0x2000
          ld $0x3000, r2      # r2 = 0x2000
          ld $5, r3           # r3 = 5
          j  *(r2, r3, 4)     # goto 0x3020

.pos 0x3000
          .long 0x100
          .long 0x100
          .long 0x100
          .long 0x100
          .long 0x100
          .long 0x4000

.pos 0x4000
          ld $0, r4         # r4 = 0
          halt
