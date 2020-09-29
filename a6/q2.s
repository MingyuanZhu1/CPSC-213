.pos 0x100
ld $i, r0       # r0 = &i
ld (r0), r0     # r0 = i
ld $n, r1       # r1 = &n
ld (r1), r1     # r1 = n
ld $c, r2       # r2 = &c
ld (r2), r2     # r2 = c

loop_begin:
mov r0, r3      # r3 = i
not r3          # r3 = -i (1/2)
inc r3          # r3 = -i (2/2) two's complement
add r1, r3      # r3 = n + (-i)
bgt r3, loop    # goto loop if r3 > 0
br end          # reached base case

loop:
ld $a, r4               # r4 = &a
ld (r4, r0, 4), r4      # r4 = a[i]
ld $b, r5               # r5 = &b
ld (r5, r0, 4), r5      # r5 = b[i]
not r5                  # r5 = -b[i] (1/2)
inc r5                  # r5 = -b[i] (2/2) two's complement
add r4, r5              # r5 = a[i] + (-b[i])
bgt r5, if              # goto if if r5 > 0
br end_loop             # goto end_loop

if:
inc r2                  # c++

end_loop:
inc r0                  # i++
br loop_begin           # goto loop_begin

end:
ld $i, r1               # r0 = &i
st r0, (r1)             # i = i
ld $c, r3               # r3 = &c
st r2, (r3)             # c = c

halt


.pos 0x1000
 i:  .long 0xffffffff
 n:  .long 5
 c:  .long 0
 a:  .long 10
     .long 20
     .long 30
     .long 40
     .long 50
 b:  .long 11
     .long 20
     .long 28
     .long 44
     .long 48
 

