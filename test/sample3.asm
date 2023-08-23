;; (3) When calculating movement processing for a matrix. (RAM0×RAM1=RAM2)

;;        ┌                 ┐ ┌         ┐   ┌                 ┐
;;        │ M00 M01 M02 M03 │ │ 1 0 0 x │   │ M00 M01 M02 M03 │
;;        │ M10 M11 M12 M13 │ │ 0 1 0 y │ → │ M10 M11 M12 M13 │
;;        │ M20 M21 M22 M23 │ │ 0 0 1 z │   │ M20 M21 M22 M23 │
;;        └                 ┘ │ 0 0 0 1 │   └                 ┘
;;                            └         ┘

; ------- sample (3) start -------

DATA_TOP	= $10000 >> 2	; External memory addresses are in units of 4 bytes
MAT_SIZE	= $0C		; array size
RAM0_ADR	= $00		; Start address to store X, Y, Z movement amount
RAM1_ADR	= $00		; Work address for array
RAM2_ADR	= $00		; Address of original array

; (Transfer array with movement amount set from external memory to RAM0)
;
	MVI DATA_TOP,RA0
	                                                 MOV RAM0_ADR,CT0
	DMA D0,MC0,#$02
;
; (Copy of array to be operated from RAM2 to RAM1)
	                                                 MOV RAM2_ADR,CT2
	                                                 MOV RAM1_ADR,CT1
	                                                 MOV MAT_SIZE-1,LOP
	LPS
	                                                 MOV MC2,MC1
WAITING:
	JMP T0,WAITING
;
; (execute array calculation)
	                                                 MOV RAM0_ADR,CT0
	                                                 MOV RAM1_ADR,CT1
	     MOV MC0,X             MOV MC1,Y
	     MOV MC0,X  MOV MUL,P  MOV MC1,Y  CLR A
	AD2  MOV MC0,X  MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV RAM0_ADR,CT0
	AD2             MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV #1,RX
	AD2  MOV MC0,X  MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV RAM2_ADR+3,CT2
	AD2  MOV MC0,X  MOV MUL,P  MOV MC1,Y  CLR A      MOV ALL,MC2
	AD2  MOV MC0,X  MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV RAM0_ADR,CT0
	AD2             MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV #1,RX
	AD2  MOV MC0,X  MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV RAM2_ADR+7,CT2
	AD2  MOV MC0,X  MOV MUL,P  MOV MC1,Y  CLR A      MOV ALL,MC2
	AD2  MOV MC0,X  MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV RAM0_ADR,CT0
	AD2             MOV MUL,P  MOV MC1,Y  MOV ALU,A  MOV #1,RX
	AD2             MOV MUL,P             MOV ALU,A  MOV RAM2_ADR+11,CT2
	AD2                                              MOV ALL,MC2
	ENDI

; ------- sample (3) end -------
