#include "multiboot.h"
#include "system.h"

void main(unsigned long magic, unsigned long addr)
{	
	init_video();	
	cls();
	puts((unsigned char*)"This is the beggining of the new ERA!");

	for(;;);
}