   .data

strbuf:
   .space 80

   .text
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   li   $v0, 8             # read string into strbuf
   la   $a0, strbuf        # and nul-terminate it
   li   $a1, 80            # assumes input (including \n)
   syscall                 # is less than 80 chars

   jal  ae_count

   move $a0, $v0           # print_int(a0)
   li   $v0, 1
   syscall
   li   $v0, 11            # print_char(\n)
   li   $a0, 10
   syscall

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
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
    li $t2, '\n'        # $t2 = '\n'
    li $t3, 'a'         # $t3 = 'a'
    li $t4, 'e'         # $t4 = 'e'

    loop:   
        lw $t1, ($t0)           # set $t1 to the value at address ($t0)
        beq $t1, $t2, endloop  # if new line character, end loop
        bne $t1, $t3, if1       # go to next check if char is not 'a'
        add $v0, $v0, 1         # if it is 'a', $v0 += 1
        j endif

        if1:
            bne $t1, $t4, endif     # if not 'a' or 'e' then end
            add $v0, $v0, 1         # otherwise add $v0 to 1

        endif:
            addu $t0, $t0, 4
            j loop

    endloop:
    # EPILOGUE
    move $sp, $fp
    lw $ra, ($fp)
    lw $fp, -4($sp)
    jr $ra
