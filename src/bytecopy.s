.global bytecopy
.code 32
bytecopy:
	ldrb r12,[r1],#1
	strb r12,[r0],#1
	subs r2,r2,#1
	bgt bytecopy
	bx lr
