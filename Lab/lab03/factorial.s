.globl factorial

.data
n: .word 7

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi sp, sp, -12
    sw t0, 0(sp)
    sw s0, 4(sp)
    sw ra, 8(sp)
    mv s0, x0
    beq a0, x0, exit
    addi s0, x0, 1
    addi t0, x0, 1
loop:
    mul s0, s0, t0
    beq t0, a0, exit
    addi t0, t0, 1
    j loop
    
exit:
   mv a0, s0
   lw t0, 0(sp)
   lw s0, 4(sp)
   lw ra, 8(sp)
   addi sp, sp, 12
   jr ra
    