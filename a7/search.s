.pos 0x100
start:	
        ld   $sb, r5		# r5 = &stack bottom
        inca r5				# deallocate space for stack	
        gpc  $6, r6         # set return address
        j    main			# jump to main
        halt

.pos 0x200
main:	
	deca r5					# allocate space for stack
	st   r6, (r5)			# set return address
	ld   $-12, r1			# r1 = -12
	add  r1, r5				# allocate 3 int space for stack
	ld   $a, r0				# r0 = &a
	st   r0, 0x0(r5)		# store &a into stack[0]
	ld   $val, r0			# r0 = &val
	ld   (r0), r0			# r0 = val
	st   r0, 0x4(r5)		# store val into stack[1]
	ld   $size, r0			# r0 = &size
	ld   (r0), r0			# r0 = size
	st   r0, 0x8(r5)		# store size into stack[2]
	gpc  $6, r6				# get return address
	j    search				# jump to search
	ld   $12, r1			# r1 = 12
	add  r1, r5				# deallocate space for stack
	ld   $ret, r1			# r1 = &ret
	st   r0, (r1)			# return = result
	ld   (r5), r6			# load return address
	inca r5					# deallocate space in stack
	j    (r6)				# return
	
.pos 0x300
search:	
	ld   0x8(r5), r0		# r0 = size
	beq  r0, L3				# r0 == 0 goto L3
	ld   0x0(r5), r1		# r1 = a
	ld   0x4(r5), r2		# r2 = array address
	mov  r0, r3				# r3 = size
	shr  $1, r3				# r3 = size / 2
	mov  r3, r4				# r4 = size / 2 
	shl  $2, r4				# r4 = 2 * size 
	add  r1, r4				# r4 = mid address
	ld   (r4), r7			# r7 = mid value
	not  r7
	inc  r7					# -mid value
	add  r2, r7				# r7 = 
	beq  r7, L2				# if r7 == 0, goto L2
	bgt  r7, L0				# if r7 > 0, goto L0
	br   L1					# goto L1
L0:
	mov  r4, r1				# r1 = mid address
	inca r1					# r1 = mid address + 1
	not  r3					# 
	add  r0, r3				
L1:
	st   r1, 0x0(r5)		# array
	st   r2, 0x4(r5)		# value
	st   r3, 0x8(r5)		# size / 2			
	j    search				# jump to search
L2:
	mov  r4, r0				# move return value into r0
L3:
	j    (r6)

.pos 0x1000
a:	.long 0x1
        .long 0x3         
        .long 0x4
	.long 0x7         
	.long 0x9         
        .long 0xA         
        .long 0xC         
	.long 0x10         
	.long 0x12         
        .long 0x13
	.long 0x14
	.long 0x17
	.long 0x1A
	.long 0x1B
	.long 0x1F

.pos 0x2000
size:	.long 15
val:	.long 0x12
ret:	.long 0xFFFFFFFF
	
.pos 0x8000
stack:	
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
sb: 	.long 0
