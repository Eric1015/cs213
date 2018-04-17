.pos 0x0
                 ld   $sb, r5                   # r5 = sp = address of sb
                 inca r5                        # sp = address of word after stack
                 gpc  $6, r6                    # r6 = return address to itself
                 j    0x300                     # goto function foo (say function foo is at 0x300)
                 halt
.pos 0x100
                 .long 0x00001000
.pos 0x200
                 ld   0x0(r5), r0               # r0 = a = first arg
                 ld   0x4(r5), r1               # r1 = b = second arg
                 ld   $0x100, r2                # r2 = address of c
                 ld   0x0(r2), r2               # r2 = c (an array)
                 ld   (r2, r1, 4), r3           # r3 = c[b]
                 add  r3, r0                    # r0 = c[b] + a
                 st   r0, (r2, r1, 4)           # c[b] += a
                 j    0x0(r6)                   # goto return address to foo
.pos 0x300
                 ld   $0xfffffff4, r0           # r0 = -12
                 add  r0, r5                    # sp -= 12
                 st   r6, 0x8(r5)               # save ra on stack
                 ld   $0x1, r0                  # r0 = 1
                 st   r0, 0x0(r5)               # *sp = 1 (save on stack)
                 ld   $0x2, r0                  # r0 = 2
                 st   r0, 0x4(r5)               # *sp = 2 (save on stack)
                 ld   $0xfffffff8, r0           # r0 = -8
                 add  r0, r5                    # sp -= 8
                 ld   $0x3, r0                  # r0 = 3 (value of first arg)
                 st   r0, 0x0(r5)               # *sp = 3 (save first arg on stack)
                 ld   $0x4, r0                  # r0 = 4 (value of second arg)
                 st   r0, 0x4(r5)               # *sp = 4 (save second arg on stack)
                 gpc  $6, r6                    # r6 = return address to itself
                 j    0x200                     # goto function add (say function add is at 0x200)
                 ld   $0x8, r0                  # r0 = 8
                 add  r0, r5                    # sp += 8
                 ld   0x0(r5), r1               # r1 = 1 (value of first arg)
                 ld   0x4(r5), r2               # r2 = 2 (value of second arg)
                 ld   $0xfffffff8, r0           # r0 = -8
                 add  r0, r5                    # sp -= 8
                 st   r1, 0x0(r5)               # *sp = 1 (save first arg on stack)
                 st   r2, 0x4(r5)               # *sp = 2 (save second arg on stack)
                 gpc  $6, r6                    # r6 = return address to itself
                 j    0x200                     # goto function add
                 ld   $0x8, r0                  # r0 = 8
                 add  r0, r5                    # sp -= 8
                 ld   0x8(r5), r6               # r6 = sb (get return address to main from memory)
                 ld   $0xc, r0                  # r0 = 12
                 add  r0, r5                    # sp += 12
                 j    0x0(r6)                   # goto return address to main
.pos 0x1000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
.pos 0x8000
# These are here so you can see (some of) the stack contents.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0
