.pos 0x0
                 ld   $sb, r5               # r5 = &sb (stack bottom)
                 inca r5                    # r5 = goto the bottom of the stack
                 gpc  $6, r6                # r6 = set the return address
                 j    0x300                 # goto 0x300
                 halt                     
.pos 0x100
                 .long 0x00001000           #c (pointer point towards to 0x1000)
.pos 0x200
puu:             ld   (r5), r0              # r0 = a
                 ld   4(r5), r1             # r1 = b
                 ld   $0x100, r2            # r2 = &c
                 ld   (r2), r2              # r2 = c
                 ld   (r2, r1, 4), r3       # r3 = c[b]
                 add  r3, r0                # r0 = c[b] + a
                 st   r0, (r2, r1, 4)       # c[b] = c[b] + a
                 j    (r6)                  # goto return address
.pos 0x300
fn1:             ld   $-12, r0              # r0 = -12
                 add  r0, r5                # allocating three int space in stack
                 st   r6, 8(r5)             # store return address in the stack
                 ld   $1, r0                # r0 = 1 
                 st   r0, (r5)              # store 1 in local a
                 ld   $2, r0                # r0 = 2
                 st   r0, 4(r5)             # store 2 in local b
                 ld   $-8, r0               # r0 = -8
                 add  r0, r5                # r5 move up by two
                 ld   $3, r0                # r0 = 3   
                 st   r0, (r5)              # push 3
                 ld   $4, r0                # r0 = 4
                 st   r0, 4(r5)             # push 4 in the next of the stack
                 gpc  $6, r6                # store the return address in r6
                 j    0x200                 # jump 0x200
                 ld   $8, r0                # r0 = 8
                 add  r0, r5                # clear the stack by two elements
                 ld   (r5), r1              # r1 = a
                 ld   4(r5), r2             # r2 = b
                 ld   $-8, r0               # r0 = -8
                 add  r0, r5                # move r5 up by two elements
                 st   r1, (r5)              # push a
                 st   r2, 4(r5)             # push b into the second element of the stack
                 gpc  $6, r6                # store return address in r6
                 j    0x200                 # jump to 0x200
                 ld   $8, r0                # r0 = 8
                 add  r0, r5                # clear the stack by 2
                 ld   8(r5), r6             # r6 = c
                 ld   $12, r0               # r0 = 12
                 add  r0, r5                # clear the whole stack
                 j    (r6)                  # jump to return address
.pos 0x1000
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
