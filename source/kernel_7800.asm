
	processor 6502

;****** 00-1F ********* TIA REGISTERS ******************

INPTCTRL = $01     ;Input control                                write-only

INPT0    = $08     ;Paddle Control Input 0                       read-only
INPT1    = $09     ;Paddle Control Input 1                       read-only
INPT2    = $0A     ;Paddle Control Input 2                       read-only
INPT3    = $0B     ;Paddle Control Input 3                       read-only

; ** some common alternate names for INPT0/1/2/3
INPT4B   = $08     ;Joystick 0 Fire 0                            read-only
INPT4A   = $09     ;Joystick 0 Fire 1                            read-only
INPT5B   = $0A     ;Joystick 1 Fire 0                            read-only
INPT5A   = $0B     ;Joystick 1 Fire 1                            read-only
INPT4R   = $08     ;Joystick 0 Fire 0                            read-only
INPT4L   = $09     ;Joystick 0 Fire 1                            read-only
INPT5R   = $0A     ;Joystick 1 Fire 0                            read-only
INPT5L   = $0B     ;Joystick 1 Fire 1                            read-only

INPT4    = $0C     ;Player 0 Fire Button Input                   read-only
INPT5    = $0D     ;Player 1 Fire Button Input                   read-only

AUDC0    = $15     ;Audio Control Channel 0                      write-only
AUDC1    = $16     ;Audio Control Channel 1                      write-only
AUDF0    = $17     ;Audio Frequency Channel 0                    write-only
AUDF1    = $18     ;Audio Frequency Channel 1                    write-only
AUDV0    = $19     ;Audio Volume Channel 0                       write-only
AUDV1    = $1A     ;Audio Volume Channel 1                       write-only

;****** 20-3F ********* MARIA REGISTERS ***************

BACKGRND = $20     ;Background Color                             write-only
P0C1     = $21     ;Palette 0 - Color 1                          write-only
P0C2     = $22     ;Palette 0 - Color 2                          write-only
P0C3     = $23     ;Palette 0 - Color 3                          write-only
WSYNC    = $24     ;Wait For Sync                                write-only
P1C1     = $25     ;Palette 1 - Color 1                          write-only
P1C2     = $26     ;Palette 1 - Color 2                          write-only
P1C3     = $27     ;Palette 1 - Color 3                          write-only
MSTAT    = $28     ;Maria Status                                 read-only
P2C1     = $29     ;Palette 2 - Color 1                          write-only
P2C2     = $2A     ;Palette 2 - Color 2                          write-only
P2C3     = $2B     ;Palette 2 - Color 3                          write-only
DPPH     = $2C     ;Display List List Pointer High               write-only
P3C1     = $2D     ;Palette 3 - Color 1                          write-only
P3C2     = $2E     ;Palette 3 - Color 2                          write-only
P3C3     = $2F     ;Palette 3 - Color 3                          write-only
DPPL     = $30     ;Display List List Pointer Low                write-only
P4C1     = $31     ;Palette 4 - Color 1                          write-only
P4C2     = $32     ;Palette 4 - Color 2                          write-only
P4C3     = $33     ;Palette 4 - Color 3                          write-only
CHARBASE = $34     ;Character Base Address                       write-only
P5C1     = $35     ;Palette 5 - Color 1                          write-only
P5C2     = $36     ;Palette 5 - Color 2                          write-only
P5C3     = $37     ;Palette 5 - Color 3                          write-only
OFFSET   = $38     ;Unused - Store zero here                     write-only
P6C1     = $39     ;Palette 6 - Color 1                          write-only
P6C2     = $3A     ;Palette 6 - Color 2                          write-only
P6C3     = $3B     ;Palette 6 - Color 3                          write-only
CTRL     = $3C     ;Maria Control Register                       write-only
P7C1     = $3D     ;Palette 7 - Color 1                          write-only
P7C2     = $3E     ;Palette 7 - Color 2                          write-only
P7C3     = $3F     ;Palette 7 - Color 3                          write-only

;****** 280-2FF ******* PIA PORTS AND TIMERS ************

SWCHA    = $280    ;P0, P1 Joystick Directional Input            read-write
SWCHB    = $282    ;Console Switches                             read-write
CTLSWA   = $281    ;I/O Control for SCHWA                        read-write
SWACNT   = $281    ;VCS name for above                           read-write
CTLSWB   = $283    ;I/O Control for SCHWB                        read-write
SWBCNT   = $283    ;VCS name for above                           read-write

INTIM    = $284    ;Iterval Timer Read                           read-only
TIM1T    = $294    ;Set 1    CLK Interval (838   nsec/interval)  write-only
TIM8T    = $295    ;Set 8    CLK Interval (6.7   usec/interval)  write-only
TIM64T   = $296    ;Set 64   CLK Interval (63.6  usec/interval)  write-only
T1024T   = $297    ;Set 1024 CLK Interval (858.2 usec/interval)  write-only
TIM64TI  = $29E    ;Interrupt timer 64T                          write-only


	SEG
	ORG $1800
;
;loop:
;	ldx $40
;	inx
;	cpx #131
;	bne skip
;	ldx #0
;skip:
;	stx $40
;	stx BACKGRND
;	stx WSYNC
;	stx WSYNC
;	jmp loop

	lda #>DLL
	sta DPPH
	lda #<DLL
	sta DPPL
; Wait for VBLANK
PollVBlank:
	sta WSYNC
	lda MSTAT
	bpl PollVBlank
; Check for signal that cart has the data ready
	ldx $18fc
	ldx $18fd
	ldx $18fe
	ldx $18ff
	ldx $f7dc
	cpx #$25
	bne NoSignal
; Disable DMA
	sta CTRL
	sta WSYNC
;	jmp $f700
NoSignal:
; Enable DMA
	lda #$40
	sta CTRL
	
; Wait for VBLANK END
PollNotVBlank:
	sta WSYNC
	lda MSTAT
	bmi PollNotVBlank
	jmp PollVBlank

; Signal for ARM that 6502 is getting ready to poll for control transfer signal
	ORG $18fa
DL_End:
	HEX 00 00
Signal_Cart:
	HEX 25 25 25 25

; DLs $1a00-$1bff (512) 12 per page
; DLL $1900-$19ff (256)
; Code $1800-$18ff (256)

	ORG $1900
DLL:
	; Top padding
	HEX 0f
	BYTE >DL_End
	BYTE <DL_End
	HEX 08
	BYTE >DL_End
	BYTE <DL_End

	REPEAT 24
	HEX 07
	BYTE >DL00
	BYTE <DL00
	REPEND

	; Bottom padding
	REPEAT 5
	HEX 0f
	BYTE >DL_End
	BYTE <DL_End
	REPEND

; GRP_LOW MODE GRP_HIGH PAL/WIDTH POSITION
	ORG $1a00
DL00: ; 24-29 cycles for DMA startup
	; Always start from $f700 because xxx1 0xxx xxxx xxxx is always in cart space
	; 160a
	HEX c0 40 f0 0c 00 ;10 per header
	HEX c0 40 f0 0c 50 ; 3 per byte read
	HEX c0 40 f0 0c 50 ; extra for H scrolling
	; 160b
	HEX c0 c0 f0 80 00
	HEX c0 c0 f0 80 40
	HEX c0 c0 f0 90 80
	HEX c0 c0 f0 90 80 ; extra for H scrolling
	HEX 00 00
