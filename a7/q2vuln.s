.pos 0x1000
start:
  ld $stacktop, r5
  gpc $6, r6
  j main
  halt

main:
  deca r5             # allocate space for stack
  st r6, (r5)         # set return address
  ld $-128, r0        # r0 = -128
  add r0, r5          # allocate space for stack
  deca r5             # allocate space for stack  
  ld $str1, r0        # r0 = &str1
  st r0, (r5)         # push to stack top
  gpc $6, r6          # jump to print
  j print             # jump to print
  inca r5             # deallocate stack
  
  ld $0, r0           # r0 = 0 (standard in)
  mov r5, r1          # r1 = buffer
  ld $256, r2         # r2 = size
  sys $0              # read
  mov r0, r4          # r4 = r0
  deca r5             # allocate space for r5

  ld $str2, r0        # r0 = &str2
  st r0, (r5)         # r5 = str2
  gpc $6, r6          # jump to print
  j print             # jump to print
  inca r5             # deallocate stack
  ld $1, r0           # r0 = 1
  mov r5, r1          # r1 = r5
  mov r4, r2          # r2 = r4
  sys $1              # write
  ld $128, r0         # r0 = 128
  add r0, r5          # deallocate space for stack
  ld (r5), r6         # r6 = str2
  inca r5             # deallocate stack
  j (r6)              # return r6

print:
  ld (r5), r0         # r0 = &str
  ld 4(r0), r1        # r1 = string
  ld (r0), r2         # r2 = length
  ld $1, r0           # r0 = 1 (standard out)
  sys $1              # write 
  j (r6)              # return

.pos 0x1800
proof:
  deca r5             # allocate space for stack
  ld $str3, r0        # r0 = & str3
  st r0, (r5)         # store return val to r5
  gpc $6, r6          # jump to print
  j print             # jump to print
  halt

.pos 0x2000
str1:
  .long 30
  .long _str1
_str1:
  .long 0x57656c63
  .long 0x6f6d6521
  .long 0x20506c65
  .long 0x61736520
  .long 0x656e7465
  .long 0x72206120
  .long 0x6e616d65
  .long 0x3a0a0000

str2:
  .long 11
  .long _str2
_str2:
  .long 0x476f6f64
  .long 0x206c7563
  .long 0x6b2c2000

str3:
  .long 43
  .long _str3
_str3:
  .long 0x54686520
  .long 0x73656372
  .long 0x65742070
  .long 0x68726173
  .long 0x65206973
  .long 0x20227371
  .long 0x7565616d
  .long 0x69736820
  .long 0x6f737369
  .long 0x66726167
  .long 0x65220a00

.pos 0x4000
stack:
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
stacktop:
  .long 0
