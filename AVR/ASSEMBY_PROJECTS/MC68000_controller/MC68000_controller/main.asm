;
; MC68000_controller.asm
;
; Created: 06/05/2018 16:25:06
; Author : david
;

.nolist
.include "..\mc68000pinDef.inc"
.list

;interrupt vector

	.org 0x000
	rjmp reset

	.org 0x006
	rjmp as_routine

;inizio del codice
	.org 0x008

reset:	
	
	;imposta lo stack pointer
	ldi r16, low(RAMEND - 1)
	ldi r17, high(RAMEND - 1)

	out SPL, r16
	out SPH, r17

	;inizializza i registri del bus indirizzi
	;imposta tutti i bit a 0
	clr r16
	;per impostare address_control_ddr come input
	out address_ddr, r16
	;ci si assicura che le resistenze di pull-up non siano attive
	out address_port, r16

	;inizializza i registri del bus controlli
	;il registro r16 è già impostato a 0, quindi imposto come output DTACK
	;e il led di stato
	;			0 1 0 1 0 0 0 0
	ldi r16, (1 << _DTACK_) | (1 << LED)
	out data_control_ddr, r16
	;imposto le resistende di pullup per i pin in imput e alzo DATCK
	;nego r16, così i pin in input avranno le resistenze alzate
	com r16
	;		1 0 1 0 1 1 1 1 
	;tuttavia, siccome DTACK è active low, devo alzarlo, settando a 1 il relativo bit
	;		1 0 1 1 1 1 1 1
	sbr r16, _DTACK_
	;anche PHEN deve essere impostato come input, non come pull-up tuttavia
	;		1 0 0 1 1 1 1 1  
	cbr r16, PHEN
	;e accendo il led: reset iniziato
	;		1 1 0 1 1 1 1 1
	sbr r16, LED
	;e lo metto in data control port: le necessarie resistenze di pullup sono attive e DTACK è high.
	out data_control_port, r16

	;inizializzo l'interrupt per avviare il controller all'attivazione di _AS_
	;imposta l'interrupt triggered su INT2 falling-edge
	;siccome il registro interrupt è condiviso anche con altri flag, si procede così:
	; 1. leggo lo stato corrente del registro
	lds r16, as_interrupt_reg
	;imposto il bit necessario
	cbr r16, as_mode_bit
	;e rimetto tutto in ordine
	sts as_interrupt_reg, r16
	;abilito adesso l'interrupt request, seguendo la stessa procedura
	lds r16, as_interrupt_enable
	sbr r16, as_int_en
	sts as_interrupt_enable, r16

	;imposto la modalità di idle
	clr r16
	ldi r16, (1 << sleep_enable) | (1 << sleep_bit_1)
	out sleep_mode_reg, r16

	;spengo il led di stato per far capire che la prima parte è stata completata
	cbi data_control_port, LED
	;abilito gli interrupt
	sei
	;metto in idle la cpu
	sleep

as_routine:

	;termina gli interrupt
	cli
	;accende il led: interrupt recognised
	sbi data_control_port, LED
	;legge l'indirizzo
	in r16, address_pin
	;lo memorizza nel buffer
	sts GPIOREG, r16

	;fase di decodifica dell'indirizzo
	lds r16, data_control_pin
	andi r16, (1 << PHEN)
if:	tst r16
	;nessuna attività su periferica identificata, skippa all'ese
	breq else
	;call pheripheral_decode
	rjmp continue
else:
	call eeprom_decode
continue:
	;spegne il led: routine terminata
	cbi data_control_port, LED
	;riattiva gli interrupt
	sei
	sleep

;----------------------------------------------routines------------------------------

;routines di eeprom
eeprom_read:	;la routine riceve come prametro l'indirizzo al quale leggere (8 bit) e restituisce al suo posto il dato letto (8 bit)
	
	;salvataggio contesto massimo
	push YL
	push YH
	;ottiene l'indirizzo corrente dello stack pointer, per muoversi così agevolmente (senza tenere conto dei push dei regisrti)
	ldi YL, SPL
	ldi YH, SPH
	;salvataggio dei registri che vado a sporcare
	push r16

	;codice effettivo della routine
	;leggo l'indirizzo passato come argomento
	ldd r16, Y + 5
	;lo imposto nella eeprom
	out EEPROM_address_low_reg, r16
	;avvia la lettura del dato
	sbi EEPROM_control_reg, EEPROM_read_bit
	;legge il dato appena ottenuto dalla eeprom
	in r16, EEPROM_data_reg
	;lo restituisce al posto dell'argomento
	std Y + 5, r16
	;ripristina i registri
	push r16
	push YH
	push YL
	;ritorna
	ret

eeprom_write:	;la routine riceve come parametro l'indirizzo (8 bit) al quale scrivere e  il dato che deve andare a scrivere (8 bit)
	
	;salvataggio contesto massimo
	push YL
	push YH
	;ottiene l'indirizzo corrente dello stack pointer, per muoversi così agevolmente (senza tenere conto dei push dei regisrti)
	ldi YL, SPL
	ldi YH, SPH
	;salvataggio dei registri che vado a sporcare
	push r16
	push r17
	;legge il dato passato
	ldd r17, Y + 5
	;legge l'indirizzo passato
	ldd r16, Y + 6

	;immetto gli indirizzi
	out EEPROM_address_low_reg, r16
	;immetto il dato
	out EEPROM_data_reg, r17
	;scrivo dunque il dato nella EEPROM
	sbi EEPROM_control_reg, EEPROM_write_enable
	sbi EEPROM_control_reg, EEPROM_write_bit

wait_1:
	
	sbic EEPROM_control_reg, EEPROM_write_bit	;dalla documentazione di codice, esce fuori che EEPE viene pulito dopo la fine della scrittura, quindi aspettiamo
	rjmp wait_1
	;terminata l'attesa, passo a terminare la routine

	push r17
	push r16
	push YH
	push YL

	ret

eeprom_decode:

	push r16
	push r17

	;verifica se il dato è in lettura
	lds r16, data_control_pin
	andi r16, (1 << RW_)
if_4: tst r16
	  breq else_3
	  lds r16, data_control_pin
	  andi r16, (1 << _UDS_)
		if_5: tst r16
			breq else_4 ;se i due sono uguali, il risultato non è zero
			;leggi il msb
			lds r17, GPIOREG
			push r17
			call eeprom_read
			pop r17
			rjmp continue_4
		;altrimenti se UDS è high
		else_4:
			;imposta a zero il msb (pulisci r17)
			clr r17
		continue_4:
			;se LDS è low
			lds r16, data_control_pin
			andi r16, (1 << _UDS_)
			if_6: tst r16
				breq continue_5
				;incrementa l'indirizzo
				lds r16,GPIOREG
				inc r16
				;leggi li lsb
				push r16
				call eeprom_read
				pop r16
				rjmp continue_5
			;altrimenti, se LDS è high
			else_5:
				;imposta a zero il lsb (pulisci r16)
				clr r16
			continue_5:
		;passa il lsb
		push r16
		;passa il msb
		push r17
		call write
		pop r17
		pop r16
		rjmp continue_3
;il bit in data_control_pin è 0, indicando una richiesta di write
else_3:
		;incrementa lo stack per riservare spazio per il valore di ritorno
		;chiama la funzione read (from motorola)
		;adesso ho il dato che devo scrivere
		;passa l'indirizzo
		;passa il dato
		;chiama la funzione eeprom_read

continue_3:
	pop r17
	pop r16
	ret

;funzioni di lettura e scrittura (interfacciamento con il motorola)

write:	;la funzione riceve il dato da inviare (16 bit)(MSB, LSB)

	push YL
	push YH
	;ottiene il dato dallo stack
	in YL,SPL
	in YH,SPH
	;salva i registri che dovrà usare
	push r16
	push r17
	push r18

	;imposta le linee dati come output
	ser r17
	out upper_data_ddr, r17
	out lower_data_ddr, r17

	;legge il MSB
	ldd	r17, Y + 5
	;legge il LSB
	ldd r18, Y + 6

	lds r16, data_control_pin
	andi r16, (1 << _UDS_)
if_2:	tst r16
	breq else_2
	;invia il dato su UDS
	out upper_data_port, r17
	rjmp continue_2
else_2:
	lds r16, data_control_pin
	andi r16, (1 << _LDS_)
	if_3:	tst r16
			breq continue_2	;non si richiede l'invio di nessun dato
			;invia il dato su LDS
			out upper_data_port, r18
continue_2:
	;conferma il dato
	cbi data_control_port, _DTACK_
wait_2:
	;aspetta che il dato sia stato ricevuto (aspetta che AS diventi high)
	sbic data_control_pin, _AS_
	rjmp wait_2
	;rimuove il dato dal bus
	clr r17
	out upper_data_port, r17
	out lower_data_port, r17
	;nega dtack
	sbi data_control_port, _DTACK_
	;la scrittura del dato è ultimata
	;ripristino dei registri
	pop r18
	pop r17
	pop r16
	pop YH
	pop YL
	ret
