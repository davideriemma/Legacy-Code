/*
 * write.asm
 *
 *  Created: 29/04/2018 06:50:49
 *   Author: david
 */ 
 ;routine per la scrittura dei dati "Write TO Motorola"

 ;VERSIONE 1.0, PARAMETRI: IL DATO DA SCRIVERE NEL MOTOROLA

 .nolist
 .include "..\mc68008pinDef.inc"
 .list

	;salva i registri che dovrà usare
	push r17
	;imposta le linee dati come output
	ser r17
	out data_ddr, r17
	;ottiene il dato dallo stack
	in YL,SPL
	in YH,SPH

	ldd	r17, Y + 4
	;aspetta che il dato sulle linee sia valido
wait:
	sbic data_control_pin, _DS_
	rjmp wait
	;invia il dato
	out data_port,r17
	;conferma il dato
	cbi data_control_port, _DTACK_
wait_2:
	;aspetta che il dato sia stato ricevuto (aspetta che AS diventi high)
	sbic data_control_pin, _AS_
	rjmp wait_2
	;rimuove il dato dal bus
	clr r17
	out data_port, r17
	;nega dtack
	sbi data_control_port, _DTACK_
	;la scrittura del dato è ultimata
	;ripristino dei registri
	pop r17
	ret

