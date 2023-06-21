# Name: James Zhang
# UID: 118843940
# Directory ID: jzhang72

is_palindrome:

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   # BODY
   jal strlen              # call strlen, note string is in $a0 already
   li $t0, 0               # i = $t0
   move $t1, $v0           # len = $t1
   div $t2, $t1, 2         # len / 2 = $t2

   loop:
      bge $t0, $t2, return_one      # check for loop condition

      addu $t3, $t0, $a0            # i
      lbu $t3, ($t3)                # string[i] = $t3

      addu $t4, $a0, $t1            # len
      subu $t4, $t4, $t0            # len - i
      subu $t4, $t4, 1              # len - i - 1
      lbu $t4, ($t4)                # string[len - i - 1] = $t4

      bne $t3, $t4, return_zero
      add $t0, $t0, 1
      j loop
   
   return_one:
      li $v0, 1                     # return 1
      j return

   return_zero:
      li $v0, 0                     # return 0

   # EPILOGUE
   return:
      move $sp, $fp           # restore $sp
      lw   $ra, ($fp)         # restore saved $ra
      lw   $fp, -4($sp)       # restore saved $fp
      j    $ra                # return to kernel

strlen: 
   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   li $t0, 0               # length = 0
   li $t1, 0               # i = 0
   strlen_loop:   
      addu $t2, $a0, $t1               # i 
      lbu $t2, ($t2)                   # string[i]
      beq $t2, $zero, strlen_endloop
      add $t1, $t1, 1
      addu $t0, $t0, 1
      j strlen_loop
   
   strlen_endloop:
      move $v0, $t0
      # EPILOGUE
      move $sp, $fp           # restore $sp
      lw   $ra, ($fp)         # restore saved $ra
      lw   $fp, -4($sp)       # restore saved $fp
      j    $ra                # return to kernel
   