.pos 0x1000
#ct
#Compute the average grade for a single student and store it in the struct. For simplicity, you can ignore the fractional part of the average; i.e., you do not need to round.

#Iterate through the list of students and compute their average grades and store them
                     ld   $n, r0              # r0 = &n
                 	ld   (r0), r0            # r0 = n 
                 	ld   $s, r1              # r1 = &s
                 	ld   (r1), r1            # r1 = s  
			ld   $0, r2              # r2 = counter = 0                 
calc_average:        beq r0, sort        	    # if n = 0 goto end_loop
                 	inc r2                   # r2 = counter++ = 1
                 	ld (r1, r2, 4), r5       # r5 = grade 0 
                 	
			inc r2                   # r2 = counter++
                 	ld (r1, r2, 4), r4       # r4 = grade 1
                 	add r4, r5               # r5 = grade 0 + grade 1

                 	inc r2                   
                 	ld (r1, r2, 4), r4       
                 	add r4, r5 
              
                 	inc r2                   
                 	ld (r1, r2, 4), r4       
                 	add r4, r5 
              
                 	inc r2                   
                 	shr $2, r5               
                 	st r5, (r1, r2, 4)  
     
                 	dec r0                   
                 	inc r2                   
                 	j calc_average          # goto calc_average



# Swap the position of two adjacent students in the list.

swap:            	ld $6, r0                # r0 = 6
                 	mov r5, r7               # r7 = j
                 	dec r7                   # r7 = j-1
                 	shl $3, r7               # r7 = (j-1) x 8
                 	add r6, r7               # r7 = (j-1) x 24
                 	add r1, r7               # r7 = &arr[j-1]
                 	mov r7, r4               # r4 = &arr[j-1]
                 	ld $24, r2               # r2 = 24
                 	add r2, r4               # r4 = &arr[j]

loop_s:       	beq r0, return2          # goto return2 if r0 = 0
                 	ld (r4), r2              # r2 = arr[j]
                 	ld (r7), r6              # r6 = arr[j-1]
                 	st r6, (r4)               
                 	st r2, (r7)              
                 	inca r4                   
                 	inca r7                  # swap
                 	dec r0                   # r0--
                 	j loop_s
              

   
#Sort the list by average grade in ascending order. You are free to use any sort algorithm you like, but Bubble Sort is the simplest. Here’s a version of bubble (sinking) sort in C that you might consider.  
               
sort:          	ld $n, r0                
                 	ld  (r0), r0             # r0 = n 
                 	mov r0, r3               # r3 = n
                 	dec r3                   # r3 = n-1


loop1:      		beq r3, median           
                 	j sort2                 # goto loop2    
          
                 

sort2:          	ld $1, r2                # r2 = 1 = j
                 	mov r2, r5               # r5 = j

loop2:      		mov r3, r6               # r6 = i
                 	not r6                   # negate I
                 	inc r6                   # r3 = - i
                 	add r5, r6               # r3 = j - i 
                 	bgt r6, return1          # if j - i > 0 j
                 	j compare

return1:        	dec r3                   # i--
                 	j loop1

return2:        	inc r5
                 	j loop2            


#Compare the average grades of two adjacent students and swap their position conditionally, using your code from Step 3. 
compare:     		mov r5, r4               # r4 = j 
                 	mov r5, r6               # r6 = j
                 	dec r4                   # r4 = j-1 = 0
                 	dec r6                   # r6 = j-1 = 0
                 	shl $3, r4               # r4 = (j-1) x 8
                 	shl $4, r6               # r6 = x 16
                 	add r6, r4               # r4 = x 24
                 	add r1, r4               # r4 = &arr[j-1]
                 	mov r4, r7               # r7 = &arr[j-1]
                 	ld $24, r0               # r0 = 24 
                 	add r0, r7               # r7 = &arr[j]
                 	ld  20(r4), r4           # r4 = avg of arr[j-1]
                 	ld  20(r7), r7           # r7 = avg of arr[j]
                 	not r4                   
                 	inc r4                   # r4 = - avg of arr[j-1]
                 	add r4, r7               # r7 = avg of arr[j] - avg of arr[j-1]
                 	bgt r7, return2          # goto return2 if r4 > 0
			beq r7, return2          # goto return2 if r4 = 0
                 	
                 	j swap
                 


# Find the median entry in the sorted list and store that student’s sid in m. For simplicity you can assume the list contains an odd number of students.
                                 
median:          	ld $n, r0                # r0 = &n
                 	ld (r0), r0              # r0 = n
                 	shr $1, r0               # r0 = n/2
                 	mov r0, r2               # r2 = n/2
                 	ld $s, r1                # r1 = &s
                 	ld (r1), r1              # r1 = s = &arr[0]
                 	mov r0, r3               # r3 = r0 = n/2
                 	shl $3, r2               # r2 = (n/2) x 8
                 	shl $4, r3               # r3 = x16
                 	add r3, r2               # r2 = x24
                 	add r1, r2               
                 	ld (r2), r4              # r4 = arr[(n/2) x 24] 
                 	ld $m, r5                # r5 = &m
                 	st r4, (r5)              # m = r4 = arr[(n/2) x 24]
                 
                 	halt             


                 
                 

.pos 0x9000                

n:    .long 5 # just one student
m:    .long 0 # student id of the student w/ median grade
s:    .long base # address of the array

base: .long 1234 # student ID
      .long 80 # grade 0
      .long 60 # grade 1
      .long 78 # grade 2
      .long 90 # grade 3
      .long 0 # computed average

	.long 2345
	.long 17
	.long 12
	.long 14
	.long 15
	.long 0

	.long 3456
	.long 25
	.long 30
	.long 33
	.long 27
	.long 0

	.long 4567
	.long 35
	.long 40
	.long 43
	.long 47
	.long 0

	.long 5678
	.long 55
	.long 60
	.long 63
	.long 57
	.long 0


              
                 




