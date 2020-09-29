.pos 0x100
ld $i, r0		# r0 = &i
ld $j, r1		# r1 = &j
ld $p, r2		# r2 = &p
ld $a, r3		# r3 = &a 
ld 12(r3), r4		# r4 = a[3]
st r4, (r0)		# i = a[3]
ld (r3, r4, 4), r5	# r5 = a[i]
st r5, (r0)		# i = a[i]
st r1, (r2)		# p = &j
ld $0x4, r6		# r6 = 4
st r6, (r1)		# *p = 4
ld 8(r3), r6		# r6 = a[2]
shl $2, r6		# r6 = a[2] * 4
add r3, r6		# r3 = &a[a[2]]
st r6, (r2)		# p  = &a[a[2]]
ld 16(r3), r6		# r6 = a[4]
ld (r2), r7		# r7 = p
ld (r7), r0		# r8 = *p
add r0, r6		# r6 = *p + a[4]
st r6, (r7)		# *p = *p + a[4]
halt

.pos 0x1000
i:               .long 0x0         # i
.pos 0x2000
a:            		.long 0xffffffff        # a[0]
                 	.long 0xffffffff       # a[1]
                 	.long 0x1        	# a[2]
                 	.long 0x1        	# a[3]
                 	.long 0x1        # a[3]
                 	.long 0x1        # a[3]
                 	.long 0x1        # a[3]
                 	.long 0x1        # a[3]
                 	.long 0x1        # a[3]
                 	.long 0x1        # a[3]
                 	.long 0x1        # a[3]
.pos 0x3000
j:				.long 0x0		# j

.pos 0x4000
p: 				.long 0x0		# p
