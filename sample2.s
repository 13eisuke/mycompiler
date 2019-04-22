# codegen:sample2.s

	INITIAL_GP = 0x10008000
	INITIAL_SP = 0x7ffffffc
	# system call service number
	stop_service = 99
.text
init:
	# initialize $gp (global pointer) and $sp (stack pointer)
	la      $gp, INITIAL_GP
	la      $sp, INITIAL_SP
	jal     main                    # jump to `main'
	nop                             #   (delay slot)
	li      $v0, stop_service       # $v0 <- 99 (stop_service)
	syscall                         # stop
	nop
	# not reach here
stop:
	j stop
	nop

.text	0x00001000

main:
	li	$v0, 1
	la	$t2, _fact
	sw	$v0, 0($t2)
	li	$v0, 1
	la	$t2, _i
	sw	$v0, 0($t2)
L0:
	la	$t2, _i 
	lw	$t0, 0($t2)
	nop
	li	$t1, 6
	slt	$v0, $t0, $t1
	beq	$v0, $zero, L1
	nop
	la	$t2, _fact 
	lw	$t0, 0($t2)
	nop
	la	$t2, _i
	lw	$t1, 0($t2)
	nop
	mult	$t0, $t1
	mflo	$v0
	sw	$v0, 0($sp)
	la	$t2, _fact
	sw	$v0, 0($t2)
	la	$t2, _i 
	lw	$t0, 0($t2)
	nop
	li	$t1, 1
	add	$v0, $t0, $t1
	sw	$v0, 0($sp)
	la	$t2, _i
	sw	$v0, 0($t2)
	j	L0
	nop
L1:
	jr	$ra

.data	0x10004000
_i:	.word	0x0000
_fact:	.word	0x0000

# End of file
