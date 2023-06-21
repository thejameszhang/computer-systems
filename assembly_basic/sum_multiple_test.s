.text

main:
    li      $sp,                0x7ffffffc      # initialize $sp

# PROLOGUE
    subu    $sp,                $sp,        8   # expand stack by 8 bytes
    sw      $ra,                8($sp)          # push $ra (ret addr, 4 bytes)
    sw      $fp,                4($sp)          # push $fp (4 bytes)
    addu    $fp,                $sp,        8   # set $fp to saved $ra

    la      $a0,                array           # pointer to the array address
    lw      $a1,                y               # multiple of y

    jal     sum_multiple

    move    $a0,                $v0             # print_int(a0)
    li      $v0,                1
    syscall 
    li      $v0,                11              # print_char(\n)
    li      $a0,                10
    syscall 

# EPILOGUE
    move    $sp,                $fp             # restore $sp
    lw      $ra,                ($fp)           # restore saved $ra
    lw      $fp,                -4($sp)         # restore saved $fp
    j       $ra                                 # return to kernel
# Directory ID: jzhang72 
# Name: James Zhang

sum_multiple:

    # PROLOGUE
    subu $sp, $sp, 8
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    addu $fp, $sp, 8

    # BODY
    move $t0, $a0       # move x into $t0, a general purpose register
    move $t1, $a1       # move y into $t1, a general purpose register
    li $v0, 0           # $v0 = 0

    loop:
        lw $t2, ($t0)       # load the value of $t0 into $t2
        beqz $t2, endloop   # if 0, then end the loop

        rem $t3, $t2, $t1   # $t3 = $t2 % y
        bnez $t3, endif     # if $t3 is NOT a multiple of y, then jump to endif
        add $v0, $v0, t2$   # if it is a multiple, then add to result $v0
        endif:
            addu $t0, $t0, 4    # increment $t0 to the next element in array
            j loop              # go through the loop again

    endloop:
    # EPILOGUE
    move $sp, $fp
    lw $ra, ($fp)
    lw $fp, -4($sp)
    jr $ra