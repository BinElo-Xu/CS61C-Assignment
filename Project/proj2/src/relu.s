.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)

loop_start:
    add s0, a0, zero # s0 -> array
    add s1, a1, zero # s1 -> array size
    li t0, 1 # to -> number of handled elem
    bge s1, t0, loop_continue
    li a0, 78
    j loop_end

loop_continue:
    lw t1, 0(s0)
    add a0, t1, zero
    bgt a0, zero, same
    add a0, zero, zero
    j same

loop_end:
    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    addi sp, sp, 12
	ret

same:
    sw a0, 0(s0)
    addi t0, t0, 1
    addi s0, s0, 4
    bgt t0, s1, loop_end
    j loop_continue
