
.pos 0x1000
          # start
          ld  $sb, r5         # r5 = address of sb
          inca r5             # word after the last word of stack
          gpc $6, r6          # r6 = return address
          j   copy            # goto copy
          halt


.pos 0x2000
copy:     deca r5             # allocate space for frame
          st  r6, (r5)        # save ra on stack
          ld  $0, r0          # r0 = temp_i = 0
          ld  $src, r2        # r2 = address of src
          deca r5             # allocate space for dst array
          deca r5             # allocate space for dst array
L1:       ld  (r2, r0, 4), r4 # r4 = src[temp_i]
          beq r4, L1_end      # goto L1_end if src[temp_i] == 0
          st  r4, (r5, r0, 4) # dst[temp_i] = src[temp_i]
          inc r0              # temp_i++
          br  L1              # goto L1
L1_end:   ld  $0, r3          # r3 = 0
          st  r3, (r5, r0, 4) # dst[temp_i] = 0
          inca r5             # discard callee part of the frame
          inca r5             # discard callee part of the frame
          j   0(r5)           # goto ra

.pos 0x3000
src:      .long 0x1
          .long 0x2
          .long 0xb0000000
          .long 0x30200000
          .long 0xff00
          .long 0xff00
          .long 0xff00
          .long 0xff00
          .long 0xff00
          .long 0xff00
          .long 0xff00
          .long 0x0
          .long 0xff00
          .long 0x0000ffff
          .long 0xffff0100
          .long 0xffffffff
          .long 0x0200ffff
          .long 0xffff0300
          .long 0xffffffff
          .long 0x0400ffff
          .long 0xffff0500
          .long 0xffffffff
          .long 0x0600ffff
          .long 0xffff0700
          .long 0xffffffff
          .long 0xf000ff00
          .long 0xff00ff00

.pos 0x4000
          .long 0x0000ffff
          .long 0xffff0100
          .long 0xffffffff
          .long 0x0200ffff
          .long 0xffff0300
          .long 0xffffffff
          .long 0x0400ffff
          .long 0xffff0500
          .long 0xffffffff
          .long 0x0600ffff
          .long 0xffff0700
          .long 0xffffffff
          .long 0xf0000000

.pos 0x8000
          .long 0x0
          .long 0x0
          .long 0x0
          .long 0x0
          .long 0x0
          .long 0x0
          .long 0x0
          .long 0x0
sb:       .long 0x0
