#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef int size_t;

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

extern unsigned long v_magic;
extern unsigned long v_addr;

/* BASE.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const unsigned char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, size_t limit);
extern char *strncpy(char *dest, const char *src, size_t limit);

/* SCRN.C */
extern void init_video(void);
extern void puts(unsigned char *text);
extern void putch(unsigned char c);
extern void prints(char *text,char last);
extern void printc(char c);
extern void printhex(unsigned long num,char last);
extern void printnum(unsigned long num,int base,char last);
extern void move_csr_back(void);
extern void cls();
extern void scroll();

/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_wait(int ticks);
extern void timer_install();

/* KEYBOARD.C */
extern void keyboard_install();
extern void addToBuffer(char c);
extern void move_csr(void);
extern void wait_com();
extern void delete_char(int pos);
extern void refresh_com();
extern void clear_line(int n);
extern void insert_char(char c, int pos);
extern void backspace_char(int pos);


extern int csr_x;
extern int csr_y;
extern int com_len;
extern int start_line;
extern char line[256];
extern int init_len;
extern void alert(char s[], int line);
extern void addCharToLine(char c);

/* FUNCTIONS.C */
extern void help();
extern void info();
extern void reboot();
extern void makefunc(char *line,int comlen);
#endif
