#include "multiboot.h"
#include "system.h"
#include "stdlib.h"

unsigned long v_magic;
unsigned long v_addr;

void main(unsigned long magic, unsigned long addr)
{	
    v_magic = magic;
    v_addr = addr;
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();
    // timer_install();
    keyboard_install();
    // multiboot_info_t *mbi;
    __asm__ __volatile__ ("sti");
    // timer_wait(60);
    cls();
    // prints("Welcome to the maOS system v0.00001.",'\n');
    // help();	    
    wait_com();
    // info(magic,addr);
    // reboot();
        
	// puts((unsigned char*)"This is the beggining of the new ERA!");
	for(;;);
}