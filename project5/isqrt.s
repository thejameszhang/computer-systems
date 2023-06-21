# Name: James Zhang
# UID: 118843940
# Directory ID: jzhang72

isqrt:

    # PROLOGUE
    subu $sp, $sp, 8                # expand stack by 8 bytes
    sw   $ra, 8($sp)                # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)                # push $fp (4 bytes)
    addu $fp, $sp, 8                # set $fp to saved $ra

    # BODY
    
    blt $a0, 2, return_n            # return n if n < 2
    subu $sp, $sp, 4                # store n into stack
    sw $a0, 4($sp)
    
    srl $a0, $a0, 2                 # right shift
    
    jal isqrt
    lw $t3, 4($sp)                  # recover n
    sll $t0, $v0, 1                 # t0 = small
    addu $t1, $t0, 1                # t1 = large

    mul $t2, $t1, $t1               # large * large
    bgt $t2, $t3, return_small
    move $v0, $t1                   # return large
    j end

    return_n:
        move $v0, $a0               # return n
        j end
    
    return_small:
        move $v0, $t0               # return small
    
    end:
        # EPILOGUE
        move $sp, $fp                   # restore $sp
        lw   $ra, ($fp)                 # restore saved $ra
        lw   $fp, -4($sp)               # restore saved $fp
        j    $ra                        # return to kernel