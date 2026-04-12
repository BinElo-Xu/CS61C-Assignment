.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:
    # Prologue
    addi sp, sp, -12
    sw ra, 8(sp)
    sw s0, 4(sp)
    sw s1, 0(sp)

loop_start:
    add s0, a0, zero # s0 -> array
    add s1, a1, zero # s1 -> array length
    li t0, 1 # int t0 = 1
    li t1, -1 # max value
    li t2, 0 # tmp value
    li t3, 0 # ans value
    li t4, 1 # always 1
    bge s1, t0, loop_continue
    addi t3, zero, 77
    j loop_end

loop_continue:
    lw t2, 0(s0)
    sub a0, t0, t4
    bgt t2, t1, update_index
    addi t0, t0, 1
    addi s0, s0, 4
    bgt t0, s1, loop_end
    j loop_continue

loop_end:
    # Epilogue
    lw s1, 0(sp)
    lw s0, 4(sp)
    lw ra, 8(sp)
    addi sp, sp, 12
    mv a0, t3
    ret

update_index:
    mv t3, a0
    mv t1, t2
    addi t0, t0, 1
    addi s0, s0, 4
    bgt t0, s1, loop_end
    j loop_continue
    