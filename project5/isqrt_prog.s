   .data

# array terminated by 0 (which is not part of the array)
xarr:
   .word 1
   .word 12
   .word 225
   .word 169
   .word 16
   .word 25
   .word 100
   .word 81
   .word 99
   .word 121
   .word 144
   .word 0 

   .text

# main(): ##################################################
#   uint* j = xarr
#   while (*j != 0):
#     printf(" %d\n", isqrt(*j))
#     j++
#
main:
   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   subu $sp, $sp, 8        # save s0, s1 on stack before using them
   sw   $s0, 8($sp)        # push $s0
   sw   $s1, 4($sp)        # push $s1

   la   $s0, xarr          # use s0 for j. init to xarr
main_while:
   lw   $s1, ($s0)         # use s1 for *j
   beqz $s1, main_end      # if *j == 0 go to main_end
   move $a0, $s1           # result (in v0) = isqrt(*j)
   jal  isqrt              # 
   move $a0, $v0           # print_int(result)
   li   $v0, 1
   syscall
   li   $a0, 10            # print_char('\n')
   li   $v0, 11
   syscall
   addu $s0, $s0, 4        # j++
   b    main_while
main_end:
   lw   $s0, -8($fp)       # restore s0
   lw   $s1, -12($fp)      # restore s1

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
# end main #################################################
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