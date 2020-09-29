ld $t, r0			# r0 = &t 
ld $array, r1 		# r1 = &array
ld (r0), r3			# r3 = t
ld 4(r1),r2			# r2 = array[1]
ld (r1), r6			# r6 = array[0]
st r6, (r0)			# t = r1
st r2, (r1)			# array[0] = array[1]
ld (r0), r7 			# r7 = t
st r7, 4(r1)			# array[1] = t
halt 

.pos 0x1000

t:	.long 0

.pos 0x2000

array:    .long 0x00000001
        	.long 0x00000002