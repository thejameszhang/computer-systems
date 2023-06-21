# Directory ID: jzhang72 
# Name: James Zhang

ae_count:

    # PROLOGUE
    subu $sp, $sp, 8
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    addu $fp, $sp, 8

    # BODY
    move $t0, $a0       # move x into $t0, a general purpose register
    li $v0, 0           # $v0 = 0

    loop:   
        lbu $t1, ($t0)           # set $t1 to the value at address ($t0)
        beq $t1, $zero, endloop # if null, end loop
        bne $t1, 'a', if1       # go to next check if char is not 'a'
        add $v0, $v0, 1         # if it is 'a', $v0 += 1
        j endif

        if1:
            bne $t1, 'e', endif     # if not 'a' or 'e' then end
            add $v0, $v0, 1         # otherwise add $v0 to 1

        endif:
            addu $t0, $t0, 1
            j loop

    endloop:
    # EPILOGUE
    move $sp, $fp
    lw $ra, ($fp)
    lw $fp, -4($sp)
    jr $ra
