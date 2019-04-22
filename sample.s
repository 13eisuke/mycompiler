# codegen:sample.s

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
	li	$t0, 4
	li	$t1, 2
	add	$v0, $t0, $t1
	sw	$v0, 0($sp)
	la	$t2, _a
	sw	$v0, 0($t2)
	li	$t0, 3
	li	$t1, 1
	sub	$v0, $t0, $t1
	sw	$v0, 0($sp)
	la	$t2, _b
	sw	$v0, 0($t2)
	li	$t0, 2
	li	$t1, 2
	mult	$t0, $t1
	mflo	$v0
	sw	$v0, 0($sp)
	la	$t2, _c
	sw	$v0, 0($t2)
	li	$t0, 4
	li	$t1, 2
	div	$t0, $t1
	mflo	$v0
	sw	$v0, 0($sp)
	la	$t2, _d
	sw	$v0, 0($t2)
	li	$t0, 5
	la	$t2, _b
	lw	$t1, 0($t2)
	nop
	div	$t0, $t1
	mfhi	$v0
	sw	$v0, 0($sp)
	la	$t2, _i
	sw	$v0, 0($t2)
	jr	$ra

.data	0x10004000
_a:	.word	0x0000
_b:	.word	0x0000
_c:	.word	0x0000
_d:	.word	0x0000
_i:	.word	0x0000

# End of file
