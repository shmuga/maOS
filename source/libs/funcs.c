#include "system.h"
#include "multiboot.h"
#include "stdlib.h"

void help(){
	char help[]= "Use one of this functions : \n \
	help - all functions in one doc \n \
	info - information about the system \n \
	cls - clear the screen \n \
	reboot - reboot the system \n";
	prints(help,0);
}

void freemem(multiboot_info_t *mbi){
    if(mbi->flags & (1 << 6))
    {
       unsigned long TotalMapAddress = mbi->mmap_addr;
       unsigned long TotalMapLength = mbi->mmap_length;
       
       prints("----\n",0);
       prints("MapAdress: ",0);
       printhex(TotalMapAddress,0);
       prints("\n",0);
       prints("Map length: ",0);
       printhex(TotalMapLength,0);
       prints("\n----\n",'\n');

       memory_map_t *MemMap = (memory_map_t*)mbi->mmap_addr;

       unsigned long CurrentReadingAddress = TotalMapAddress;
       unsigned long freemem = 0;  
       unsigned long allmem = 0;     
       prints("Map adress - type - base adress - length",'\n');
       while((long)MemMap < TotalMapAddress + TotalMapLength)
       {
          
          printhex((int)MemMap,'-');          
          printhex(MemMap->type,'=');
          printhex(MemMap->base_addr_low,'=');
          printhex(MemMap->length_low,'\n');
          
             
          if(MemMap->type == 1)
          {             
              freemem += MemMap->length_low;
          }
          allmem += MemMap->length_low;
          CurrentReadingAddress += MemMap->size;
          MemMap = (memory_map_t*)((unsigned long)MemMap + MemMap->size + sizeof(unsigned int));

       }
       prints("\nAll memomry (KB): ",0);
       printnum(allmem/1000,10,'\n');
       prints("\nFree memomry (KB): ",0);
       printnum(freemem/1000,10,'\n');
       prints("\nUsed memomry (KB): ",0);
       printnum((allmem-freemem)/1000,10,'\n');
    }    
}

void info(unsigned long magic, unsigned long addr){
	multiboot_info_t *mbi;
    mbi = (multiboot_info_t *) addr;
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC){
       prints ("Invalid magic number",0);
       return;
    }

    mbi = (multiboot_info_t*) addr;
    freemem(mbi);
}

void reboot(){
  outportb(0x64,0xFE);
}

void makefunc(char *line,int comlen){
    if(strcmp(line,"help")==0) help();
    if(strcmp(line,"info")==0) info(v_magic,v_addr);
    if(strcmp(line,"reboot")==0) reboot();
    if(strcmp(line,"cls")==0) cls();
}