;; (1) The contents of internal RAM0 of the DSP are copied to internal RAM1.

; ------- sample (1) start -------

COPY_SIZE       = 12    ; copy size
RAM0_ADR        = $00   ; copy source address
RAM1_ADR        = $00   ; copy destination address

        MOV RAM0_ADR,CT0        ; Set copy source address of RAM0
        MOV RAM1_ADR,CT1        ; Set copy destination address for RAM1
        MOV COPY_SIZE-1,LOP     ; Set transfer size minus 1 to LOP register
        LPS                     ; Execution of one instruction loop
        MOV MC0,MC1             ; Transfer from RAM0 to RAM1
        ENDI

; ------- sample (1) end -------
