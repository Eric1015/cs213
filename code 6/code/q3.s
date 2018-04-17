.pos 0x100
                  # iterate through all the students
                  ld   $s, r1               # r1 = address of s
                  ld   $n, r0               # r0 = address of n
                  ld   (r0), r0             # r0 = n
                  not  r0                   # r0 = ~n
                  inc  r0                   # r0 = -n
                  ld   $0x0, r4             # r4 = temp_i = 0
students_loop:    mov  r4, r5               # r5 = temp_i
                  add  r0, r5               # r5 = temp_i - n
                  beq  r5, end_students_loop  # goto end_students_loop if temp_i == n
                  ld   (r1, r4, 4), r7      # r7 = address of student[temp_i]
                  br   average              # goto average
end_students_loop: br  compare_average      # goto compare_average

                  # compute the average of a student
average:          ld   $0x0, r2             # r2 = temp_ave = 0
                  ld   $0x0, r3             # r3 = temp_j = 0
average_loop:     ld   $-4, r6              # r6 = -4
                  mov  r3, r5               # r5 = temp_j
                  add  r6, r5               # r5 = temp_j - 4
                  beq  r5, end_average_loop # goto end_average_loop if temp_j == 4
                  inc  r3                   # temp_j++
                  ld   (r7, r3, 4), r6      # r6 = grade[temp_j]
                  add  r6, r2               # r2 += grade[temp_j]
                  br average_loop           # goto average_loop
end_average_loop: shr $2, r2                # r2 = temp_ave / 4
                  st  r2, 20(r7)            # average = temp_ave / 4
                  inc r4                    # temp_i++
                  br  students_loop         # goto students_loop

                  # swap function
swap:             mov r2, r3                # r3 = base address of s
                  mov r0, r1                # r1 = temp_i
                  ld  (r2, r0, 4), r3       # r3 = &student[temp_i]
                  dec r1                    # r1 = temp_i - 1
                  ld  (r2, r1, 4), r4       # r4 = &student[temp_i - 1]
                  ld  $0, r1                # r1 = temp_k = 0
                  ld  (r3, r1, 4), r6       # r6 = student[temp_i].sid
                  ld  (r4, r1, 4), r7       # r7 = student[temp_i - 1].sid
                  st  r7, (r3, r1, 4)       # student[temp_i].sid = student[temp_i - 1].sid
                  st  r6, (r4, r1, 4)       # student[temp_i - 1].sid = student[temp_i].sid
                  inc r1                    # temp_k++
                  ld  (r3, r1, 4), r6       # r6 = student[temp_i].grade0
                  ld  (r4, r1, 4), r7       # r7 = student[temp_i - 1].grade0
                  st  r7, (r3, r1, 4)       # student[temp_i].grade0 = student[temp_i - 1].grade0
                  st  r6, (r4, r1, 4)       # student[temp_i - 1].grade0 = student[temp_i].grade0
                  inc r1                    # temp_k++
                  ld  (r3, r1, 4), r6       # r6 = student[temp_i].grade1
                  ld  (r4, r1, 4), r7       # r7 = student[temp_i - 1].grade1
                  st  r7, (r3, r1, 4)       # student[temp_i].grade1 = student[temp_i - 1].grade1
                  st  r6, (r4, r1, 4)       # student[temp_i - 1].grade1 = student[temp_i].grade1
                  inc r1                    # temp_k++
                  ld  (r3, r1, 4), r6       # r6 = student[temp_i].grade2
                  ld  (r4, r1, 4), r7       # r7 = student[temp_i - 1].grade2
                  st  r7, (r3, r1, 4)       # student[temp_i].grade2 = student[temp_i - 1].grade2
                  st  r6, (r4, r1, 4)       # student[temp_i - 1].grade2 = student[temp_i].grade2
                  inc r1                    # temp_k++
                  ld  (r3, r1, 4), r6       # r6 = student[temp_i].grade3
                  ld  (r4, r1, 4), r7       # r7 = student[temp_i - 1].grade3
                  st  r7, (r3, r1, 4)       # student[temp_i].grade3 = student[temp_i - 1].grade3
                  st  r6, (r4, r1, 4)       # student[temp_i - 1].grade3 = student[temp_i].grade3
                  inc r1                    # temp_k++
                  ld  (r3, r1, 4), r6       # r6 = student[temp_i].ave
                  ld  (r4, r1, 4), r7       # r7 = student[temp_i - 1].ave
                  st  r7, (r3, r1, 4)       # student[temp_i].ave = student[temp_i - 1].ave
                  st  r6, (r4, r1, 4)       # student[temp_i - 1].ave = student[temp_i].ave
                  br  compare_then          # goto compare_then

                  # bubble sort function
compare_average:  ld  $s, r2                # r2 = address of s
                  ld  $n, r5                # r5 = address of n
                  ld  (r5), r5              # r5 = n
                  dec r5                    # r5 = n - 1
                  beq r5, end_compare_loop_out # goto end_compare_loop_out if n == 1
compare_loop_out: mov r5, r6                # r6 = temp_n - 1
                  inc r6                    # r6 = temp_n
                  beq r6, end_compare_loop_out # goto end_compare_loop_out if temp_n == 0
                  not r6                    # r6 = ~(temp_n)
                  inc r6                    # r6 = -(temp_n)
                  ld  $1, r0                # r0 = temp_i = 1
compare_loop_in:  mov r0, r1                # r1 = temp_i
                  mov r5, r6                # r6 = temp_n - 1
                  inc r6                    # r6 = temp_n
                  not r6                    # r6 = ~(temp_n)
                  inc r6                    # r6 = -(temp_n)
                  add r6, r1                # r1 = temp_i - temp_n
                  beq r1, end_compare_loop_in # goto end_compare_loop_in if temp_i == temp_n
                  ld  (r2, r0, 4), r6       # r6 = address of student[temp_i]
                  dec r0                    # temp_i--
                  ld  (r2, r0, 4), r7       # r7 = address of student[temp_i - 1]
                  ld  20(r6), r6            # r6 = student[temp_i].ave
                  ld  20(r7), r7            # r7 = student[temp_i - 1].ave
                  not r6                    # r6 = ~student[temp_i].ave
                  inc r6                    # r6 = -student[temp_i].ave
                  add r6, r7                # r7 = student[temp_i - 1].ave - student[temp_i].ave
                  inc r0                    # r0 = temp_i
                  bgt r7, swap              # goto swap if student[temp_i].ave > student[temp_i + 1].ave
                  br  compare_then          # goto compare_then
compare_then:     inc r0                    # r0 = temp_i++
                  br  compare_loop_in       # goto compare_loop_in
end_compare_loop_in: dec r5                 # r5 = (temp_n - 1)--
                     br  compare_loop_out   # goto compare_loop_out

end_compare_loop_out: ld  $n, r0            # r0 = address of n
                      ld  (r0), r0          # r0 = n
                      shr $1, r0            # r0 = n / 2
                      ld  $s, r1            # r1 = address of s
                      ld  (r1, r0, 4), r2   # r2 = address of student[n / 2]
                      ld  (r2), r2          # r2 = student[n / 2].sid
                      ld  $m, r3            # r3 = address of m
                      st  r2, (r3)          # m = student[n / 2].sid
                 halt

.pos 0x2000
n:               .long 1                   # 5 students
m:               .long 0                   # median
s:               .long student1            # address of student1
                 .long student2            # address of student2
                 .long student3            # address of student3
                 .long student4            # address of student4
                 .long student5            # address of student5

.pos 0x3000
student1:        .long 1234                # student ID
                 .long 80                  # grade 0
                 .long 100                 # grade 1
                 .long 78                  # grade 2
                 .long 90                  # grade 3
                 .long 0                   # ave
student2:        .long 3456                # student ID
                 .long 50                  # grade 0
                 .long 75                  # grade 1
                 .long 90                  # grade 2
                 .long 65                  # grade 3
                 .long 0                   # ave
student3:        .long 5678                # student ID
                 .long 43                  # grade 0
                 .long 53                  # grade 1
                 .long 61                  # grade 2
                 .long 83                  # grade 3
                 .long 0                   # ave
student4:        .long 7890                # student ID
                 .long 89                  # grade 0
                 .long 91                  # grade 1
                 .long 88                  # grade 2
                 .long 92                  # grade 3
                 .long 0                   # ave
student5:        .long 9012                # student ID
                 .long 63                  # grade 0
                 .long 57                  # grade 1
                 .long 64                  # grade 2
                 .long 96                  # grade 3
                 .long 0                   # ave
