.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:

    # Prologue
    addi sp, sp -20
    sw ra, 16(sp)
    sw s0, 12(sp)
    sw s1, 8(sp)
    sw s2, 4(sp)
    sw s3, 0(sp)
    
    # initialize the variables
    add s0, a0, zero # s0 -> array v0
    add s1, a1, zero # s1 -> array v1
    add s2, a2 zero # s2 -> length of array
    add t0, a3, zero # stride of v0
    add t1, a4, zero # stride of v1
    addi t2, zero, 4 # unit of one stride
    addi t3, zero, 1 # the counter
    add t4, zero, zero # the adder
    add t5, zero, zero # the answer
    
    # exception handling
    blt s2, t3, length_exception
    blt t0, t3, stride_exception
    blt t1, t3, stride_exception

loop_start:
    lw t6, 0(s0)
    lw s3, 0(s1)
    mul s3, s3, t6
    add t5, t5, s3
    mv a0, t5 # update return value
    mul t4, t0, t2
    add s0, s0, t4
    mul t4, t1, t2
    add s1, s1, t4
    addi t3, t3, 1
    bgt t3, s2, loop_end
    j loop_start
    
loop_end:

    # Epilogue
    lw s3, 0(sp)
    lw s2, 4(sp)
    lw s1, 8(sp)
    lw s0, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    
    ret

length_exception:
    addi a0, zero, 75
    j loop_end
    
stride_exception:
    addi a0, zero, 76
    j loop_end
