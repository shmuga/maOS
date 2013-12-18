    global loader                   ; the entry symbol for ELF    
    extern main
    MODULEALIGN       equ     1<<0
    MEMINFO           equ     1<<1
    FLAGS             equ     MODULEALIGN | MEMINFO
    MAGIC             equ     0x1BADB002
    CHECKSUM          equ     -(MAGIC + FLAGS)

    section .text:                  ; start of the text (code) section 
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM    

    loader:                         ; the loader label (defined as entry point in linker script)
        mov esp, 0xCAFEBABE 
        mov byte [0xB8000],'h'
    .loop:
        hlt
        jmp .loop                   ; loop forever
        