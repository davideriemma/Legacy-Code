
	.org 0x000
	rjmp reset

reset:
	clr r16
	sbr r16, 0
	sts 0x53,r16
	sleep

