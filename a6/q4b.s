.pos 0x100
start:
    ld $sb, r5              # initialize stack pointer
    inca    r5              # move the pointer to the bottom of stack
    gpc $6, r6              # set the return address
    j main                  # goto main
    halt                    # halt

f:
    deca r5                 # allocate stack
    ld $0, r0               # r0 = j = 0
    ld 4(r5), r1            # r1 = i = 0
    ld $0x80000000, r2      # r2 = 0x80000000
f_loop:
    beq r1, f_end           # if i == 0 goto f_end
    mov r1, r3              # r3 = r1   
    and r2, r3              # r3 = 0x80000000 & i
    beq r3, f_if1           # if r3 == 0 goto f_if1
    inc r0                  # j++
f_if1:
    shl $1, r1              # i = i * 2
    br f_loop               # goto f_loop
f_end:
    inca r5                 # deallocate stack
    j(r6)                   # return 

main:
    deca r5                 # allocate stack 
    deca r5                 # allocate stack 
    st r6, 4(r5)            # store return address
    ld $8, r4               # r4 = i = 8
main_loop:                  
    beq r4, main_end        # if i == 0 goto main_end
    dec r4                  # i--
    ld $x, r0               # r0 = &x
    ld (r0,r4,4), r0        # r0 = x[i]
    deca r5                 # allocate stack
    st r0, (r5)             # store x[i] into top of stack
    gpc $6, r6              # set return address
    j f                     # jump to f
    inca r5                 # deallocate stack
    ld $y, r1               # r1 = &y
    st r0, (r1,r4,4)        # store x[i] into f(x[i])
    br main_loop            # goto main_loop
main_end:
    ld 4(r5), r6            # update the return address
    inca r5                 # deallocate stack
    inca r5                 # deallocate stack
    j (r6)                  # return

.pos 0x2000
x:
    .long 1
    .long 2
    .long 3
    .long -1
    .long -2
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

