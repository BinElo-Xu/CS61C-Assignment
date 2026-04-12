.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:

    # Error checks
    add t0, a1, zero #rows of m0
    add t1, a2, zero #columns of m0
    add t2, a4, zero #rows of m1
    add t3, a5, zero #columns of m1
    
    # Prologue
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s0, 8(sp)
    sw s1, 4(sp)
    sw s2, 0(sp)
    
    li t4, 1
    blt t0, t4, exception_m0
    blt t1, t4, exception_m0
    blt t2, t4, exception_m1
    blt t3, t4, exception_m1
    bne t1, t2, dimension_exception
    
    # Initialization
    add s0, zero, a0 # s0 -> m0
    add s1, zero, a3 # s1 -> m1
    add s2, zero, a6 # s2 -> d
    li t6 4 # unit step
    li t4, 0 # int i = 0
    
outer_loop_start:

    bge t4, t0, outer_loop_end
    li t5, 0 # int j = 0
    
inner_loop_start:

    bge t5, t3, inner_loop_end

    mul a0, t4, t1
    mul a0, a0, t6
    add a0, s0, a0 # begining of rows
    
    add a1, t5, zero
    mul a1, a1, t6
    add a1, s1, a1 # begining of cols
    
    add a2, t1, zero
    addi a3, zero, 1
    add a4, zero, t3
    addi sp, sp, -28
    sw t0, 24(sp)
    sw t1, 20(sp)
    sw t2, 16(sp)
    sw t3, 12(sp)
    sw t4, 8(sp)
    sw t5, 4(sp)
    sw t6, 0(sp)
    call dot
    lw t0, 24(sp)
    lw t1, 20(sp)
    lw t2, 16(sp)
    lw t3, 12(sp)
    lw t4, 8(sp)
    lw t5, 4(sp)
    lw t6, 0(sp)
    addi sp, sp, 28
    sw a0, 0(s2)
    addi s2, s2, 4
    addi t5, t5, 1
    j inner_loop_start

inner_loop_end:
    addi t4, t4, 1
    j outer_loop_start

outer_loop_end:

    # Epilogue
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw s0, 8(sp)
    lw ra, 12(sp)
    addi sp, sp, 16
    ret

exception_m0:
    addi a0, zero, 72
    j outer_loop_end
    
exception_m1:
    addi a0, zero, 73
    j outer_loop_end

dimension_exception:
    addi a0, zero, 74
    j outer_loop_end
