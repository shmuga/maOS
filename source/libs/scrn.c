#include "system.h"

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
int com_len = 0;
int start_line = 0;
char line[256] = "";

char init_line[] = "command: ";
int init_len = 9;


void scroll(void)
{
    unsigned blank, temp;
    blank = 0x20 | (attrib << 8);
    if(csr_y >= 25)
    {
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

void move_csr(void)
{
    unsigned temp;
    temp = csr_y * 80 + csr_x;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void cls()
{
    unsigned blank;
    int i;

    blank = 0x20 | (attrib << 8);

    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }

    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }    
    else if(c == '\r')
    {
        csr_x = 0;
    }    
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }

    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }
    scroll();
    move_csr();
}

void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void init_video(void)
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}

void wait_com() {
    start_line = csr_y;    
    puts((unsigned char*)init_line);
    csr_x = init_len;
}

void clear_line(int n) {
    int cur_y = csr_y;
    int cur_x = csr_x;
    char blink_line[] = "                                                                                ";
    csr_y = n;
    csr_x = 0;
    puts((unsigned char*)blink_line);
    csr_y = cur_y;
    csr_x = cur_x;
}

void refresh_com() {
    int cur_y = csr_y;
    int cur_x = csr_x;
    for (int i = start_line; i <= csr_y; i++) {
        clear_line(i);
    }
    csr_y = start_line;
    csr_x = 0;
    wait_com();
    for (int i = 0; i < com_len; i++) {
        putch(line[i]);
    }
    csr_y = cur_y;
    csr_x = cur_x;
    move_csr();
}

void insert_char(char c, int pos) {
    for (int i = com_len; i >= pos; i--) {
        if (line[i-1] == ' ') line[i] = ' ';
        else line[i] = line[i - 1];
    }
    line[pos] = c;
    com_len++;
    refresh_com();
    csr_x++;
    move_csr();
}

void delete_char(int pos) {
    // alert(line, 20);
    int temp = 80 * (csr_y - start_line) + csr_x - init_len;
    if (temp >= com_len) return;
    if (com_len > 0) {
        for (int i = pos; i < com_len; i++) {
            line[i] = line[i + 1];
        }        
        com_len--;
        line[com_len] = 0;
    }
    refresh_com();
    // alert(line, 21);
}

void backspace_char(int pos) {
    int temp = 80 * (csr_y - start_line) + csr_x - init_len;
    if (temp > com_len) return;
    if (temp <= 0) return;
    if (com_len > 0) {
        for (int i = pos; i < com_len; i++) {
            line[i] = line[i + 1];
        }
        com_len--;
        csr_x--;
    }
    refresh_com();

}

void alert(char s[], int line) {
    clear_line(line);
    int cur_y = csr_y;
    int cur_x = csr_x;
    csr_y = line;
    csr_x = 0;
    putch('|');
    for (int i = 0; i < 70; i++) {
        putch(s[i]);
    }
    putch('|');
    csr_y = cur_y;
    csr_x = cur_x;
    move_csr();
}
// command: hello
////////////01234567890
// command: helolo
