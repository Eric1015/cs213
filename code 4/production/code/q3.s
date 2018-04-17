.pos 0x100
code:
                 ld $i, r0                # r0 = address of i
                 ld $v0, r1               # r1 = address of v0
                 ld $v1, r3               # r3 = address of v1
                 ld $v2, r4               # r4 = address of v2
                 ld $v3, r5               # r5 = address of v3
                 ld $s, r2                # r2 = address of s.x[0]

                 # v0 = s.x[i]
                 ld 0x0(r0), r6           # r6 = i
                 ld (r2, r6, 4), r7       # r7 = s.x[i]
                 st r7, 0(r1)             # v0 = s.x[i]

                 # v1 = s.y[i]
                 ld $2, r7                # r7 = 2
                 ld (r2, r7, 4), r0       # r0 = address of s.y
                 st r3, (r0, r6, 4)       # v1 = s.y[i]

                 # v2 = s.z->x[i]
                 ld $3, r7                # r7 = 3
                 ld (r2, r7, 4), r0       # r0 = address of s.z
                 st r4, (r0, r6, 4)       # v2 = s.z->x[i]

                 # v3 = s.z->z->y[i]
                 ld (r0, r7, 4), r0       # r0 = address of s.z->z
                 ld $2, r7                # r7 = 2
                 ld (r0, r7, 4), r0       # r0 = address of s.z->z->y
                 st r5, (r0, r6, 4)       # v3 = s.z->z->y[i]

                 halt
.pos 0x2000
static:
i:               .long 1                  # i
v0:              .long 0                  # v0
v1:              .long 0                  # v1
v2:              .long 0                  # v2
v3:              .long 0                  # v3
s:               .long 1                  # x[0]
                 .long 2                  # x[1]
                 .long s_y                # *y
                 .long s_z                # *z

.pos 0x3000
heap:
s_y:             .long 3                  # s.y[0]
                 .long 4                  # s.y[1]
s_z:             .long 5                  # s.z->x[0]
                 .long 6                  # s.z->x[1]
                 .long s_z_y              # s.z->y
                 .long s_z_z              # s.z->z
s_z_z:           .long 9                  # s.z->z->x[0]
                 .long 10                  # s.z->z->x[1]
                 .long s_z_z_y            # s.z->z->y
s_z_z_y:         .long 11                  # s.z->z->y[0]
                 .long 12                  # s.z->z->y[1]
s_z_y:           .long 7                  # s.z->y[0]
                 .long 8                  # s.z->y[1]
