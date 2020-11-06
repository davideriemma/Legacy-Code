;
; EEPROM_rw_studium.asm
;
; Created: 10/04/2018 18:52:41
; Author : david
;
;il programma scrive 24 (0x18) all'indirizzo 0x000 della eeprom, poi lo legge e lo mette nella memoria dati

.cseg
.org 0x0000

;non devo settare nulla in EECR di EEPMx perchè voglio una scrittura pulita del dato

ldi r17, 0x0
ldi r18, 0x00
ldi r19, data

;immetto gli indirizzi
out EEARL, r17
out EEARH, r18

;immetto il dato
out EEDR, r19

;il modo di scrittura è già stato immesso
;scrivo dunque il dato nella EEPROM

sbi EECR, EEMPE
sbi EECR, EEPE

wait:
	
	sbic EECR, EEPE	;dalla documentazione di codice, esce fuori che EEPE viene pulito dopo la fine della scrittura, quindi aspettiamo
	rjmp wait

;Adesso leggo il dato

sbi EECR, EERE
in result_reg, EEDR

;e lo stipo in memoria

sts result, result_reg

.dseg
result: .byte 1	;spazio in memoria dove immagazzinare il risultato

.def result_reg = r16
.equ data = 0x18
