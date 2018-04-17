.pos 0x100
start:
    ld $sb, r5              # r5 = &sb = sp (sp points to the last word in stack)
    inca    r5              # sp += 4  (sp points to word after stack)
    gpc $6, r6              # r6 = return address to itself
    j main                  # goto function countNumOfOne (say function countNumOfOne is at the address of main)
    halt

f:
    deca r5                 # sp -= 4
    ld $0, r0               # r0 = temp_k =  0
    ld 4(r5), r1            # r1 = x[temp_i - 1] = first arg
    ld $0x80000000, r2      # r2 = -2147483648
f_loop:
    beq r1, f_end           # goto f_end if x[temp_i - 1] == 0
    mov r1, r3              # r3 = temp_j = x[temp_i - 1] (copy)
    and r2, r3              # r3 = -2147483648 if (x[temp_i - 1] < 0), else r3 = 0
    beq r3, f_if1           # goto f_if1 if temp_j => 0
    inc r0                  # temp_k++
f_if1:
    shl $1, r1              # x[temp_i - 1] *= 2
    br f_loop               # goto f_loop
f_end:
    inca r5                 # sp += 4
    j(r6)                   # goto the return address

main:
    deca r5                   # sp -= 4      (allocate callee part of main's frame)
    deca r5                   # sp -= 4
    st r6, 4(r5)              # *sp = ra       (save the return address in memory)
    ld $8, r4                 # r4 = temp_i = 8
main_loop:
    beq r4, main_end          # goto main_end if temp_i == 0
    dec r4                    # temp_i--
    ld $x, r0                 # r0 = address of x
    ld (r0,r4,4), r0          # r0 = x[temp_i - 1]
    deca r5                   # sp -= 4
    st r0, (r5)               # *sp = x[temp_i]  (save the first arg on stack)
    gpc $6, r6                # r6 = return address
    j f                       # goto f
    inca r5                   # sp += 4
    ld $y, r1                 # r1 = address of y
    st r0, (r1,r4,4)          # y[temp_i - 1] = temp_k (temp_k is from f)
    br main_loop              # goto main_loop
main_end:
    ld 4(r5), r6              # r6 = *(sp + 4)
    inca r5                   # sp += 4
    inca r5                   # sp += 4 (remove callee part of main's frame)
    j (r6)                    # goto function main which is the start point

.pos 0x2000
x:
    .long 1
    .long 2
    .long 3
    .long 0xffffffff
    .long 0xfffffffe
    .long 0
    .long 184
    .long 340057058

y:
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0

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
