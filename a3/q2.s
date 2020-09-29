.pos 0x100
ld $a, r0		# r0 = &a
ld $s, r1		# r1 = &s
ld $tos, r2		# r2 = &tos
ld $tmp, r3		# r3 = &tmp
ld $0x0, r7		# r7 = 0
st r7, (r2)		# tos = 0
st r7, (r3)		# tmp = 0
ld (r2), r5		# r5 = tos

ld $0x0, r4		# r4 = 0
ld (r0, r4, 4), r4	# r4 = a[0]
st r4, (r1, r5, 4)	# s[tos] = a[0]

inc r5			# tos++
st r5, (r2)		# tos++

ld $0x1, r4		# r4 = 1
ld (r0,r4,4), r4	# r4 = a[1]
st r4, (r1, r5, 4)	# s[tos] = a[1]

inc r5			# tos++
st r5, (r2)		# tos++

ld $0x2, r4		# r4 = 2
ld (r0, r4,4), r4	# r4 = a[2]
st r4, (r1, r5, 4)	# s[tos] = a[2]

inc r5			# tos++
st r5, (r2)		# tos++

dec r5			# tos--
st r5, (r2)		# tos--

ld (r1, r5, 4), r6	# r6 = s[tos]
st r6, (r3)		# tmp = s[tos]

dec r5			# tos--
st r5, (r2)		# tos--

ld (r3), r7		# r7 = tmp
ld (r1, r5, 4), r6	# r6 = s[tos]
add r6, r7		# r7 = tmp + s[tos]
st r7, (r3)		# tmp = tmp + s[tos]

dec r5			# tos--
st r5, (r2)		# tos--

ld (r3), r7		# r7 = tmp
ld (r1, r5, 4), r6	# r6 = 	s[tos]
add r6, r7		# r7 = tmp + s[tos]
st r7, (r3)		#tmp = tmp + s[tos]
halt

.pos 0x1000
tos:               .long 0x0         # tos
.pos 0x2000
a:            		.long 0x1        # a[0]
                 	.long 0x2      	 # a[1]
                 	.long 0x3        # a[2]
.pos 0x4000
s:            		.long 0x1        # s[0]
                 	.long 0x2      	 # s[1]
                 	.long 0x3        # s[2]
                 	.long 0x4        # s[3]
                 	.long 0x3        # s[4]


                 	
.pos 0x3000
tmp:				.long 0x0		# tmp


