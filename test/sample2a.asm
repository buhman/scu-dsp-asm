;; (2) When calculating 2 x 3 + 4 x 5. (RAM0 x RAM1 + RAM0 x RAM1 = RAM2)
;;     (sample 2b is an optimized version of 2a.)

; ------- sample (2a) start -------

RAM0_ADR        = $00   ; 2, 4 Start of storage address
RAM1_ADR        = $00   ; 3, 5 storage address start
RAM2_ADR        = $00   ; Result storage address

        MOV RAM0_ADR,CT0        ; Set RAM0 address
        MOV RAM1_ADR,CT1        ; Set RAM1 address
        MVI #2,MC0              ; Store "2" to RAM0 (at RAM0 address 0, post-incrementing CT0)
        MVI #3,MC1              ; Store "3" to RAM1 (at RAM1 address 0, post-incrementing CT1)
        MVI #4,MC0              ; Store "4" to RAM0 (at RAM0 address 1, post-incrementing CT0)
        MVI #5,MC1              ; Store "5" to RAM1 (at RAM1 address 1, post-incrementing CT1)
        MOV RAM0_ADR,CT0        ; Set RAM0 address
        MOV RAM1_ADR,CT1        ; Set RAM1 address
        MOV RAM2_ADR,CT2        ; Set RAM2 address
        MOV MC0,X               ; Transfer data from RAM0 to RX
        MOV MC1,Y               ; Transfer data from RAM1 to RY
        MOV MUL,P               ; Store the integration result of RX and RY in PH,PL
        MOV MC0,X               ; Transfer data from RAM0 to RX
        MOV MC1,Y               ; Transfer data from RAM1 to RY
        CLR A                   ; Set "0" to ACH and ACL
        AD2   MOV ALU,A         ; Store the addition result of PH,PL and ACH,ACL in ACH,ACL
        MOV MUL,P               ; Store the integration result of RX and RY in PH,PL
        AD2   MOV ALL,MC2       ; Store the addition result of PH, PL and ACH, ACL in RAM2
        ENDI

; ------- sample (2a) end -------
