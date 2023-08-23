;; (2) When calculating 2 x 3 + 4 x 5. (RAM0 x RAM1 + RAM0 x RAM1 = RAM2)
;;     (sample 2b is an optimized version of 2a.)

; ------- sample (2b) start -------

RAM0_ADR        = $00   ; 2, 4 Start of storage address
RAM1_ADR        = $00   ; 3, 5 storage address start
RAM2_ADR        = $00   ; Result storage address

	                                                 MOV RAM0_ADR,CT0
	                                                 MOV RAM1_ADR,CT1
	MVI #2,MC0
	MVI #3,MC1
	MVI #4,MC0
	MVI #5,MC1
	                                                 MOV RAM0_ADR,CT0
	                                                 MOV RAM1_ADR,CT1
	     MOV MC0,X             MOV MC1,Y             MOV RAM2_ADR,CT2
	     MOV MC0,X  MOV MUL,P  MOV MC1,Y  CLR A
	AD2             MOV MUL,P             MOV ALU,A
	AD2                                              MOV ALL,MC2
	ENDI

; ------- sample (2b) end -------
