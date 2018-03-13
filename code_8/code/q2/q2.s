.pos 0x0
                 ld   $0x1028, r5					# r5 = sp = 0x1028
                 ld   $0xfffffff4, r0				# r0 = -12	
                 add  r0, r5						# sp = 0x101c
                 ld   $0x200, r0					# r0 = 0x200
                 ld   0x0(r0), r0					# r0 = 0
                 st   r0, 0x0(r5)					# *sp = 0 (save the first argument)
                 ld   $0x204, r0					# r0 = 0x204
                 ld   0x0(r0), r0					# r0 = 0
                 st   r0, 0x4(r5)					# *(sp + 4) = 0 (save the second argument)
                 ld   $0x208, r0					# r0 = 0x208
                 ld   0x0(r0), r0					# r0 = 0
                 st   r0, 0x8(r5)					# *(sp + 8) = 0 (save the third argument)
                 gpc  $6, r6						# r6 = ra = pc + 6 (save the return address)
                 j    0x300							# goto 0x300
                 ld   $0x20c, r1					# sp = 0x20c
                 st   r0, 0x0(r1)					# *sp = return value
                 halt                     
.pos 0x200
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
.pos 0x300
                 ld   0x0(r5), r0					# r0 = a1 = first argument
                 ld   0x4(r5), r1					# r1 = a2 = second argument
                 ld   0x8(r5), r2					# r2 = a3 = third argument
                 ld   $0xfffffff6, r3				# r3 = -10
                 add  r3, r0						# r0 = a1 - 10
                 mov  r0, r3						# r3 = a1 - 10
                 not  r3							# negate r3
                 inc  r3							# r3 = 10 - a1
                 bgt  r3, L6						# goto L6 if a1 < 10
                 mov  r0, r3						# r3 = a1 - 10
                 ld   $0xfffffff8, r4				# r4 = -8
                 add  r4, r3						# r3 = a1 - 18
                 bgt  r3, L6						# goto L6 if a1 > 18
                 ld   $0x400, r3					# r3 = 0x400
                 j    *(r3, r0, 4)					# goto *(0x400 + (a1 - 10) * 4)
.pos 0x330
				 # come here if a1 = 10
                 add  r1, r2						# r2 = a3 + a2
				 br   L7							# goto L7
				 
				 # come here if a1 = 12          
                 not  r2							# negate a3
                 inc  r2							# r2 = -a3
                 add  r1, r2						# r2 = a2 - a3
                 br   L7							# goto L7
				 
				 # come here if a1 = 14
                 not  r2							# negate a3
                 inc  r2							# r2 = -a3
                 add  r1, r2						# r2 = a2 - a3
                 bgt  r2, L0						# goto L0 if a2 > a3
                 ld   $0x0, r2						# r2 = i = 0
                 br   L1							# goto L1
L0:              ld   $0x1, r2						# r2 = i = 1
L1:              br   L7							# goto L7

				 # come here if a1 = 16
                 not  r1							# negate a2
                 inc  r1							# r1 = -a2
                 add  r2, r1						# r1 = a3 - a2
                 bgt  r1, L2						# goto L2 if a3 > a2
                 ld   $0x0, r2						# r2 = i = 0
                 br   L3							# goto L3
L2:              ld   $0x1, r2						# r2 = i = 1
L3:              br   L7							# goto L7

				 # come here if a1 = 18
                 not  r2							# negate a3
                 inc  r2							# r2 = -a3
                 add  r1, r2						# r2 = a2 - a3
                 beq  r2, L4						# goto L4 if a2 == a3
                 ld   $0x0, r2						# r2 = i = 0
                 br   L5							# goto L5
L4:              ld   $0x1, r2						# r2 = i = 1
L5:              br   L7							# goto L7
				
				 # come here if a1 = 11, 13, 15, 17 or a1 < 10 or a1 > 18
L6:              ld   $0x0, r2						# r2 = i = 0
                 br   L7							# goto L7
L7:              mov  r2, r0						# r0 = i
                 j    0x0(r6)						# goto ra
.pos 0x400
                 .long 0x00000330         
                 .long 0x00000384         
                 .long 0x00000334         
                 .long 0x00000384         
                 .long 0x0000033c         
                 .long 0x00000384         
                 .long 0x00000354         
                 .long 0x00000384         
                 .long 0x0000036c         
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
