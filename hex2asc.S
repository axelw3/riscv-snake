  # hexmain.S
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
	.globl hex2asc

hex2asc:
	li	a0, 17		# test number (from 0 to 15)
	
	addi    sp,sp,-4
	sw      ra,0(sp)
	
	jal	hexasc		# call hexasc
	
	li	a7, 11	# write a0 to stdout
	ecall

	lw      ra,0(sp)
	addi    sp,sp,4
	jr      ra	

  # You can write your own code for hexasc here
  #
hexasc:
	andi t0,a0,0x0F
	addi t0,t0,-9
	bgtz t0,char
hexasc2:
	addi t0,t0,9
	addi t0,t0,0x30
	add a0,t0,zero
	andi a0,a0,0x7F
	jr ra
char:
	addi t0,t0,7
	j hexasc2
