.pos 0x1000
          gpc $34, r7
          br  test3



test:     ld  $0, r2
          beq r2, test4

test2:    ld  $1, r2
          bgt r2, test

test3:    j   test2

test4:    ld  $0x2000, r3
          j   6(r3)
          ld  $0x2000, r3

.pos 0x2000
          ld $0, r0
          ld $0, r0
          ld $0, r0
          halt
