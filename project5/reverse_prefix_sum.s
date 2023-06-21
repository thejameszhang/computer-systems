# Name: James Zhang
# UID: 118843940
# Directory ID: jzhang72

reverse_prefix_sum:

    # PROLOGUE
    subu $sp, $sp, 8            # expand stack by 8 bytes
    sw   $ra, 8($sp)            # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)            # push $fp (4 bytes)
    addu $fp, $sp, 8            # set $fp to saved $ra

    # BODY

    subu $sp, $sp, 4            # make room for r

    lw $t0, ($a0)               # *arr
    bne $t0, -1, rec            # *arr != -1, recursive
    li $v0, 0                   # return 0
    j ret

    rec:
        subu $sp, $sp, 4            # store array index address on stack
        sw $a0, 4($sp)
        addu $a0, $a0, 4            # get next integer
        jal reverse_prefix_sum      # $v0 = reverse_prefix_sum(arr+1)
        
        lw $a0, 4($sp)              # t1 = array index address
        lw $t1, ($a0)               # *arr
        addu $t1, $t1, $v0          # r = reverse_prefix_sum(arr+1) + *arr

        sw $t1, 8($sp)              # store r onto the stack
        sw $t1, ($a0)               # store r into array
        move $v0, $t1               # return r

    ret:
        # EPILOGUE
        move $sp, $fp               # restore $sp
        lw   $ra, ($fp)             # restore saved $ra
        lw   $fp, -4($sp)           # restore saved $fp
        j    $ra                    # return to kernel