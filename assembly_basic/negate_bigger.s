# Directory ID: jzhang72 
# Name: James Zhang

negate_bigger:

    # PROLOGUE
    subu $sp, $sp, 8
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    addu $fp, $sp, 8

    # BODY
    bgt $a0, $a1, else  # if (x > y), jump to else
    mul $v0, $a1, -1    # otherwise negate y and store in $v0
    j endif

    else:
        mul $v0, $a0, -1 # negate x
    
    endif:
    # EPILOGUE
    move $sp, $fp
    lw $ra, ($fp)
    lw $fp, -4($sp)
    jr $ra