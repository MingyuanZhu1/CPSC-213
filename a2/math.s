ld $a, r0		# r0 = &a
ld $b, r1		# r1 = &b
ld (r1), r2		# r2 = b
ld (r0), r3		# r3 = a
inc r2			# r2 = b+1
ld $0x4, r4		# r4 = 4
add r4, r2		# r2 = (b+1)+4
shr $0x1, r2 	# r2 = (b+1)+4 / 2	
ld (r1), r5		# r5 = b
and r2, r5		# r5 = (((b+1)+4) / 2) & b
shl $0x2	, r5 	# r5 = (((b+1)+4) / 2) & b << 2
st r5, (r0)		# a = r5
halt


.pos 0x1000
a: .long 0x3
b: .long 0x5