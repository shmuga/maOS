    global loader                
    extern main
    
    MODULEALIGN       equ     1<<0
    MEMINFO           equ     1<<1
    FLAGS             equ     MODULEALIGN | MEMINFO
    MAGIC             equ     0x1BADB002
    CHECKSUM          equ     -(MAGIC + FLAGS)
    KERNEL_STACK_SIZE equ     4096    

    section .multiboot
        align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

    section .bss
    kernel_stack:                 
        resb KERNEL_STACK_SIZE    

    section .text:          
    loader:
        mov esp, kernel_stack + KERNEL_STACK_SIZE                        
        call main
        hlt
    .loop:        
        jmp .loop                  
        
    