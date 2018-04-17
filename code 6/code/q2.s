.pos 0x100
                 ld   $0x0, r0            # r0 = temp_i = 0
                 ld   $a, r1              # r1 = address of a[0]
                 ld   $0x0, r2            # r2 = temp_s = 0
                 ld   $0xfffffffb, r4     # r4 = -5
loop:            mov  r0, r5              # r5 = temp_i
                 add  r4, r5              # r5 = temp_i-5
                 beq  r5, end_loop        # goto end_loop if temp_i=5 
                 ld   (r1, r0, 4), r3     # r3 = a[temp_i]
                 bgt  r3, then            # goto then if a[temp_i] > 0
end_if:          inc  r0                  # temp_i++
                 br   loop                # goto loop
then:            add  r3, r2              # temp_s += a[temp_i]
                 br   end_if              # goto end_if
end_loop:        ld   $s, r1              # r1 = address of s
                 st   r2, 0x0(r1)         # s = temp_s
                 st   r0, 0x4(r1)         # i = temp_i
                 halt
.pos 0x1000
s:               .long 0x00000000         # s
i:               .long 0x00000010         # i
a:               .long 0x0000000a         # a[0]
                 .long 0xffffffe2         # a[1]
                 .long 0xfffffff4         # a[2]
                 .long 0x00000004         # a[3]
                 .long 0x00000008         # a[4]
