# Name: James Zhang
# UID: 118843940
# Directory ID: jzhang72

collatz:

    # PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

    # BODY
    lw $t0, 12($sp)          # $t0 = n
    lw $t1, 16($sp)          # $t1 = d
    bne $t0, 1, rec          # if $t0 != 1, go to rec
    move $v0, $t1            # otherwise $v0 = d = $t1
    j ret

rec:

    rem $t2, $t0, 2         # $t2 = n % 2
    beqz $t2, even_case     # if (n % 2), jump to even_case

    mul $t3, $t0, 3         # 3 * n
    add $t3, $t3, 1         # 3 * n + 1
    j call
    
    even_case:
        div $t3, $t0, 2     # n / 2
    
    call:
        add $t4, $t1, 1         # d + 1 regardless of which case 
        subu $sp, $sp, 8        # store n and d on the stack
        sw $t4, 8($sp)          
        sw $t3, 4($sp)
        
        jal collatz

ret:
    # EPILOGUE
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra                # return to kernel

