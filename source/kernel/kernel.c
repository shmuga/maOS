#include "multiboot.h"

#define TERM_WIDTH 80
#define TERM_HEIGHT 24


void print_char( int line, int pos, int fg_color ,int bg_color , char symbol)
{
	int letter = (bg_color*16*16*16+fg_color*16*16 + (int)symbol);
	*((int*)(753664 + 160 * (line-1) + 2*(pos-1))) = letter;
}

void print_line(int line, int pos, int fg_color ,int bg_color , char *symbol){
	int i=0;
	while(symbol[i] != 0)
	{
		print_char(line,pos+i,fg_color,bg_color,symbol[i]);		
		i++;
	}
		
}

void clear_terminal(int color){
	for (int i=1;i<26;i++){
		for (int j = 1; j <81; j++)
		{
			print_char(i,j,color,color,'a');
		}		
	}
}

void main(unsigned long magic, unsigned long addr)
{
	
	clear_terminal(0);
	// *((int*)0xb8000)=1792 + 65+a;
	// *((int*)0xb8000)=0x07690748 + a;
	// *((int*)0xb80a0)=0x07690748;	
	// print_char(2,45,1,15,'a');
	// char i='a';
	char hello[] = "hello";
	char world[] = "world!";

	// char j='a';
	print_line(12,36,0,2,hello);
	print_line(12,42,0,2,world);

	for(;;);
}