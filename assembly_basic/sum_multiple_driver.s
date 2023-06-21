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
