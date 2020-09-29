.pos 0x100
ld $a, r0		# r0 = &a
ld $p, r1		# r1 = &p
ld $b, r2		# r2 = &b
ld $0x3, r3		# r3 = 3
st r3, (r0)		# a = 3
st r0, (r1)		# p = &a
ld (r1), r1		# r1 = p = &a
ld (r1), r4		# r4 = *p = a
dec r4			# r4 = *p - 1 = a - 1 
st r4, (r1)		# *p = *p - 1
ld $p, r1		# r1 = &p
st r2, (r1)		# p = &b[0]
ld (r1), r6		# r6 = p
inca r6			# r6 = r6 + 1
st r6, (r1)		# p++



ld $a, r1		# r1 = &a
ld (r1), r1		# r1 = a
ld $b, r2		# r2 = &b
ld (r2, r1, 4), r4	# r4 = b[a]
ld $p, r3		# r3 = &p
ld (r3), r5		# r5 = p
st r4, (r5, r1, 4)	# p[a] = b[a]
ld (r2), r2		# r2 = b[0]
ld (r3), r0		# r0 = p
ld $3, r6		# r6 = 3
st r2, (r0, r6, 4)	# *(p+3) = b[0]
halt

.pos 0x200
a:		.long 0 	#a
b:		.long 1		#b[0]
		.long 2		#b[1]
		.long 3		#b[2]
		.long 4		#b[3]
		.long 5		#b[4]
p:		.long 2		#p
