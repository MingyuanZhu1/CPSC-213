ld $data, r0				#r0 = & array
ld $i, r1				#r1 = & i
ld $x, r2				#r2 = & x
ld $y, r3				#r3 = & y
ld (r1), r4				# r4 = i
ld (r0, r4, 4), r5		# r5 = array[i] 
inc r4 					# r4=  i+1
ld (r0,r4,4), r7			# r7 = array[1+i]
add r5, r7				# r7 = array[i] + array[1+i]
st r7, (r3)				# y = r7
ld $0xff, r6				# r6 = 0xff
and r7, r6				# r6 = y & 0xff
st r6, (r2) 				# x = y & 0xff
halt

.pos 0x1000
i:               .long 0x0         # i
.pos 0x2000
data:             .long 0xffffffff        # b[0]
                 	.long 0xffffffff       # b[1]
                 	.long 0x1        # b[2]
                 	.long 0x1        # b[3]

.pos 0x3000
x:				.long 0x0		# x

.pos 0x4000
y: 				.long 0x0		# y
