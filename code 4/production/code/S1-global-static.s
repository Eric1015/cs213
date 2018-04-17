.pos 0x100
                 ld $a, r0                # r0 = address of a
                 ld 0(r0), r0             # r0 = value of a
                 ld $array, r1            # r1 = address of array
                 ld 0(r1), r2             # r2 = value of array[0]
                 ld 4(r1), r3             # r3 = value of array[1]
                 nop
                 ld (r1, r2, 4), r4       # r4 = value of array[1]
                 ld (r1, r3, 4), r5
                 halt                     # halt
.pos 0x1000
a:               .long 0xffffffff         # a

.pos 0x2000
array:           .long 0x00000001         # array[0]
                 .long 0x00000002         # array[1]
                 .long 0x00000001         # array[2]
