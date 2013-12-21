#include "multiboot.h"
#include "system.h"

void main(unsigned long magic, unsigned long addr)
{	
	init_video();	
	cls();
	puts((unsigned char*)"This is the beggining of the new ERA!");
	gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    // init_video();    
    // timer_install();
    keyboard_install();

    __asm__ __volatile__ ("sti");

	for(;;);
}